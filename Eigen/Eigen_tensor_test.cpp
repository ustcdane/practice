#include <unsupported/Eigen/CXX11/Tensor>
#include <iostream>
#include <vector>
#include <string>

// https://bitbucket.org/eigen/eigen/src/677c9f1577810e869f4f09881cabc3e503a810c1/unsupported/Eigen/CXX11/src/Tensor/README.md?at=default&fileviewer=file-view-default

using namespace std;
using namespace Eigen;

int main() {
	// Create a tensor of rank 3 of sizes 2, 3, 4.  This tensor owns
	// memory to hold 24 floating point values (24 = 2 x 3 x 4)
	Tensor<float, 3> t_3d(2, 3, 4);
	
	// Resize t_3d by assigning a tensor of different sizes, but same rank.
	t_3d = Tensor<float, 3>(3, 4, 3);

	// Create a 4 x 3 tensor of floats. fixed size
	TensorFixedSize<float, Sizes<4, 3>> t_4x3;


	/*
	TensorMap<Tensor<data_type, rank>>(data, size0, size1, ...)
	参数data:要初始化的数据数组地址，(size0,size1,……）矩阵每一维的长度，rank:矩阵的维度。
	没有内存拷贝，仅仅是数据指针映射
	*/
	// Map a tensor of ints on top of stack-allocated storage.
	int storage[128];  // 2 x 4 x 2 x 8 = 128
	TensorMap<Tensor<int, 4>> t_4d(storage, 2, 4, 2, 8);//构造一个int类型，大小为(2,4,2,8)的四维矩阵，数据从storage中映射，没有拷贝数据

	// The same storage can be viewed as a different tensor.
	// You can also pass the sizes as an array.
	TensorMap<Tensor<int, 2>> t_2d(storage, 16, 8);

	// You can also map fixed-size tensors.  Here we get a 1d view of
	// the 2d fixed-size tensor.
	TensorFixedSize<float, Sizes<4, 5>> t_4_3;
	TensorMap<Tensor<float, 1>> t_12(t_4_3.data(), 12);

	// Set the value of the element at position (0, 1, 0);
	Tensor<float, 3> tt_3d(2, 3, 4);
	// assign
	tt_3d(0, 1, 0) = 12.0f;

	// Initialize all elements to random values.
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 4; ++k) {
				tt_3d(i, j, k) = i+j;
			}
		}
	}

	// Print elements of a tensor.
	for (int i = 0; i < 2; ++i) {
		cerr << tt_3d(i, 0, 0) << endl;
	}

	// devices {DefaultDevice, ThreadPoolDevice 、GpuDevice}
	// 可以通过设置device，指定运行设备

	// dim int NumDimensions 
	Eigen::Tensor<float, 2> a(2, 2);
	cout << "Dims " << a.NumDimensions << "\n";
	
	// shape Dimensions dimensions()
	const Eigen::Tensor<float, 2>::Dimensions& d = a.dimensions();
	cout << "Dim size: " << d.size() << ", dim 0: " << d[0] << ", dim 1: " << d[1] << "\n";

	// dim size Index dimension(Index n)
	int dim1 = a.dimension(1);
	cout << "Dim 1: " << dim1 << "\n";

	// size
	cout << "Size: " << a.size() << "\n";

	// init tensor
	// 所有元素初始化：setConstant(const Scalar& val)
	a.setConstant(1.1f);
	cout << "Constant: \n" << a << "\n";

	// setRandom()
	a.setRandom();
	cout << "random: \n" << a << "\n";

	// setZero()
	a.setZero();
	cout << "zero: \n" << a << "\n";

	// init by initializer_list
	a.setValues({ { 0.0f, 1.0f},{ 2.0f, 3.0f } });
	cout << "values: \n" << a << "\n";
	a.setValues({ { 4.0, 1.0, 5.0 } });
	cout << "values: \n" << a << "\n";

	// data pointer
	float* a_data = a.data();
	a_data[0] = 22.22f;
	cout << "a(0, 0): " << a(0, 0) << "\n";

	getchar();
	return 0;
}