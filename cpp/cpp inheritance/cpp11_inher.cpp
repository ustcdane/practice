#include <iostream>
using namespace std;

/*
构造方法用来初始化类的对象，与父类的其它成员不同，它不能被子类继承（子类可以继承父类所有的成员变量和成员方法，但不继承父类的构造方法）。
因此，在创建子类对象时，为了初始化从父类继承来的数据成员，系统需要调用其父类的构造方法。
如果没有显式的构造函数，编译器会给一个默认的构造函数，并且该默认的构造函数仅仅在没有显式地声明构造函数情况下创建。
*/

/*
构造原则如下：
1. 如果子类没有定义构造方法，则调用父类的无参数的构造方法。
2. 如果子类定义了构造方法，不论是无参数还是带参数，在创建子类的对象的时候,首先执行父类无参数的构造方法，然后执行自己的构造方法。
3. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数，则会调用父类的默认无参构造函数。
4. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类自己提供了无参构造函数，则会调用父类自己的无参构造函数。
5. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类只定义了自己的有参构造函数，则会出错（如果父类只有有参数的构造方法，
   则子类必须显示调用此带参构造方法）。
6. 如果子类调用父类带参数的构造方法，需要用父类的构造函数初始方式。
*/



class AA {
public:
	AA() {} // 去掉的话,BB会出错
	AA(int a) :a_(a) {}
	int a_;
};
class BB :public AA {
public:
	BB() { b_ = 2; }
	int b_;
};

/************************************************************************/
/*                                                                      */
/************************************************************************/

class A {
public:
	A(int *pa, int &a):pa_(pa),ref_a_(a),a_(a){}
	int *pa_;
	int &ref_a_;
	int a_;
};

struct MyType {
	MyType():mm_(222){}
		int mm_;
};

class B:public A {
public:
	// 子类初始化父类成员，如果想要真正的起作用，需要初始化指针或者引用的类型
	B() :A(&(m_.mm_), m_.mm_) {}
	MyType m_;
};


int main() {

	BB bb;
	cout << bb.a_ << "\t" << bb.b_ << "\n";

	cout << "*************************************************\n";
	B b;
	cout << b.a_ << "\t" << *b.pa_ << "\t" << b.ref_a_ << "\t" << b.m_.mm_ << "\n";


	getchar();
	return 0;
}