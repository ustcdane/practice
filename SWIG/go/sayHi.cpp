#include "sayHi.h"

void Test::Push(const std::string& str) {
	vec_.push_back(str);
}

std::string Test::Get(int i) {
	if(i <0 || i >= vec_.size())
		return "";
	return vec_[i];
}
