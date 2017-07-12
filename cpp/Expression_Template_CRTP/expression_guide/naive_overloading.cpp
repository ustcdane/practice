// a naive solution( bad! )
// operator overloading
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

class MyType {
public:
	MyType(size_t size, double val = 0.0) : size_(size) {
		features_ = new double [size_];
		for (size_t i = 0; i < size_; i++) features_[i] = val;
		cout << "\tMyType constructor size = " << size_ << "\n";
	}

	// construct vector using initializer list 
	MyType(std::initializer_list<double> init) {
		size_ = init.size();
		features_ = new double[size_];
		for (size_t i = 0; i < size_; i++) features_[i] = *(init.begin() + i);
			cout << "\tMyType constructor size = " << size_ << "\n";
	}
	// in c++11 move constructor can be used here 
	MyType(const MyType& rhs):size_(rhs.size()) {
		features_ = new double[size_];
		for (size_t i = 0; i < size_; i++) features_[i] = rhs[i];
		cout << "\tMyType copy constructor size = " << size_ << "\n";
	}

	MyType& operator=(const MyType& rhs) {
		if (this != &rhs) {
			delete[]features_;
			size_ = rhs.size();
			features_ = new double[size_];
			for (size_t i = 0; i < size_; i++) features_[i] = rhs[i];
			cout << "\tMyType assignment constructor size = " << size_ << "\n";
		}
		return *this;
	}        
	
	// move constructor
	MyType(MyType&& rhs) :size_(rhs.size()) {
		features_ = rhs.features_;
		rhs.size_ = 0;
		rhs.features_ = nullptr;
		cout << "\tMyType move constructor size = " << size_ << "\n";
	}
	// move assignment
	MyType& operator=(MyType&& rhs) {
		if (this != &rhs) {
			size_ = rhs.size_;
			rhs.size_ = 0;
			features_ = rhs.features_;
			rhs.features_ = nullptr;
			cout << "\tMyType move assignment constructor size = " << size_ << "\n";
		}
		*this;
	}
	
	~MyType() { 
		if (nullptr != features_) {
			delete [] features_;
			size_ = 0;
			features_ = nullptr;
		}
	}

	double &operator[](size_t i) { return features_[i]; }
	double operator[](size_t i) const { return features_[i]; }
	size_t size()               const { return size_; }
private:
	size_t size_;
	double* features_;
};

//This kind of approach is inefficient, because temporal memory is allocated and de-allocated during each operation
MyType operator+(MyType const &u, MyType const &v) {
	MyType sum(std::max(u.size(), v.size()));
	for (size_t i = 0; i < u.size(); i++) {
		sum[i] = u[i] + v[i];
	}
	cout << "\t in MyType +\n";
	return sum;
}
// operator- balabala

int main() {
	MyType a(3, 1.1);
	MyType b(3, 2.01);
	MyType c = {3.01, 3.01, 3.01};

	cout << "\t----computing-----\n";
	MyType d = a + b + c;
	for (size_t i = 0; i < d.size(); i++) {
		cout << "\t" << d[i] << "\n";
	}
	return 0;
}
