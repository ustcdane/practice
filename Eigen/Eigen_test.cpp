#include <iostream>
#include <Eigen/Dense>
// for random test
#include <random>
#include <time.h>
//using Eigen::MatrixXd;
using namespace Eigen;
using namespace Eigen::internal;
using namespace Eigen::Architecture;

using namespace std;

typedef struct GRU_layer {
	VectorXf Z_gate_CPU;
	VectorXf R_gate_CPU;
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

bool getNet(GRU_layer **neu1, int num_hidden_layer)
{
	for (int hl =0; hl < num_hidden_layer; hl++)
	{
		neu1[hl] = new GRU_layer();
		if (!neu1[hl])
		{
			return false;
		}
		neu1[hl]->Z_gate_CPU = VectorXf::Zero(2);
		neu1[hl]->R_gate_CPU = VectorXf::Zero(3);
	}
	return true;
}

void freeNet(GRU_layer **neu1, int num_hidden_layer)
{
	for (int hl = 0; hl < num_hidden_layer; hl++)
	{
		if (neu1[hl])
		{
			//neu1[h1]->R_gate_CPU.
			delete neu1[hl];
			//neu1 = nullptr;
		}
	}
}
int main()
{
	////////////////////////////////Eigen memory//////////////////////////////////////////
	GRU_layer *gruArr[2] = {0};
	if (getNet(gruArr,1))
	{
		cout << "neu1[0]->Z_gate_CPU :" << gruArr[0]->Z_gate_CPU << endl;
		cout << "neu1[0]->R_gate_CPU :" << gruArr[0]->R_gate_CPU << endl;
	}

	freeNet(gruArr, 1);
	cout << "neu1[0]->R_gate_CPU :" << gruArr[0]->R_gate_CPU <<"\n-----\n"<< endl;

	////////////////////////////////Eigen random//////////////////////////////////////////
	//std::cout << s << std::endl;
	std::default_random_engine random(time(nullptr));
	std::uniform_int_distribution<int> dis1(0, 100);
	for (int i = 0; i < 10; ++i)
		cout << dis1(random) << ' ';
	cout << endl;
#pragma region one_d_object

	cout << "*******************1D-object****************" << endl;

	Vector4d v1;
	v1 << 1, 2, 3, 4;
	cout << "v1=\n" << v1 << endl;
	cout << "v1 row size:\n" << v1.rows() << endl;
	
	VectorXd v2(3);
	v2 << 1, 2, 3;
	cout << "v2=\n" << v2 << endl;

	Vector3d v3d_3;
	v3d_3 << 1, 1, 1;
	cout << "v3d_3 = \n" << v3d_3 << endl;
	cout << "v3d_3.transpose()*v3d_3 =\n" << v3d_3.transpose()*v3d_3 << endl;

	//cout << "v3d_3*v3d_3:\n" << v3d_3*v3d_3 << endl;
	
	RowVector3d rV;
	rV << 1, 2, 3;
	cout << "rV=\n" << rV << endl;

	Array4i v3;
	v3 << 1, 2, 3, 4;
	cout << "v3=\n" << v3 << endl;

	ArrayXf v4(3);
	v4 << 1, 2, 3;
	cout << "v4=\n" << v4 << endl;

#pragma endregion

#pragma region two_d_object

	cout << "*******************2D-object****************" << endl;
	//2D objects:
	MatrixXd m(2, 2);

	//method 1
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	cout << "m=\n" << m << endl;
	//method 2
	m << 3, -1,
		2.5, -1.5;
	cout << "m=\n" << m << endl;

#pragma endregion

#pragma region Comma_initializer

	cout << "*******************Initialization****************" << endl;

	int rows = 5;
	int cols = 5;
	cout << "VectorXd::Zero(9):\n" << VectorXd::Zero(9) << endl;
	MatrixXf m1(rows, cols);
	m1 << (Matrix3f() << 1, 2, 3, 4, 5, 6, 7, 8, 9).finished(),
		MatrixXf::Zero(3, cols - 3),
		MatrixXf::Zero(rows - 3, 3),
		MatrixXf::Identity(rows - 3, cols - 3);
	cout << "m1=\n" << m1 << endl;

	cout << "Block in  m1, m1.block(1,0,2,2):" << endl;
	cout << m1.block(1,0,2,2) << endl;

	cout << "Block in  m1, m1.block(1,0,1,3):" << endl;
	cout << m1.block(1, 0, 1, 3) << endl;

	MatrixXi mi2(2, 2);
	mi2 << 1, 1, 2, 2;
	cout << "mi2 = \n" << mi2 << endl;


#pragma endregion

#pragma region Runtime_info

	cout << "*******************Runtime Info****************" << endl;

	MatrixXf m2(5, 4);
	m2 << MatrixXf::Identity(5, 4);
	cout << "m2=\n" << m2 << endl;

	MatrixXf m3;
	m3 = m1*m2;
	cout << "m3.rows()=" << m3.rows() << "  ;  "
		<< "m3.cols()=" << m3.cols() << endl;

	cout << "m3=\n" << m3 << endl;

#pragma endregion

#pragma region Resizing

	cout << "*******************Resizing****************" << endl;

	//1D-resize	
	v1.resize(4);
	cout << "Recover v1 to 4*1 array : v1=\n" << v1 << endl;

	//2D-resize
	m.resize(2, 3);
	cout << " m.resize(2, 3) m=\n" << m << endl;
	m.resize(Eigen::NoChange, 3);
	m.resizeLike(m2);
	m.resize(2, 2);

#pragma endregion

#pragma region Coeff_access

	cout << "*******************Coefficient access****************" << endl;

	float tx = v1(1);
	tx = m1(1, 1);
	cout << endl;

#pragma endregion

#pragma  region Predefined_matrix

	cout << "*******************Predefined Matrix****************" << endl;

	//1D-object
	typedef  Matrix3f   FixedXD;
	FixedXD x;

	x = FixedXD::Zero();
	x = FixedXD::Ones();
	x = FixedXD::Constant(tx);//tx is the value
	x = FixedXD::Random();
	cout << "x=\n" << x << endl;

	typedef ArrayXf Dynamic1D;
	//»òÕß typedef VectorXf Dynamic1D
	int size = 3;
	Dynamic1D xx;
	xx = Dynamic1D::Zero(size);
	xx = Dynamic1D::Ones(size);
	xx = Dynamic1D::Constant(size, tx);
	xx = Dynamic1D::Random(size);
	cout << "xx=\n" << x << endl;

	//2D-object
	typedef MatrixXf Dynamic2D;
	Dynamic2D y;
	y = Dynamic2D::Zero(rows, cols);
	y = Dynamic2D::Ones(rows, cols);
	y = Dynamic2D::Constant(rows, cols, tx);//tx is the value
	y = Dynamic2D::Random(rows, cols);

#pragma endregion

#pragma region Arithmetic_Operators

	cout << "******************* Arithmetic_Operators****************" << endl;

	//add & sub
	MatrixXf m4(5, 4);
	MatrixXf m5;
	m4 = m2 + m3;
	m3 -= m2;

	cout << "m1 size:" << m1.size() << "\nm1:\n" <<m1 << "\n";
	cout << "m2 size:" << m2.size() << "\nm2:\n" << m2 << "\n";
	//product
	m3 = m1*m2;
	cout << "m3 = m1*m2=\n" << m3 << "\n";


	cout << "m4:" << m4 << "\n";
	cout << "m4.size(): " << m4.size() << endl;
	//transposition
	m5 = m4.transpose();
	cout << "m4.transpose():" << m5 << "\n";
	//m5=m.adjoint();//°éËæ¾ØÕó	

	//dot product
	double xtt;
	cout << "v1=\n" << v1 << endl;
	v2.resize(4);
	v2 << VectorXd::Ones(4);
	cout << "v2=\n" << v2 << endl;

	cout << "*************dot product*************" << endl;
	xtt = v1.dot(v2);
	cout << "v1.*v2=" << xtt << endl;

	//vector norm

	cout << "*************matrix norm*************" << endl;
	xtt = v1.norm();
	cout << "norm of v1=" << xtt << endl;
	xtt = v1.squaredNorm();
	cout << "SquareNorm of v1=" << xtt << endl;

#pragma endregion

	cout << endl;
	getchar();
}
