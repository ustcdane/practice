// RVO and NRVO test
#include <iostream>

using namespace std;

struct Example{
	Example() {
	cout << "Constructor\n";
}
Example(const Example& rhs) {
	cout << "Copy Constructor\n";
}

Example& operator=(const Example& rhs) {
	cout << "Assignment Constructor\n";
	return *this;
}
};

Example fun() {
	Example temp;
	return temp;
}

// RVO
/*
void fun_rvo(Example& _temp)
{
	Example temp;
	_temp.Example::Example(temp); //copy constructor
	return;
}
*/

// NRVO
/*
void fun_nrvo(Example& _temp) {
	_temp.Example::Example();
	return;
}
*/

int main() {
	Example bar = fun();
	
	return 0;
}
