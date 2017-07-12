#pragma once

//Copyright (C) 2017 http://ustcdane.github.io/
//Author: Daniel Wang <daneustc@gmail.com>

#include <iostream>

#include "op.hpp"

namespace op {

	// 对基本类型 Real(默认为double)的封装
	class valueType : public Expression<valueType> {
	public:
		valueType() : val_(0.0) {}

		valueType(const Real& rhs) : val_(rhs) {}
		// here is where evaluation happens
		valueType(const valueType& rhs) :val_(rhs.value()) {}

		// 参数为Expression类型的构造函数
		template<class R>
		valueType(const Expression<R>& rhs) : val_(rhs.value()) {}

		valueType& operator=(const Real& rhs) {
			val_ = rhs;
			return *this;
		}
		// here is where computing happens,lazy support
		valueType& operator=(const valueType& rhs) {
			val_ = rhs.value();
			return *this;
		}
		
		// here is where computing happens,lazy support
		template<class R>
		valueType& operator=(const Expression<R>& rhs) {
			val_ = rhs.value();
			return *this;
		}

		template<class R>
		valueType& operator+=(const Expression<R>& rhs) {
			return *this = (*this + rhs);
		}

		template<class R>
		valueType& operator-=(const Expression<R>& rhs) {
			return *this = (*this - rhs);
		}

		template<class R>
		valueType& operator*=(const Expression<R>& rhs) {
			return *this = (*this * rhs);
		}

		template<class R>
		valueType& operator/=(const Expression<R>& rhs) {
			return *this = (*this / rhs);
		}

		valueType& operator+=(const Real& rhs) {
			val_ += rhs;
			return *this;
		}
		valueType& operator-=(const Real& rhs) {
			val_ -= rhs;
			return *this;
		}
		valueType& operator*=(const Real& rhs) {
			return *this = (*this * rhs);
		}
		valueType& operator/=(const Real& rhs) {
			return *this = (*this / rhs);
		}

		// it's important, if don't implement,error will be:
		// op::Expression<op::valueType>::value': recursive on all control paths, function will cause runtime stack overflow
		OP_VALUE_RETURN_TYPE value() const {
			return val_;
		}

		void set_value(const Real& x) { val_ = x; }

	protected:
		Real val_;
	}; // End of definition of valueType

	template<class A>
	inline Real value(const Expression<A>& x) { return x.value(); }

	inline std::ostream& operator<< (std::ostream& os, const op::valueType& x)
	{
		os << value(x);
		return os;
	}

	typedef valueType doubleType;

} // End of namespace op

