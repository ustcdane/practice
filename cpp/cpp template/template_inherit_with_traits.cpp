#include <iostream>
//  tiny struct about eigen\unsupported\Eigen\CXX11\src\Tensor\TensorBase.h
// If you has no knowledge about cpp traits please see: https://github.com/ustcdane/practice/tree/master/cpp/cpp%20traits

/*
 Used as template parameter in class to indicate
 which accessors should be provided.
*/
enum AccessorLevels {
	/** Read-only access via a member function. */
	ReadOnlyAccessors=1,
	/** Read/write access via member functions. */
	WriteAccessors=2
};

template <typename T>
struct traits
{
	enum Flag {
		flags = ReadOnlyAccessors
	};
};


template<typename Derived>
struct accessors_level
{
	enum {
		has_direct_access = (traits<Derived>::flags & ReadOnlyAccessors) ? 1 : 0,
		has_write_access = (traits<Derived>::flags & WriteAccessors) ? 1 : 0,
		level = has_direct_access | (has_write_access<<1)
	};
};

// TensorBase Forward Declarations 
template<typename Derived, int AccessLevel> class TensorBase;

// template specialization
template < typename Derived >
class TensorBase < Derived, ReadOnlyAccessors>
{
public:
	typedef traits<Derived> DerivedTraits;
	void level() {
		std::cerr <<"level:" << derived().level_ << "\n";
	}
protected:
	static const int level_ = ReadOnlyAccessors;
	template <typename OtherDerived, int AccessLevel> friend class TensorBase;
	const Derived& derived() const { return *static_cast<const Derived*>(this); }
};


template<typename Derived, int AccessLevel = accessors_level<Derived>::level>
class TensorBase : public TensorBase<Derived, ReadOnlyAccessors> {
public:
	typedef traits<Derived> DerivedTraits;
	template <typename OtherDerived, int OtherAccessLevel> friend class TensorBase;

protected:
	static const int level_ = accessors_level<Derived>::level;
	Derived& derived() { return *static_cast<Derived*>(this); }
};

template<typename T>
struct TensorXX:public TensorBase<TensorXX<T>> {
};

template<typename T>
struct TensorYY :public TensorBase<TensorYY<T>> {
};

// ÌØ»¯
template<typename T_>
struct traits<TensorXX<T_>> {
	enum Flag {
		flags = WriteAccessors
	};
};

template<typename T_>
struct traits<TensorYY<T_>> {
	enum Flag {
		flags = ReadOnlyAccessors|WriteAccessors
	};
};


template<typename T>
void print(TensorBase<T> & t) {
	t.level();
}

int main() {
	TensorXX<int> txx;
	txx.level();
	TensorYY<float> tyy;
	tyy.level();
	std::cerr << "-----------------------------------\n";
	print(txx);
	print(tyy);
	//getchar();
	return 0;
}