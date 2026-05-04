#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
//-----内存分布-----
//using namespace std;
//int globalVar = 1;//静态区
//static int staticGlobalVar = 1;//静态区
//void Test()
//{
//	static int staticVar = 1;//静态区
//	int localVar = 1;//栈
//	int num1[10] = { 1, 2, 3, 4 };//栈
//	char char2[] = "abcd";//char--栈 *char--栈--局部变量的首元素
//	const char* pChar3 = "abcd";//pChar--栈 *pChar--常量区--解引用为常量区的首元素
//	int* ptr1 = (int*)malloc(sizeof(int) * 4);//ptr--栈 *ptr--堆
//	int* ptr2 = (int*)calloc(4, sizeof(int));
//	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
//	free(ptr1);
//	free(ptr3);
//}
// 
//-----C++的动态内存管理-----内置类型
//void Test()
//{
//	// 动态申请一个int类型的空间
//	int* ptr4 = new int;
//	// 动态申请一个int类型的空间并初始化为10
//	int* ptr5 = new int(10);//这里的初始化是通过对象里面的构造函数实现的
//	// 动态申请10个int类型的空间
//	int* ptr6 = new int[10];
//	// 动态申请10个int类型的空间,并进行初始化
//	int* ptr7 = new int[10] {1, 2, 3, 4, 5, 6};//没有填的自动初始化为0
//	delete ptr4;
//	delete ptr5;
//	delete[] ptr6;
//	delete[] ptr7;
//}
//int main()
//{
//	Test();
//	return 0;
//}

//---new和delete操作自定义类型---
//using namespace std;
//class A
//{
//public:
//	A(int a = 0)
//		: _a(a)
//	{
//		cout << "A():" << this << endl;
//	}
//	~A()
//	{
//		cout << "~A():" << this << endl;
//	}
//private:
//		int _a;
//};
//int main()
//{
//	// new/delete 和 malloc/free最大区别是 new/delete对于【自定义类型】除了开空间
//	//还会调用构造函数和析构函数
//	A* p1 = (A*)malloc(sizeof(A));
//	A* p2 = new A(1);//会调用构造函数
//	free(p1);
//	delete p2;//会调用析构函数
//	// 内置类型是几乎是一样的
//	//int* p3 = (int*)malloc(sizeof(int)); // C
//	//int* p4 = new int;
//	//free(p3);
//	//delete p4;
//	A* p5 = (A*)malloc(sizeof(A) * 10);
//	A* p6 = new A[10];
//	free(p5);
//	delete[] p6;
//	return 0;
//}

//----operator new与operator delete函数----
//new和delete是用户进行动态内存申请和释放的操作符，operator new 和operator delete是
//系统提供的全局函数，new在底层调用operator new全局函数来申请空间，delete在底层通过
//operator delete全局函数来释放空间。
using namespace std;
//new和delete是用户进行动态内存申请和释放的操作符，operator new 和operator delete是
//系统提供的全局函数，new在底层调用operator new全局函数来申请空间，delete在底层通过
//operator delete全局函数来释放空间。

/*
operator new：该函数实际通过malloc来申请空间，当malloc申请空间成功时直接返回；申请空间
失败，尝试执行空间不足应对措施，如果改应对措施用户设置了，则继续申请，否则抛异常。
*/
//
//void* __CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc)
//{
//	// try to allocate size bytes
//	void* p;
//	while ((p = malloc(size)) == 0)
//		if (_callnewh(size) == 0)
//		{
//			// report no memory
//			// 如果申请内存失败了，这里会抛出bad_alloc 类型异常
//			static const std::bad_alloc nomem;
//			_RAISE(nomem);
//		}
//		return (p);
//}
///*
//operator delete: 该函数最终是通过free来释放空间的
//*/
//void operator delete(void* pUserData)
//{
//	_CrtMemBlockHeader* pHead;
//	RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
//	if (pUserData == NULL)
//		return;
//	_mlock(_HEAP_LOCK);  /* block other threads */
//	__TRY
//		        /* get a pointer to memory block header */
//		pHead = pHdr(pUserData);
//	         /* verify block type */
//	_ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
//	_free_dbg(pUserData, pHead->nBlockUse);
//	__FINALLY
//		_munlock(_HEAP_LOCK);  /* release other threads */
//	__END_TRY_FINALLY
//		return;
//}
///*
//free的实现
//*/
//#define   free(p)               _free_dbg(p, _NORMAL_BLOCK)

//------new和delete的实现----
//----定位new表达式(placement-new)----
//malloc/free和new/delete 的区别




