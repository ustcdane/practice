#include <iostream>

/*
Bjarne Stroustrup:
Think of a trait as a small object whose main purpose is to carry information used
by another object or algorithm to determine "policy" or "implementation details".
*/

/*
当函数，类或者一些封装的通用算法中的某些部分会因为数据类型不同而导致处理或逻辑不同
（而我们又不希望因为数据类型的差异而修改算法本身的封装时），traits会是一种很好的解决方案。
*/

/*

需要在当T为float时，Compute方法的参数为float，返回类型为int，
而当T为其他类型，Compute方法的参数为T，返回类型也为T
*/

template <typename T>
struct TraitsHelper {
	typedef T ret_type;
	typedef T par_type;
};

template <>
struct TraitsHelper<float> {
	typedef int ret_type;
	typedef float par_type;
};

template <typename T>
struct Test {
	static typename TraitsHelper<T>::ret_type compute(typename TraitsHelper<T>::par_type d)
	{
		return d;
	}
};

int main() {
	
	using namespace std;
	
	cout << "Test<int>::compute(1):\t" << Test<int>::compute(1) << "\n";
	cout << "Test<float>::compute(1.1):\t" << Test<float>::compute(1.1) << "\n";
	cout << "Test<double>::compute(1.1):\t" << Test<double>::compute(1.1) << "\n";
	
	return 0;
}
