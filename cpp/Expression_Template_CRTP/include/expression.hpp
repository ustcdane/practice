#pragma  once
// Copyright (C) 2017 http://ustcdane.github.io/
// Author: Daniel Wang <daneustc@gmail.com>

namespace op
{
	// 值类型默认为double, 可以通过定义OP_FLOATING_POINT_TYPE来改精度
#ifdef OP_FLOATING_POINT_TYPE
	typedef OP_FLOATING_POINT_TYPE Real;
#else
	typedef double Real;
#endif

	// expression 函数求值返回类型
	typedef Real OP_VALUE_RETURN_TYPE;

	// 这个就是expression template,所有子类必须继承于它
	// op，valueType等的基类，CRTP，继承者即Expression的模板参数
	template<class A>
	struct Expression {

		// 根据模板参数(A)，把expression 转换到真正的类型(const reference of A)
		const A& cast() const { return static_cast<const A&>(*this); }

		OP_VALUE_RETURN_TYPE value() const {
			return cast().value();
		}

	private:// 防止继承者不是Expression的模板参数
		Expression() {}
		friend A;
		Expression& operator=(const Expression&) {
			return *this;
		}
	};
}// End of namespace op
