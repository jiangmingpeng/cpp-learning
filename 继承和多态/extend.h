#pragma once
#include <iostream>
#include <vector>
using namespace std;

//class Person
//{
//public:
//	// 进⼊校园/图书馆/实验室刷⼆维码等⾝份认证
//	void identity()
//	{
//		cout << "void identity()" << _name << endl;
//	}
//protected:
//	string _name = "张三"; // 姓名
//	string _address; // 地址
//	string _tel; // 电话
//	int _age = 18; // 年龄
//};
//
//class Student :public Person
//{
//public:
//	Student(const int& stuid = 0)
//		: _stuid(stuid)
//	{
//
//	}
//	// 进⼊校园/图书馆/实验室刷⼆维码等⾝份认证
//	void identity()
//	{
//		// ...
//	}
//	// 学习
//	void study()
//	{
//		// ...
//	}
//protected:
//	int _stuid; // 学号
//};
//
//class Teacher :public Person
//{
//public:
//	Teacher(const string& title = "teacher")
//		:_title(title)
//	{
//
//	}
//		// 进⼊校园/图书馆/实验室刷⼆维码等⾝份认证
//	void identity()
//	{
//		// ...
//	}
//	// 授课
//	void teaching()
//	{
//		//...
//	}
//protected:
//
//	string _title; // 职称
//};



//namespace JMP
//{
//	//template<class T>
//	//class vector
//	//{};
//	// stack和vector的关系，既符合is-a，也符合has-a
//	template<class T>
//	class stack : public vector<T>//继承vector 的成员（公有 或者是 保护）
//	{
//	public:
//		void push(const T& x)
//		{
//			// 基类是类模板时，需要指定⼀下类域，
//			// 否则编译报错:error C3861: “push_back”: 找不到标识符
//			// 因为stack<int>实例化时，也实例化vector<int>了
//			// 但是模版是按需实例化，push_back等成员函数未实例化，所以找不到
//			vector<T>::push_back(x);//库里面的函数是公有的 而成员变量是保护的  
//			//所以这里的公有继承完全够用
//			//push_back(x);
//		}
//		void pop()
//		{
//			vector<T>::pop_back();//因为这些函数都是公有的（或者是保护）所以可以在派生类内部调用
//		}
//		const T& top()
//		{
//			return vector<T>::back();
//		}
//		bool empty()
//		{
//			return vector<T>::empty();
//		}
//	};
//}

//class Person
//{
//protected:
//	string _name; // 姓名
//	string _sex; // 性别
//	int _age; // 年龄
//};
//class Student : public Person
//{
//public:
//	int _No; // 学号
//};

// Student的_num和Person的_num构成隐藏关系，可以看出这样代码虽然能跑，但是⾮常容易混淆
//class Person
//{
//public:
//	Person(const string& name)
//		:_name(name)
//	{
//
//	}
//protected:
//	string _name = "小李子"; // 姓名
//	int _num = 111; // ⾝份证号
//};
//class Student : public Person
//{
//public:
//	Student(const string& name)
//		//调用基类构造函数来初始化派生类对象中的基类子对象，不属于匿名构造
//		:Person(name)//想要初始化基类的成员 在基类中就得有一个构造函数 否则无法在 派生类实例化对象时进行初始化
//	{
//
//	}
//	void Print()
//	{
//		cout << "姓名:" << _name << endl;
//		cout << "身份证号:" <<Person:: _num << endl;
//		cout << "学号:" << _num << endl;
//
//	}
//protected:
//	int _num = 999; // 学号
//};

//class A
//{
//public:
//	void fun()
//	{
//		cout << "func()" << endl;
//	}
//};
//class B : public A
//{
//public:
//	void fun(int i)
//	{
//		cout << "func(int i)" << i << endl;
//	}
//};



//class Person
//{
//public:
//	Person(const char* name = "peter")//直接构造
//		: _name(name)
//	{
//		cout << "Person()" << endl;
//	}
//
//	Person(const Person& p)//拷贝构造
//		: _name(p._name)
//	{
//		cout << "Person(const Person& p)" << endl;
//	}
//
//	Person& operator=(const Person& p)//赋值构造
//	{
//		cout << "Person operator=(const Person& p)" << endl;
//		if (this != &p)
//			_name = p._name;
//
//		return *this;
//	}
//
//	~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//protected:
//	string _name; // 姓名
//};
//class Student : public Person
//{
//public:
//	Student(const char* name, int num)
//		: Person(name)
//		, _num(num)
//	{
//		cout << "Student()" << endl;
//	}
//
//	Student(const Student& s)
//		: Person(s)
//		, _num(s._num)
//	{
//		cout << "Student(const Student& s)" << endl;
//	}
//
//	Student& operator = (const Student& s)
//	{
//		cout << "Student& operator= (const Student& s)" << endl;
//		if (this != &s)
//		{
//			// 构成隐藏，所以需要显⽰调⽤
//			Person::operator =(s);//调用派生类的赋值构造时 要注意基类的也要同时调用 也要知道构成隐藏 需要显示调用
//			_num = s._num;
//		}
//		return *this;
//	}
//
//	~Student()
//	{
//		cout << "~Student()" << endl;
//	}
//protected:
//	int _num; //学号
//};

//// C++11的⽅法
//class Base //final
//{
//public:
//	void func5() { cout << "Base::func5" << endl; }
//protected:
//	int a = 1;
//private:
//	 //C++98的⽅法/
//	//Base()//把构造函数私有化 那么在派生类实例化对象的时候就无话调用基类的构造 导致编译错误 变向阻止了 类的继承
//	//{}
//};
//class Derive :public Base
//{
//	void func4() { cout << "Derive::func4" << endl; }
//protected:
//	int b = 2;
//};
//
//
//class Student;
//class Person
//{
//public:
//	friend void Display(const Person& p, const Student& s);
//
//protected:
////public:
//	string _name; // 姓名
//};
//class Student : public Person//友元不能继承
//{
//public:
//	friend void Display(const Person& p, const Student& s);
//protected:
//	int _stuNum; // 学号
//};
//void Display(const Person& p, const Student& s)
//{
//	cout << p._name << endl;
//	cout << s._stuNum << endl;
//}

//class Person 
//{
//public:
//	string _name = "jiang cheng!!";
//	static int _count;
//};
//
//class Student : public Person 
//{
//protected:
//	int _stuNum;
//};
//
//class Person
//{
//public:
//	string _name = "jiang cheng"; // 姓名
//};
//class Student : virtual public Person
//{
//protected:
//	int _num; //学号
//};
//class Teacher : virtual public Person
//{
//protected:
//	int _id; // 职⼯编号
//};
//class Assistant : public Student , public Teacher
//{
//protected:
//	string _majorCourse; // 主修课程
//};

//
//class Person
//{
//public:
//	Person(const char* name)
//		:_name(name)
//	{
//	}
//	string _name; // 姓名
//};
//class Student : virtual public Person
//{
//public:
//	Student(const char* name, int num)
//		:Person(name)
//		, _num(num)
//	{
//	}
//protected:
//	int _num; //学号
//};
//class Teacher : virtual public Person
//{
//public:
//	Teacher(const char* name, int id)
//		:Person(name)
//		, _id(id)
//	{}
//protected:
//	int _id; // 职⼯编号
//};
//// 不要去玩菱形继承
//class Assistant : public Student, public Teacher
//{
//public:
//	Assistant(const char* name1, const char* name2, const char* name3)
//		:Person(name1)//最后的_name 由被虚拟继承的类构造函数决定 因为大家的_name 都是继承他的
//		, Student(name2, 1)
//		, Teacher(name3, 2)
//	{
//	}
//protected:
//	string _majorCourse; // 主修课程
//};




// Tire(轮胎)和Car(⻋)更符合has-a的关系
//class Tire {
//protected:
//	string _brand = "Michelin"; // 品牌
//	size_t _size = 17; // 尺⼨
//};
//class Car {
//protected:
//	string _colour = "⽩⾊"; // 颜⾊
//	string _num = "陕ABIT00"; // ⻋牌号
//	Tire _t1; // 轮胎
//	Tire _t2; // 轮胎
//	Tire _t3; // 轮胎
//	Tire _t4; // 轮胎
//};
//class BMW : public Car {
//public:
//	void Drive() { cout << "好开-操控" << endl; }
//};
//// Car和BMW/Benz更符合is-a的关系
//class Benz : public Car {
//public:
//	void Drive() { cout << "好坐-舒适" << endl; }
//};
//template<class T>
//class vector
//{
//};
//// stack和vector的关系，既符合is-a，也符合has-a
//template<class T>
//class stack : public vector<T>
//{
//};
//template<class T>
//class stack
//{
//public:
//	vector<T> _v;
//};



