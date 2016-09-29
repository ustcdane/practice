#include <assert.h>
#include <curl/curl.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

void error(const char* string)
{
  perror(string);
  exit(1);
}

int epollFd;
int timeout = -1;
struct pollfd pollfd;

int socketCallback(CURL* easy, curl_socket_t fd, int action, void* u, void* s)
{
  struct epoll_event event;
  event.events = 0;
  event.data.fd = fd;

  pollfd.fd = fd;
  pollfd.events = 0;
  pollfd.revents = 0;

  if (action == CURL_POLL_REMOVE) {
    printf(">>> %s: removing fd=%d\n", __func__, fd);

    assert(pollfd.fd == fd);
    pollfd.fd = -1;

    int res = epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, &event);
    if (res == -1 && errno != EBADF)
      error("epoll_ctl(DEL)");
    return 0;
  }

  if (action == CURL_POLL_IN || action == CURL_POLL_INOUT) {
    pollfd.events |= POLLIN;
    event.events |= EPOLLIN;
  }
  if (action == CURL_POLL_OUT || action == CURL_POLL_INOUT) {
    pollfd.events |= POLLOUT;
    event.events |= EPOLLOUT;
  }

  printf(">>> %s: adding fd=%d action=%d\n", __func__, fd, action);
  if (event.events != 0) {
    int res = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event);
    if (res == -1)
      res = epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &event);
    if (res == -1)
      error("epoll_ctl(MOD)");
  }

  return 0;
}

int timerCallback(CURLM* multi, long timeout_ms, void* u)
{
  printf(">>> %s: timeout: %ld ms\n", __func__, timeout_ms);
  timeout = timeout_ms;
  return 0;
}

int main(int argc, char** argv)
{
  // argv[1] == URL
  // argc > 2 == use poll instead of epoll
  assert(argc >= 2);
  int usePoll = argc > 2;

  pollfd.fd = -1;

  epollFd = epoll_create(1);
  if (epollFd == -1)
    error("epoll_create");

  curl_global_init(CURL_GLOBAL_ALL);
  printf("Using %s\n", curl_version());

  CURL* easy = curl_easy_init();
  curl_easy_setopt(easy, CURLOPT_URL, argv[1]);
  curl_easy_setopt(easy, CURLOPT_FOLLOWLOCATION, 1);

  CURLM* multi = curl_multi_init();
  curl_multi_setopt(multi, CURLMOPT_SOCKETFUNCTION, socketCallback);
  curl_multi_setopt(multi, CURLMOPT_TIMERFUNCTION, timerCallback);

  curl_multi_add_handle(multi, easy);

  int running_handles = 1;
  while (running_handles > 0) {
    if (usePoll) {
      printf(">>> calling poll\n");
      int res;
      if (pollfd.fd != -1) {
        res = poll(&pollfd, 1, timeout);
      }
      else {
        res = poll(NULL, 0, timeout);
      }
      if (res == -1) {
        error("poll");
      }
      else if (res == 0) {
        curl_multi_socket_action(multi, CURL_SOCKET_TIMEOUT, 0,
                                 &running_handles);
      }
      else {
        curl_multi_socket_action(multi, pollfd.fd, 0,
                                 &running_handles);
      }
    }
    else {
      printf(">>> calling epoll_wait\n");
      struct epoll_event event;
      int res = epoll_wait(epollFd, &event, 1, timeout);
      if (res == -1) {
        error("epoll_wait");
      }
      else if (res == 0) {
        curl_multi_socket_action(multi, CURL_SOCKET_TIMEOUT, 0,
                                 &running_handles);
      }
      else {
        curl_multi_socket_action(multi, event.data.fd, 0,
                                 &running_handles);
      }
    }
  }

  curl_global_cleanup();
  close(epollFd);

  printf(">>> bye bye\n");
  return 0;
}
