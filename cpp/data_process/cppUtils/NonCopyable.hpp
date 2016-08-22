/*=============================================================================
#     FileName: NonCopyable.hpp
#         Desc: 
#       Author: Daniel Wang
#        Email: daneustc@gmail.com
#     HomePage: http://ustcdane.github.io/
#      Version: 0.0.1
#   LastChange: 2016-08-18 11:42:29
#      History:
=============================================================================*/
#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

#include <iostream>
#include <string>

namespace cppUtils {
class NonCopyable {
 protected:
  NonCopyable() {};
  ~NonCopyable() {};
 private:
  NonCopyable(const NonCopyable& );
  const NonCopyable& operator=(const NonCopyable& );
};
}

#endif
