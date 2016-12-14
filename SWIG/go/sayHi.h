#ifndef NGINX_MODULE_H_
#define NGINX_MODULE_H_
#include <string>
#include <vector>


class Test {
	public:
		int GetSize() const { return vec_.size();}
		void Push(const std::string& str);
		std::string Get(int i);
	private:
		std::vector<std::string> vec_;
};

//void init_saiHi(){}
#endif
