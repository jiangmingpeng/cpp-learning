#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;



//class Person 
//{
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//};
//class Student : public Person 
//{
//public:
//	virtual void BuyTicket() { cout << "买票-打折" << endl; }//重写函数
//};
//void Func(Person* ptr)
//{
//	// 这⾥可以看到虽然都是Person指针Ptr在调⽤BuyTicket
//	// 但是跟ptr没关系，⽽是由ptr指向的对象决定的。
//	ptr->BuyTicket();
//}
//
//int main()
//{
//	Person ps;
//	Student st;
//	Func(&ps);
//	Func(&st);
//	return 0;
//}


class Animal
{
public:
	virtual void talk() const = 0;//直接=0 这个类就成了 抽象类了 1.不能创建对象 2.压力派生类进行函数重写
};
class Dog : public Animal
{
public:
	virtual void talk() const
	{
		std::cout << "汪汪" << std::endl;
	}
};
class Cat : public Animal
{
public:
	virtual void talk() const
	{
		std::cout << "(>^ω^<)喵" << std::endl;
	}
};
void letsHear(const Animal& animal)//引用
{
	animal.talk();
}
//int main()
//{
//	Cat cat;
//	Dog dog;
//	letsHear(cat);
//	letsHear(dog);
//	return 0;
//}


//class A
//{
//public:
//	virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//	virtual void test() { func(); }
//};
//class B : public A
//{
//public:
//	void func(int val = 0) { std::cout << "B->" << val << std::endl; }
//};
//int main(int argc, char* argv[])
//{
//	B* p = new B;
//	p->test();
//	p->func();
//	return 0;
//}


// error C3668: “Benz::Drive”: 包含重写说明符“override”的⽅法没有重写任何基类⽅法
//class Car {
//public:
//	virtual void Dirve()
//	{
//	}
//};
//class Benz :public Car 
//{
//public:
//	virtual void Drive() override //函数名不同 由override检查出不能重写 或者重写错误
//	{ cout << "Benz-舒适" << endl; }
//};
//int main()
//{
//	return 0;
//}

// error C3248: “Car::Drive”: 声明为“final”的函数⽆法被“Benz::Drive”重写
//class Car
//{
//public:
//	virtual void Drive() final //放在类后面不给继承 放在成员函数后不给重写 
//	{}//
//};
//class Benz :public Car
//{
//public:
//	virtual void Drive() { cout << "Benz-舒适" << endl; }
//};
//int main()
//{
//	return 0;
//
//}

//class Base
//{
//public:
//	virtual void Func1()//有几个虚函数 虚函数表就会有几个成员 包括继承下来的 
//	{
//		cout << "Func1()" << endl;
//	}
//	virtual void Func2()
//	{
//		cout << "Func2()" << endl;
//	}
//	virtual void Func3()
//	{
//		cout << "Func3()" << endl;
//	}
//protected:
//	int _b = 1;
//	char _ch = 'x';
//};
//class A : public Base
//{
//public:
//	virtual void Func1()//有几个虚函数 虚函数表就会有几个成员 包括继承下来的 
//	{
//		cout << "Func1()" << endl;//如果继承下来的虚函数 进行了重写 那么地址就会改变 如果没有重写 地址就是赋值基类的地址 所以在派生类中的
//		//虚函数表中看到的地址就是呈现在眼前的----根据这个虚函数表也可以反过来理解重写调用规则
//	}
//protected:
//	int _add = 1;
//
//};
//int main()
//{
//	//⼀个含有虚函数的类中都⾄少都有⼀个虚函数表指针，因为⼀个类所有虚函数的地址要
//	//被放到这个类对象的虚函数表中，虚函数表也简称虚表
//	Base b;
//	A c;
//	cout << sizeof(b) << endl;//x32平台下 算出来是12 除了类里面的成员变量 还有一个指向虚函数表的指针变量
//	return 0;
//}



class Base 
{
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
	void func5() { cout << "Base::func5" << endl; }
protected:
	int a = 1;
};

class Derive : public Base
{
public:
	// 重写基类的func1
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func1" << endl; }
	void func4() { cout << "Derive::func4" << endl; }
protected:
	int b = 2;
};


//int main()
//{
//	Base b;
//	Derive d;
//	return 0;
//}


int main()
{
	int i = 0;
	static int j = 1;
	int* p1 = new int;
	const char* p2 = "xxxxxxxx";
	printf("栈:%p\n", &i);// 记住有函数栈帧创建的过程就不会容易忘记了
	printf("静态区:%p\n", &j);
	printf("堆:%p\n", p1);
	printf("常量区:%p\n", p2);
	Base b;
	Derive d;
	Base* p3 = &b;
	Derive* p4 = &d;
	printf("Person虚表地址:%p\n", *(int*)p3);
	printf("Student虚表地址:%p\n", *(int*)p4);
	printf("虚函数地址:%p\n", &Base::func1);
	printf("普通函数地址:%p\n", &Base::func5);
	return 0;
}



//栈区（向下增长）
//↓
//（空闲内存）
//↑
//堆区（向上增长）
//静态区（.data + .bss）
//常量区（.rodata）
//代码段（.text）
