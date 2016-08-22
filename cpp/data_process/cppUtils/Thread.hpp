#ifndef _THREAD_HPP
#define _THREAD_HPP

#include <stdio.h>
#include <stdlib.h>
#include "NonCopyable.hpp"

#define MY_CHECK(exp) \
	    if(!(exp)){fprintf(stderr, "File:%s, Line:%d Exp:[" #exp "] is true, abort.\n", __FILE__, __LINE__); abort();}

namespace cppUtils {
class IThread: NonCopyable {
 private:
  pthread_t thread_;
  bool isStarted;
  bool isJoined;
 public:
  IThread(): isStarted(false), isJoined(false) {
  }
  virtual ~IThread() {
    if(isStarted && !isJoined) {
      MY_CHECK(!pthread_detach(thread_));
    }
  };
 public:
  virtual void run() = 0;
  void start() {
    MY_CHECK(!isStarted);
    MY_CHECK(!pthread_create(&thread_, NULL, worker_, this));
    isStarted = true;
  }
  void join() {
    MY_CHECK(!isJoined);
    MY_CHECK(!pthread_join(thread_, NULL));
    isJoined = true;
  }
 private:
  static void * worker_(void * data) {
    IThread * ptr = (IThread* ) data;
    ptr->run();
    return NULL;
  }
};
}

#endif
