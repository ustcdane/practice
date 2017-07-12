#pragma  once
// Copyright (C) 2017 http://ustcdane.github.io/
// Author: Daniel Wang <daneustc@gmail.com>

#include <cmath>

#include "expression.hpp"

namespace op
{
	// 利用CRTP技术实现具体类型的expression template，这里称为op(operator)

/////////////////////////////// 四则运算相关 ///////////////////////////////////
// 因为四则运算只要结合相应运算符进行运算即可,因此这里用宏大法，后面会举例Add方法具体形式
#define OP_DEFINE_BINARY_OPERATOR(OP, OPERATOR)	\
	template <class A, class B>									 \
	struct OP : public Expression<OP<A, B> > {   \
		OP(const Expression<A>& a, const Expression<B>& b) \
			: a_(a.cast()), b_(b.cast()) { }								\
		OP_VALUE_RETURN_TYPE value() const {							\
			return a_.value() OPERATOR b_.value();					\
		}																				\
	private:																	\
		const A& a_;														\
		const B& b_;														\
	};\
			\
	template <class A, class B>	\
	inline	OP<A, B> operator OPERATOR(const Expression<A>& a, const Expression<B>& b) { \
		return OP<A, B>(a.cast(), b.cast()); \
	} \
	\
	template <class A> \
	struct Scalar##OP : public Expression<Scalar##OP<A> > {	\
/* two constructor: Expression + scalar and scalar + Expression */	\
Scalar##OP(const Expression<A>& a, const Real& b)	\
			: a_(a.cast()), result_(b OPERATOR a_.value()) { }	\
	\
	Scalar##OP(const Real& a, const Expression<A>& b)	\
			: a_(b.cast()), result_(a OPERATOR a_.value()) { }	\
	\
		OP_VALUE_RETURN_TYPE value() const {	\
			return result_;	\
		}	\
	private:	\
		const A& a_;	\
		Real result_;	\
	};	\
	\
	template <class A>\
	inline Scalar##OP<A> operator OPERATOR (const Expression<A>& a, const Real& b) { \
		return Scalar##OP<A>(a.cast(), b);	\
	}	\
	\
	template <class A>	\
	inline	Scalar##OP<A> operator OPERATOR(const Real& a, const Expression<A>& b) { \
		return Scalar##OP<A>(a, b.cast());	\
	}	

OP_DEFINE_BINARY_OPERATOR(Add, +)
OP_DEFINE_BINARY_OPERATOR(Sub, -)
OP_DEFINE_BINARY_OPERATOR(Mul, *)
OP_DEFINE_BINARY_OPERATOR(Div, / )

#undef OP_DEFINE_BINARY_OPERATOR

// 举例说明 OP_DEFINE_BINARY_OPERATOR(Add, +) 宏展开的情形
// Add: 一个 expression 和 另一个expression相加
	/*template <class A, class B>
	struct Add : public Expression<Add<A, B> > {
		Add(const Expression<A>& a, const Expression<B>& b): a_(a.cast()), b_(b.cast()) { }

		OP_VALUE_RETURN_TYPE value() const {
			return a_.value() + b_.value();
		}
	private:
		const A& a_;
		const B& b_;
	};

	// 参数类型都是 Expression,重载+,返回Add<A,B>
	template <class A, class B>
	inline Add<A, B> operator+(const Expression<A>& a, const Expression<B>& b) {
		return Add<A, B>(a.cast(), b.cast());
	}

	// ScalarAdd,expression和常量相加的情形
	template <class A>
	struct ScalarAdd : public Expression<ScalarAdd<A> > {
		ScalarAdd(const Expression<A>& a, const Real& b)
			: a_(a.cast()), result_(a_.value() + b) { }

			ScalarAdd(const Real& a, const Expression<A>& b)
			: a_(b.cast()), result_(a + a_.value()) { }

		OP_VALUE_RETURN_TYPE value() const {
			return result_;
		}
	private:
		const A& a_;
		Real result_;
	};

	// 重载+运算符,expression和常量相加
	template <class A>
	inline ScalarAdd<A> operator+(const Expression<A>& a,
			const Real& b) {
		return ScalarAdd<A>(a.cast(), b);
	}
	template <class A>
	inline ScalarAdd<A> operator+(const Real& b,
			const Expression<A>& a) {
		return ScalarAdd<A>(a.cast(), b);
	}
*/

/////////////////////////////// math单目运算相关 ///////////////////////////////////
// 实现math函数库中单个参数的函数，调用expression的value获得值后，调用相关函数计算即可
#define OP_DEFINE_UNARY_FUNCTION(OP,FUNC)	\
template <class A>	\
	struct OP : public Expression<OP<A> > {	\
		OP(const Expression<A>& a)	\
			: a_(a.cast()), result_(FUNC(a.value())) { }	\
	\
		OP_VALUE_RETURN_TYPE value() const {	\
			return result_;	\
		}	\
	private:	\
		const A& a_;	\
		Real result_;	\
	};							\
									\
//template <class A> \
//OP<A> FUNC(const Expression<A>& a)	{\
//	return OP<A>(a.cast);\
//}	

// exponential,sin,cos,log10,log2...
OP_DEFINE_UNARY_FUNCTION(Exp, exp)
OP_DEFINE_UNARY_FUNCTION(Sin, sin)
OP_DEFINE_UNARY_FUNCTION(Cos, cos)
OP_DEFINE_UNARY_FUNCTION(Log10, log10)
OP_DEFINE_UNARY_FUNCTION(Log2, log2)

#undef OP_DEFINE_UNARY_FUNCTION

	/////////////////////////////// 条件运算 相关 ///////////////////////////////////
	// 条件运算, 调用expression的value获得值后，进行比较即可

#define OP_DEFINE_CONDITIONAL(OPERATOR, OP)			\
  template <class A, class B>					\
  inline bool OPERATOR(const Expression<A>& a,				\
		const Expression<B>& b) {			\
    return a.value() OP b.value();				\
  }								\
								\
  template <class A>						\
  inline bool OPERATOR(const Expression<A>& a, const Real& b) {	\
    return a.value() OP b;					\
  }								\
  								\
  template <class B>						\
  inline bool OPERATOR(const Real& a, const Expression<B>& b) {	\
    return a OP b.value();					\
  }
	
	OP_DEFINE_CONDITIONAL(operator==, == )
	OP_DEFINE_CONDITIONAL(operator!=, != )
	OP_DEFINE_CONDITIONAL(operator>, > )
	OP_DEFINE_CONDITIONAL(operator<, < )
	OP_DEFINE_CONDITIONAL(operator>=, >= )
	OP_DEFINE_CONDITIONAL(operator<=, <= )

#undef OP_DEFINE_CONDITIONAL

		// 取反: expression的负数 
		template <class A>
	struct UnaryMinus : public Expression<UnaryMinus<A> > {
		UnaryMinus(const Expression<A>& a)
			: a_(a.cast()) { }

		OP_VALUE_RETURN_TYPE value() const {
			return -a_.value();
		}
	private:
		const A& a_;
	};

	// -expression 
	template <class A>
	inline UnaryMinus<A> operator-(const Expression<A>& a) {
		return UnaryMinus<A>(a.cast());
	}

	// +expression
	template <class A>
	inline A operator+(const Expression<A>& a) {
		return a;
	}

}// End of namespace op

// 由于作用域的原因，把实现过的math相关函数在最外层重载下

#define OP_DEFINE_MATH_FUNCTION(OP,FUNC)	\
template <class A>	\
inline op::OP<A> FUNC(const op::Expression<A>& a) {	\
	return op::OP<A>(a.cast());	\
}	

OP_DEFINE_MATH_FUNCTION(Exp, exp)
OP_DEFINE_MATH_FUNCTION(Sin, sin)
OP_DEFINE_MATH_FUNCTION(Cos, cos)
OP_DEFINE_MATH_FUNCTION(Log10, log10)
OP_DEFINE_MATH_FUNCTION(Log2, log2)

#undef OP_DEFINE_MATH_FUNCTION

/////////////////// 更灵活的接口,方便用户自己定制 //////////////

namespace op {

// 用户可以定制自己的二元操作Func::Op,运算符左右两个参数都是继承与Expression的自定义类型
//  自定义类型和变量相关的操作实现类似,在此不赘述
template<typename Func, typename TLhs, typename TRhs>
struct BinaryOp : public Expression<BinaryOp<Func, TLhs, TRhs> > {
	BinaryOp(const TLhs& lhs, const TRhs& rhs):lhs_(lhs.cast()), rhs_(rhs.cast()) {}
	OP_VALUE_RETURN_TYPE value() const {
		return Func::calc(lhs_.value(), rhs_.value());
	}
	private:
	const TLhs& lhs_;
	const TRhs& rhs_;
};

template<typename Func, typename TLhs, typename TRhs>
inline BinaryOp<Func, TLhs, TRhs>
expToBinaryOp(const Expression<TLhs>& lhs, const Expression<TRhs>& rhs) {
		return BinaryOp<Func, TLhs, TRhs>(lhs.cast(), rhs.cast());
}

// 自定义二元操作运算,用户可以自定义自己的二元操作
struct Minimum {
	static Real calc(Real a, Real b) {
		return a < b ? a : b;
	}
};

} // End of namespace op

// 重载下min函数
template<typename TLhs, typename TRhs>
inline op::BinaryOp<op::Minimum, TLhs, TRhs>
min(const op::Expression<TLhs>& lhs, const op::Expression<TRhs>& rhs) {
	return op::expToBinaryOp<op::Minimum>(lhs, rhs);
}

// 类似的用户可以根据需要实现自己的二元操作
