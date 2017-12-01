#include <iostream>

using namespace std;


/*
// problem
template <typename T, bool isClonable>
class XXContainer
{
public:
		void clone(T* pObj) {
		if (isClonable) {
			pObj->clone();
		}
		else {
			//... non-Clonable algorithm ...
		}
	}
};

// 对于没有实现clone方法的非Clonable类或基本类型,pObj->clone这一句是非法的.

int main() {
int *p1;
XXContainer<int, false> aa;
aa.clone(p1);
return 0;
}
error:
left of '->clone' must point to class/struct/union/generic type
*/

//////////////////////////////////////////////////////////////////////////

// 在我们的模板类中用enum定义一个trait,以标示类是否为Clonable类,然后在原模板类内部引入一个traits提取类Traits,
// 通过对该类进行specilizing,以根据不同的trait提供不同的实现
/*
trait need:
enum
typedef
template (partial) specializatio
*/

struct ComplexObject {
	void clone() { cout << "in clone" << endl; }
};

// Solving the problem of choosing method to call by inner traits class
template <typename T, bool isClonable>
class XContainer
{
public:
	enum { Clonable = isClonable };

	void clone(T* pObj) {
		Traits<isClonable>().clone(pObj);
	}

	template <bool flag>
	struct Traits {
	};

	template <> 
	struct Traits<true> {
		void clone(T* pObj) {
			cout << "before cloning Clonable type" << endl;
			pObj->clone();
			cout << "after cloning Clonable type" << endl;
		}
	};

	template <>
	struct Traits<false> {
		void clone(T* pObj) {
			cout << "cloning non Clonable type" << endl;
		}
	};
};

//////////////////////////////////////////////////////////////////////////
// 假设我们的clone操作只涉及基本类型和ComplexObject及其派生类

struct __xtrue_type { }; // define two mark-type
struct __xfalse_type { };

struct MoreComplexObject {
	virtual void clone() { cout << "in base clone" << endl; }
};

struct DerivedComplexObject : public MoreComplexObject {
	virtual void clone() { cout << "in derived clone" << endl; }
};

// A general edtion of Traits
template <typename T>
struct Traits
{
	typedef __xfalse_type has_clone_method; // trait has clone method or not? All types defaultly has no clone method.
};

// Specialized edition for MoreComplexObject
template <>
struct Traits<MoreComplexObject>
{
	typedef __xtrue_type has_clone_method;
};

template <typename T>
class XXContainer
{
	template <typename flag>
	struct Impl {
	};

	template <>
	struct  Impl <__xtrue_type> {
		void clone(T* pObj) {
			pObj->clone();
		}
	};

	template <>
	struct Impl <__xfalse_type> {
		void clone(T* pObj) {
			std::cerr << "no clone method!\n";
		}
	};
public:
	void clone(T* pObj) {
		Impl<Traits<T>::has_clone_method>().clone(pObj);
	}
};

//////////////////////////////////////////////////////////////////////////

void main()
{

	cout << "************ demo 1 ************\n";
	int* p1 = 0;
	ComplexObject* p2 = 0;

	XContainer<int, false> n1;
	XContainer<ComplexObject, true> n2;

	n1.clone(p1);
	n2.clone(p2);

	cout << "************ demo 2 ************\n";
	p1 = 0;
	MoreComplexObject c;
	MoreComplexObject* pMore1 = &c;
	DerivedComplexObject d;
	MoreComplexObject* pMore2 = &d; // you must point to a derived object by a base-class pointer,
														//it's a little problem

	XXContainer<int> nn1;
	XXContainer<MoreComplexObject> nn2;
	XXContainer<MoreComplexObject> nn3;

	nn1.clone(p1);
	nn2.clone(pMore1);
	nn3.clone(pMore2);

	//getchar();
}
