#define _CRT_SECURE_NO_WARNINGS
//类和对象
// 格式和访问限定符 ---public/ private protected 前者公共后两者私有
//#include<iostream>
//using namespace std;
//class Stack
//{
//public:
//	// 成员函数
//	void Init(int n = 4)
//	{
//		array = (int*)malloc(sizeof(int) * n);
//		if (nullptr == array)
//		{
//			perror("malloc申请空间失败");
//			return;
//		}
//		capacity = n;
//		top = 0;
//	}
//	void Push(int x)
//	{
//		// ...扩容
//		array[top++] = x;
//	}
//	int Top()
//	{
//		assert(top > 0);
//		return array[top - 1];
//	}
//	void Destroy()
//	{
//		free(array);
//		array = nullptr;
//		top = capacity = 0;
//	}
//private:
//	// 成员变量
//	int* array;
//	int capacity;
//	int top;
//}; // 分号不能省略
//int main()
//{
//	Stack st;
//	st.Init();
//	st.Push(1);
//	st.Push(2);
//	st.Push(3);
//	cout << st.Top() << endl;
//	st.Destroy();
//	return 0;
//}

//class Date
//{
//public:
//	void Init(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//private:
//	// 为了区分成员变量，⼀般习惯上成员变量
//	// 会加⼀个特殊标识，如_ 或者 m开头
//	int _year; // year_ m_year--很明显成员变量可以在成员函数中直接使用
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d;
//	d.Init(2024, 3, 31);
//	return 0;
//}

// 不再需要typedef，ListNodeCPP就可以代表类型 ------在c++中struct升级成了类 不一样的是 class默认为私有 struct默认为共有
//struct ListNodeCPP
//{
//	void Init(int x)
//	{
//		next = nullptr;
//		val = x;
//	}
//	ListNodeCPP* next;
//	int val;
//};
//int main()
//{
//	return 0;
//}

//类域----凑齐 全局域 局部域 命名空间域 四种常见域
//#include<iostream>
//using namespace std;
//class Stack
//{
//public:
//	// 成员函数
//	void Init(int n = 4);
//private:
//	// 成员变量
//	int* array;
//	int capacity;
//	int top;
//};
//
//void Stack::Init(int n = 4)//放到外面来定义就要考虑类域的问题
//{
//	array = (int*)malloc(sizeof(int) * n);
//	if (array == nullptr)
//	{
//		perror("内存分配有问题\n");
//	}
//	array = 0;
//	top = 0;
//	capacity = n;
//}
//int main()
//{
//	Stack st;
//	st.Init();
//	return 0;
//}
//#include<iostream>
//using namespace std;
//class Date
//{
//public:
//	void Init(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()
//	{
//		cout << _year << "/" << _month << "/" << _day << endl;
//	}
//private:
//	// 这⾥只是声明，没有开空间
//	int _year;
//	int _month;
//	int _day;
//};
//关于对象大小：呢，Date实例化d1和d2两个对象，d1和d2都有各⾃独⽴的成员变量
//_year / _month / _day存储各⾃的数据，但是d1和d2的成员函数Init / Print指针却是⼀样的，存储在对象
//中就浪费了。如果⽤Date实例化100个对象，那么成员函数指针就重复存储100次，太浪费了。这⾥需
//要再额外哆嗦⼀下，其实函数指针是不需要存储的，函数指针是⼀个地址，调⽤函数被编译成汇编指
//令[call 地址]， 其实编译器在编译链接时，就要找到函数的地址，不是在运⾏时找，只有动态多态是在
//运⾏时找，就需要存储函数地址
//-------最终有的对象大小为 成员变量的大小  遵循内存对齐法则 没有成员变量也默认为1 证明对象它存在
//int main()
//{
//	// Date类实例化出对象d1和d2
//	Date d1;
//	Date d2;//d1和d2的成员函数Init / Print指针是⼀样的
//	d1.Init(2024, 3, 31);
//	d1.Print();
//	d2.Init(2024, 7, 5);
//	d2.Print();
//	return 0;
//}


//#include<iostream>
//using namespace std;
//class Date
//{
//public:
//	 //1.⽆参构造函数
//	Date()
//	{
//		_year = 1;
//		_month = 1;
//		_day = 1;
//	}
//	// 2.带参构造函数
//	Date(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	// //3.全缺省构造函数
//	//Date(int year = 1, int month = 1, int day = 1)
//	//{
//	//_year = year;
//	//_month = month;
//	//_day = day;
//	//}
//	void Print()
//	{
//		cout << _year << "/" << _month << "/" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	// 如果留下三个构造中的第⼆个带参构造，第⼀个和第三个注释掉
//	// 编译报错：error C2512: “Date”: 没有合适的默认构造函数可⽤
//	Date d1; // 调⽤默认构造函数
//	Date d2(2025, 1, 1); // 调⽤带参的构造函数
//	// 注意：如果通过⽆参构造函数创建对象时，对象后⾯不⽤跟括号，否则编译器⽆法
//	// 区分这⾥是函数声明还是实例化对象
//	// warning C4930: “Date d3(void)”: 未调⽤原型函数(是否是有意⽤变量定义的?)
//	Date d3();
//	d1.Print();
//	d2.Print();
//	return 0;
//}

//#include<iostream>
//using namespace std;
//typedef int STDataType;
//class Stack
//{
//public:
//	Stack(int n = 4)
//	{
//		cout << "stack///"<<endl;
//		_a = (STDataType*)malloc(sizeof(STDataType) * n);
//		if (nullptr == _a)
//		{
//			perror("malloc申请空间失败");
//			return;
//		}
//		_capacity = n;
//		_top = 0;
//	}
//	// ...
//private:
//	STDataType * _a;
//	size_t _capacity;
//	size_t _top;
//};
//// 两个Stack实现队列
//class MyQueue
//{
//public:
//	//编译器默认⽣成MyQueue的构造函数调⽤了Stack的构造，完成了两个成员的初始化
//private:
//	Stack pushst;
//	Stack popst;
//};
//int main()
//{
//	MyQueue mq;
//	return 0;
//}

//#include<iostream>
//using namespace std;
//typedef int STDataType;
//class Stack
//{
//public:
//	Stack(int n = 4)
//	{
//		cout << "这是初始化" << endl;
//		_a = (STDataType*)malloc(sizeof(STDataType) * n);
//		if (nullptr == _a)
//		{
//			perror("malloc申请空间失败");
//			return;
//		}
//		_capacity = n;
//		_top = 0;
//	}
//	~Stack()
//	{
//		cout << "~Stack()" << endl;
//		free(_a);
//		_a = nullptr;
//		_top = _capacity = 0;
//	}
//private:
//	STDataType* _a;
//	size_t _capacity;
//	size_t _top;
//};
//// 两个Stack实现队列
//class MyQueue
//{
//public:
//	//编译器默认⽣成MyQueue的析构函数调⽤了Stack的析构，释放的Stack内部的资源
//	// 显⽰写析构，也会⾃动调⽤Stack的析构
//	/*~MyQueue()
//	    {}*/
//private:
//	Stack pushst;
//	Stack popst;
//};
//int main()
//{
//	Stack st;
//	MyQueue mq;//程序结束后自动调用析构函数
//	return 0;
//}