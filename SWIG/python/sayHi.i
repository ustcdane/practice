/*sayHi.i*/
/*%module后面的名字是被封装的模块名称，Python通过这个名称加载程序*/
%module sayHi

%{
/*相关引用*/
#define SWIG_FILE_WITH_INIT
#include "sayHi.h"
%}

%include "std_string.i"
%include "std_vector.i"

namespace std {
    %template(StrVector) vector<string>;
}

/* Wrapper并生成代码 */
%include "sayHi.h"
