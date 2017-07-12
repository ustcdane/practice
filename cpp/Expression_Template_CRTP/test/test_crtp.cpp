#include <iostream>
#include <cmath>

#include "valueType.hpp"

using namespace std;
using op::doubleType;


doubleType algorithm(const doubleType x[2]) {
	doubleType y = 1;
	y += x[1] + x[0] * x[1];
	cout << "doubleType y = 1 + x[1] + x[0]*x[1]\n";
	return y;
}

doubleType algorithm2(const doubleType x[2]) {
	doubleType y = exp(x[0]) + -x[1] + 1;
	cout << "doubleType y = exp(x[0]) + -x[1] + 1\n";
	return y;
}

doubleType algorithm3(const doubleType x[2]) {
	const double PI = 3.141592653589793;
	doubleType y = cos(x[0]) + sin(PI/2*log2(x[1]));
	cout << "cos(x[0]) + sin(PI/2*log2(x[1]))\n";
	return y;
}

doubleType algorithm4(const doubleType x[2]) {
	const doubleType m = -0.618;
	doubleType y = min(m, min(x[0], x[1]));
	cout << "m=-0.618\nmin(m, min(x[0], x[1]))\n";
	return y;
}

int main(int argc, char** argv)
{
	doubleType x[2]; 
	doubleType y;    

	x[0] = 0.0;
	x[1] = 2.0;
	cout << "x[0] = " << x[0] << endl;
	cout << "x[1] = " << x[1] << endl;
	std::cout << "Begin run algorithm:\n";
	
	y = algorithm(x);
	std::cout << "y = " << y.value() << "\n";

	y = algorithm2(x);
	std::cout << "y = " << value(y) << "\n";

	y = algorithm3(x);
	std::cout << "y = " << y << "\n";
	if (2 == y)
		cout << "Yes.\ty = 2\n";

	y = algorithm4(x);
	std::cout << "y = " << value(y) << "\n";
	
	return 0;
}
