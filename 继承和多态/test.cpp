#define _CRT_SECURE_NO_WARNINGS
#include "extend.h"
#include "poly.h"



//int main()
//{
//	//Teacher tc({"刘老师","English","湖南郴州","1356656",20});
//	Teacher tc({ "刘老师" });
//	//Teacher tc;
//	Student st;
//	JMP::stack<int> sl;
//	sl.push(1);
//	sl.push(2);
//	sl.push(3);
//	sl.push(4);
//
//	while (!sl.empty())
//	{
//		cout << sl.top() << " ";
//		sl.pop();
//	}
//	tc.identity();
//	st.identity();
//	return 0;
//}

//int main()
//{
//	int a = 1;//临时变量具有常性这个点不能忘记
//	const double& d = a;
//	Student sobj;
//	// 1.派⽣类对象可以赋值给基类的指针/引⽤//会产生切片
//	Person* pp = &sobj;
//	Person& rp = sobj;
//
//	// 派⽣类对象可以赋值给基类的对象 是通过调⽤基类的拷⻉构造完成的 同样会产生切片
//	Person pobj = sobj;
//
//	//2.基类对象不能赋值给派⽣类对象，这⾥会编译报错
//	//sobj = pobj;
//
//	return 0;
//}

//int main()
//{
//	Student s1("jiang cheng");
//	s1.Print();
//
//	return 0;
//};
//int main()
//{
//	B b;
//	b.fun(10);//与基类的函数构成隐藏关系 从派生类找 找不到对应的函数就编译报错
//	b.A::fun();//只能使用显示调用的方法 才能看见被隐藏的函数 ----》b.fun();编译报错
//	return 0;
//};

//int main()
//{
//	Student s1("jack", 18);
//	Student s2(s1);
//	Student s3("rose", 17);
//	s1 = s3;
//
//	return 0;
//}

//int main()
//{
//	Base b;
//	Derive d;
//	return 0;
//}
//
//int main()
//{
//	Person p;
//	Student s;
//	// 编译报错：error C2248: “Student::_stuNum”: ⽆法访问 protected 成员
//	// 解决⽅案：Display也变成Student 的友元即可
//	Display(p, s);
//
//	return 0;
//}



//int Person::_count = 0;   // 必须存在，可以初始化为 0 或其他值---属于是开辟空间了 在这里定义
//为防止static 成员被重复定义 要进行只包含在一个cpp文件里 
// 最好不要放在头文件中 会出现链接错误 说重定义 这是为了防止重定义出现的
//int main()
//{
//	Person p;
//	Student s;
//	// 这⾥的运⾏结果可以看到⾮静态成员_name的地址是不⼀样的
//	// 说明派⽣类继承下来了，⽗派⽣类对象各有⼀份
//	cout << &p._name << endl;
//	cout << &s._name << endl;
//	// 这⾥的运⾏结果可以看到静态成员_count的地址是⼀样的
//	// 说明派⽣类和基类共⽤同⼀份静态成员
//	cout << &p._count << endl;
//	cout << &s._count << endl;
//	// 公有的情况下，⽗派⽣类指定类域都可以访问静态成员
//	cout << Person::_count << endl;
//	cout << Student::_count << endl;
//	return 0;
//}


//int main()
//{
//	// 编译报错：error C2385: 对“_name”的访问不明确
//	Assistant a;
//	//a._name = "peter";
//	// 需要显⽰指定访问哪个基类的成员可以解决⼆义性问题，但是数据冗余问题⽆法解决
//	a.Student::_name = "xxx";
//	a.Teacher::_name = "yyy";//但是对于这种情况 名字应该只有一个才对 这里分别取了两个名字 而事实是 应该只有一个名字 处理的应该都是同一个 _name
//	//采用虚拟继承就可以 避免出现这种情况 使被棱形继承的 重新开一份放在 继承成员量的 另一个空间
//	// 使⽤虚继承，可以解决数据冗余和⼆义性----此时被虚拟继承的类就是只有一份 后面的使用都是指向一个
//	return 0;
//}


//int main()
//{
//	// 思考⼀下这⾥a对象中_name是"张三", "李四", "王五"中的哪⼀个？
//	Assistant a("张三", "李四", "王五");
//	cout << a._name << endl;
//	return 0;
//}


