#include <iostream>
#include <string>
using namespace std;
// C++建立异质链表

class Person
{
public:
	Person(int identity, string name, string birth, char sex)
	{
		m_identity = identity;
		m_name = name;
		m_birth = birth;
		m_sex = sex;
	}
	virtual void Display() = 0;
protected:
	int m_identity;
	string m_name;
	string m_birth;
	char m_sex;
};

class Student : public Person
{
public:
	Student(int identity, string name, string birth, char sex, int gradePoint)
		:Person(identity, name, birth, sex), m_gradePoint(gradePoint) {}
	void Display()
	{
		cout << "证件号：" << m_identity << endl;
		cout << "姓名：" << m_name << endl;
		cout << "性别：" << (m_sex == '0' ? "男" : "女") << endl;
		cout << "出生年月：" << m_birth << endl;
		cout << "学分: " << m_gradePoint << endl << endl;
	}
private:
	int m_gradePoint;
};

class Staff : public Person
{
public:
	Staff(int identity, string name, string birth, char sex, string dept)
		:Person(identity, name, birth, sex), m_dept(dept) {}
	void Display()
	{
		cout << "证件号：" << m_identity << endl;
		cout << "姓名：" << m_name << endl;
		cout << "性别：" << (m_sex == '0' ? "男" : "女") << endl;
		cout << "出生年月：" << m_birth << endl;
		cout << "部门: " << m_dept << endl << endl;
	}
private:
	string m_dept;
};

class Teacher : public Person
{
public:
	Teacher(int identity, string name, string birth, char sex, int fund)
		:Person(identity, name, birth, sex), m_fund(fund) {}
	void Display()
	{
		cout << "证件号：" << m_identity << endl;
		cout << "姓名：" << m_name << endl;
		cout << "性别：" << (m_sex == '0' ? "男" : "女") << endl;
		cout << "出生年月：" << m_birth << endl;
		cout << "科研经费: " << m_fund << endl << endl;
	}
private:
	int m_fund;
};

template <typename T>class HeterList;

template <typename T>
class Node
{
	friend class HeterList<T>;
public:
	Node(T *data) :m_data(data), m_next(NULL) {}
private:
	T *m_data;
	Node<T> *m_next;
};

template <typename T>
class HeterList
{
public:
	HeterList() :m_head(NULL), m_tail(NULL) {}
	void Insert(T *newNode);
	void Delete();
	void Print();
private:
	int m_length;
	Node<T> *m_head;
	Node<T> *m_tail;
};

////////////////////////////////////////////////////////////////
template <typename T>
void HeterList<T>::Insert(T *newNode)
{
	Node<T> *tmp = new Node<T>(newNode);
	if (!m_head)
	{
		m_head = m_tail = tmp;
		m_length++;
	}
	else
	{
		m_tail->m_next = tmp;
		m_tail = tmp;
		m_length++;
	}
}

template <typename T>
void HeterList<T>::Delete()
{
	Node<T> *tmp = m_head;
	m_head = m_head->m_next;
	delete tmp;
}

template <typename T>
void HeterList<T>::Print()
{
	if (!m_head)
	{
		cout << "链表空..." << endl;
		return;
	}
	Node<T> *tmp;
	for (tmp = m_head; tmp; tmp = tmp->m_next)
	{
		tmp->m_data->Display();
	}
}

void main()
{
	Student student(0, "Tom", "19921210", '0', 100);
	Staff staff(1, "Andy", "19960101", '0', "学工处");
	Teacher teacher(2, "Douglas", "19800422", '1', 5000);
	HeterList<Person> myList;
	//加入链表
	myList.Insert(&student);
	myList.Insert(&staff);
	myList.Insert(&teacher);
	myList.Print();
	//逐个删除
	myList.Delete();
	myList.Delete();
	myList.Delete();
	myList.Print();

	getchar();
}