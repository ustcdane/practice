#ifndef _MUTEX_LOCK_HPP
#define _MUTEX_LOCK_HPP

#include <pthread.h>
#include "NonCopyable.hpp"

#define MY_CHECK(exp) \
	        if(!(exp)){fprintf(stderr, "File:%s, Line:%d Exp:[" #exp "] is true, abort.\n", __FILE__, __LINE__); abort();}

namespace cppUtils {
class MutexLock: NonCopyable {
 private:
  pthread_mutex_t mutex_;
 public:
  pthread_mutex_t* getPthreadMutex() {
    return &mutex_;
  }
 public:
  MutexLock() {
    MY_CHECK(!pthread_mutex_init(&mutex_, NULL));
  }
  ~MutexLock() {
    MY_CHECK(!pthread_mutex_destroy(&mutex_));
  }
 private:
  void lock() {
    MY_CHECK(!pthread_mutex_lock(&mutex_));
  }
  void unlock() {
    MY_CHECK(!pthread_mutex_unlock(&mutex_));
  }
  friend class MutexLockGuard;
};
class MutexLockGuard: NonCopyable {
 public:
  explicit MutexLockGuard(MutexLock & mutex)
    : mutex_(mutex) {
    mutex_.lock();
  }
  ~MutexLockGuard() {
    mutex_.unlock();
  }
 private:
  MutexLock & mutex_;
};
#define MutexLockGuard(x) assert(false);
}

#endif
