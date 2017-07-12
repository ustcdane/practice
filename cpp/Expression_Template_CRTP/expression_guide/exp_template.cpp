// expression template
// Copyright (C) 2017 http://ustcdane.github.io/

#include <algorithm>
#include <cstdio>
#include <cassert>

// this is expression, all expressions must inherit it
template<typename A>
struct Expression {
	// returns const reference of the actual type of this expression
		const A& cast() const { return static_cast<const A&>(*this); }
		int size() const { return cast().size(); }// get Expression size
private:
		Expression& operator=(const Expression&) {
			return *this;
		}
		Expression() {}
		friend A;
};

// binary expression: (binary op,lhs, rhs)
// Func can easily allows user customized theirs binary operators
template<typename Func, typename TLhs, typename TRhs>
struct BinaryOp : public Expression<BinaryOp<Func, TLhs, TRhs> > {
	BinaryOp(const TLhs& lhs, const TRhs& rhs):lhs_(lhs.cast()), rhs_(rhs.cast()) {}

	// work function, computing this expression at position i, import for lazy computing
	double value(int i) const {
		return Func::Op(lhs_.value(i), rhs_.value(i));
	}

	int size() const { return std::max(lhs_.size(), rhs_.size()); }

private:
	const TLhs& lhs_;
	const TRhs& rhs_;
};

// template binary operation, works for any expressions
template<typename Func, typename TLhs, typename TRhs>
inline BinaryOp<Func, TLhs, TRhs>
expToBinaryOp(const Expression<TLhs>& lhs, const Expression<TRhs>& rhs) {
	return BinaryOp<Func, TLhs, TRhs>(lhs.cast(), rhs.cast());
}

// binary operators +
struct Add {
	// any function defined inside its class definition is inline
	static double Op(double a, double b) { 
		return a + b;
	}
};

// define Minimum
struct Minimum {
	static double Op(double a, double b) {
		return a < b ? a : b;
	}
};

template<typename TLhs, typename TRhs>
inline BinaryOp<Add, TLhs, TRhs>
operator+(const Expression<TLhs>& lhs, const Expression<TRhs>& rhs) {
	return expToBinaryOp<Add>(lhs, rhs);
}

template<typename TLhs, typename TRhs>
inline BinaryOp<Minimum, TLhs, TRhs>
min(const Expression<TLhs>& lhs, const Expression<TRhs>& rhs) {
	return expToBinaryOp<Minimum>(lhs, rhs);
}

// allocation just by user
// no constructor and destructor to allocate and de-allocate memory
class MyExpType : public Expression<MyExpType> {
public:
	MyExpType():size_(0) {}
	MyExpType(double *features, int size)
		: size_(size), features_(features) {
		printf("MyExpType constructor size = %d. No memory allocate.\n", size_);
	}
	
	// delete copy constructor, 
	MyExpType(const MyExpType& src_) = delete;
	template<typename ExpType>
	MyExpType(const Expression<ExpType>& src_) = delete;

	// here is where computing happens,lazy support
	template<typename ExpType>
	MyExpType& operator=(const Expression<ExpType>& src) { 
		const ExpType &srcReal = src.cast();
		assert(size_ >= srcReal.size()); //
		for (int i = 0; i < srcReal.size(); ++i) {
			features_[i] = srcReal.value(i); // binary expression value work function
		}
		printf("MyExpType assignment constructor size = %d\n", size_);
		return *this;
	}
	// computing function
	double value(int i) const { return features_[i]; }
	int size()      const { return size_; }

private:
	int size_;
	double* features_;
};

void print(const MyExpType& m) {
	printf("( ");
	for (int i = 0; i < m.size() - 1; ++i) {
		printf("%g, ", m.value(i));
	}
	if (m.size()) 
		printf("%g )\n", m.value(m.size()-1));
	else 
		printf(" )\n");
}

int main() {
	const int N = 3;
	double sa[N] = { 1.1,1.1, 1.1 };
	double sb[N] = { 2.01, 2.01, 2.01 };
	double sc[N] = { 3.01, 3.01, 3.01 };
	double sd[N] = { 0 };
	MyExpType A(sa, N), B(sb, N), C(sc, N), D(sd, N);
	printf("\n");
	printf(" A = "); print(A);
	printf(" B = "); print(B);
	printf(" C = "); print(C);
	printf("\n\tD = A + B + C\n");
	D = A + B + C;
	for (int i = 0; i < A.size(); ++i) {
	printf("%d:\t%g + %g + %g = %g\n",
	i, B.value(i), C.value(i), B.value(i), D.value(i));
	}
	printf("\n\tD = A + min(B, C)\n");
	// D = A + expToBinaryOp<Minimum>(B, C);
	D = A + min(B, C);
	for (int i = 0; i < A.size(); ++i) {
	printf("%d:\t%g + min(%g, %g) = %g\n",
	i, A.value(i), B.value(i), C.value(i), D.value(i));
	}
	
	return 0;
}
