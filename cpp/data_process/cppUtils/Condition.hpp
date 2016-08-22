/*
 * https://github.com/chenshuo/muduo/blob/master/muduo/base/Condition.h
 */

#ifndef _CONDITION_HPP
#define _CONDITION_HPP

#include "MutexLock.hpp"

namespace cppUtils {
class Condition : NonCopyable {
 public:
  explicit Condition(MutexLock& mutex)
    : mutex_(mutex) {
    MY_CHECK(!pthread_cond_init(&pcond_, NULL));
  }

  ~Condition() {
    MY_CHECK(!pthread_cond_destroy(&pcond_));
  }

  void wait() {
    MY_CHECK(!pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
  }

  void notify() {
    MY_CHECK(!pthread_cond_signal(&pcond_));
  }

  void notifyAll() {
    MY_CHECK(!pthread_cond_broadcast(&pcond_));
  }

 private:
  MutexLock& mutex_;
  pthread_cond_t pcond_;
};

}

#endif
