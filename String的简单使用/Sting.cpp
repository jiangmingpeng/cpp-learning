#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <list>
using namespace std;
int func1()
{
	return 10;
}
//// 不能做参数
//void func2(auto a)
//{
//}
// 可以做返回值，但是建议谨慎使用
auto func3()
{
	return 3;
}
void Iterator_test1()
{
	char ch[] = "yeah";
	string s = "hallo world";
	string s2(s);
	string s3(s, 1, 30);//取件左闭右开
	string s4(ch);//这里是用指针接收的地址
	string s5(3, 'x');
	//第一种循环方式 通过运算符重载[]来遍历字符串
	for (int i = 0; i < s.size(); i++)
	{
		cout << s[i];
	}
	cout << endl;
	cout << "-------------------" << endl;
	//第二种 通过迭代器进行遍历字符串---各种容器的通用
	string::iterator it = s.begin();
	while (it != s.end())
	{
		//(*it)++;
		cout << (*it);
		++it;
	}
	cout << endl;
	//其他容器示例
	vector<int> v;
	v.push_back(10);
	v.push_back(9);
	v.push_back(8);
	v.push_back(7);
	vector<int>::iterator it2 = v.begin();
	while (it2 != v.end())
	{
		cout << (*it2) << " ";
		++it2;
	}
	cout << endl;
	list<int> lo;
	lo.push_back(1);
	lo.push_back(2);
	lo.push_back(3);
	lo.push_back(4);
	list<int>::iterator it3 = lo.begin();
	while (it3 != lo.end())
	{
		cout << ++(*it3) << " ";//注意这个++的用法前置后置 位置带来的问题
		it3++;
	}
	cout << endl;
	cout << "-------------------" << endl;
	//第三种范围for 的使用
	//先了解auto
	int a = 10;
	auto b = a;
	auto c = 'h';
	auto d = func1();
	// 编译报错:rror C3531: “e”: 类型包含“auto”的符号必须具有初始值设定项
	//auto e;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(d).name() << endl;
	int x = 10;
	auto y = &x;
	auto* z = &x;
	auto& m = x;//取别名的类型不变
	cout << typeid(x).name() << endl;
	cout << typeid(y).name() << endl;
	cout << typeid(z).name() << endl;
	cout << typeid(m).name() << endl;
	auto aa = 1, bb = 2;
	cout << "-------------------" << endl;
	// 编译报错：error C3538: 在声明符列表中，“auto”必须始终推导为同一类型
	//auto cc = 3, dd = 4.0;
	// 编译报错：error C3318: “auto []”: 数组不能具有其中包含“auto”的元素类型
	//auto array[] = { 4, 5, 6 };
	int array[] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++)
	{
		cout << *(array + i) << " ";
	}
	cout << endl;
	for (auto e : array)
	{
		cout << e << " ";
	}
	cout << endl;
	string s6("deng sha sha");
	cout << s6 << endl;
	for (int i = 0; i < s6.size(); i++)
	{
		cout << s6[i];
	}
	cout << endl;
	for (auto ch : s6)//读取s6.size()次s6字符并且执行循环 如果写成了 cout<< s6;那么就会循环输出11次s6
	{
		cout << ch;
	}
	cout << endl;
	cout << "-------------------" << endl;
}
void Capacity_test2()
{
	string acm = "hello world!!";
	string::reverse_iterator it = acm.rbegin();//反向的 要用反向迭代器
	while (it != acm.rend())//反向打印 rbegin 指向的是最后一个++往前走 rend指的是第一个的前一个
	{
		cout << *it;
		it++;
	}
	cout << endl;
	cout << acm.max_size() << endl;
	cout << "size:" << acm.size() << endl;
	int old = acm.capacity();
	cout << old << endl;
	for (int i = 0; i < 100; i++)
	{
		acm += "s";//如果空间还足够加入新的字符 则不会触发capacity函数 相反则不断调用
		if (acm.capacity() != old)
		{
			cout << "capacity:" << acm.capacity() << endl;
		}
		old = acm.capacity();
	}
	cout << endl;
	cout << "capacity:" << acm.capacity() << endl;
	acm.resize(200);//把有效数据个数添加到200个 不够的用空字符填补 也可以自定义字符
	//acm.resize(200,'s');//把有效数据个数添加到200个 不够的用s字符填补 注意这里是字符 不是字符串注意符号
	cout << acm.size() << endl;
	cout << acm << endl;
	acm.reserve(300);//与上一个不同的是这个对capacity起作用 不会改变字符串本身(即有效数据个数) 起到扩大容量的作用
	acm.reserve(100);//同样也可以起到瘦身作用 当然也只是相对瘦身 不会把size弄没
	cout << acm.size() << endl;
	cout << acm.capacity() << endl;
	acm.shrink_to_fit();//让容量减少到与size相适配或者差不多大
	cout << acm << endl;
	acm.clear();//清除字符串 但不改变容量大小
	cout << acm << "jiang" << endl;
	cout << acm.capacity() << endl;
	cout << acm.empty() << endl;//为空为真 相反为假

}
void Elementacc_test3()
{
	string ch = "shasha";//这里存在类型转化 可以激活编译器的优化功能 直接直接构造
	cout << ch[5] << endl;//这里的越界访问会触发报错 程序终止 一般是assert起的作用
	//[]在这里的运算符重载针对String这个类对象的 注意不要忘了运算符重载的应用对象
	cout << ch.at(3) << endl;//这里的越界访问会触发报错 程序终止 是程序抛出异常 
	cout << ch.front() << endl;//分别得到头尾元素
	cout << ch.back() << endl;
}
void Modifiers_test4()
{
	//operator+=
	string ch("dengshasha!!! ");
	string chh = "niubi ";
	string hc(ch);
	//cout << ch.append("nishishabi") << endl;//在字符串后面追加字符
	//cout << ch.append(89,'q') << endl;//在字符串后面追加字符n个一样的
	//cout << ch.append("nihao!",2) << endl;//在字符串后面追加某字符串的前n个，若是远大于则全部加上去
	ch.push_back('9');
	ch.push_back('9');
	ch.push_back('9');
	ch.pop_back();
	//ch.assign("haha\0hahaha");//复制\0前的字符并且覆盖原字符串
	cout << ch << endl;
	//hc.assign("niubi");
	//hc.assign("msde", 1); //复制前n字符并且覆盖原字符串
	//hc.assign(10,'J');
	cout << hc << endl;
	//ch.insert(0,"hahahaha ");//这里的位置是下标
	//ch.insert(0,chh);//这里的位置是下标
	//ch.insert(0, "hahahaha ",1);//第一个位置是下标 第二个是要插入的前n个
	string::iterator it = ch.begin();
	//ch.insert(it, 4, 'J');
	//ch.insert(0, 4, 'J');
	//cout << ch.erase(0,4) << "555" << endl;//从第几个（下标）开始删 删除n个
	ch.replace(0, 1, "jiang");//从第几个（下标）开始 替换哪n（可以是一个换多个）个为 右边的字符串（可以是字符对象） 前两个参数支持迭代器
	ch.replace(0, 1, 6, 'J');//从第几个（下标）开始 替换哪n（可以是一个换多个）个为 n 个什么东西
}
void Stringoperations_test5()
{
	string ch = "dengshasha!!!";
	string chh = "zhouyunyan";
	string chhh = "zhou";
	char  hs[10] = "\0";//不初始化会有随机值或者是乱码
	////const char* chh = ch.c_str();//转化成c风格的字符串
	//cout << chh << endl;
	//cout << ch.data() << endl;//得到和原字符对象相同的char*
	//int  qp = chh.copy(hs, 5, 0);//从第n个位置开始返回拷贝的长度 把chh中的值 拷贝进入hs--- 功能要清楚 
	//cout << qp << endl;
	//cout << hs << endl;
	//cout << chh.find(chhh, 0)<<endl;//找到了就返回目的字符的第一个位置 没有就返回一个很大的值
	//cout << chh.find("yan", 0) << endl;//可以指定字符串
	//cout << chh.find('a', 0) << endl;//可以指定字符查找
	//cout << chh.find("yan", 0,3) << endl;//可以查找到第几位(这里的第几位是指目标值的第几位 不是被查找的第几位) 但是只支持字符串
	//cout << chh.rfind("yan") << endl;//倒着找字符串
	//cout << chh.rfind(chhh) << endl;//倒着找字符对象
	//cout << chh.rfind("yan",1000,0) << endl;//倒着查找 目标字符中的前n个字符 找到返回第一个位置 否则返回大值
	//int a = ch.find_first_of("deng",5);//还有其他三个道理类似用的也不多就不写了 忘了就看文档
	//cout << a << endl;
	//cout << chh.substr(0,4) << endl;//在某个字符串中创建子字符串 从第几个位置 要弄几个字符
	cout << chh.compare(ch) << endl;
	cout << chh.compare( 0, 4,chhh) << endl;//=0 这表示从第几个比较到第几个是否相等
	//返回值大于0要么第一个不匹配字符的值在被比较的字符串中更大，要么所有比较的字符都匹配，但被比较的字符串更长。
	//返回值小于0则相反 等于0则相等
}
void test6()
{
	
}
#include <iostream>
#include <string>

int main()
{
	//Iteratort_est1();
//	//Capacity_test2();
//	//Elementacc_test3();
//	//Modifiers_test4();
//	//Stringoperations_test5();
	std::string name;

	std::cout << "Please, enter your full name: ";
	std::getline(std::cin, name);
	std::cout << "Hello, " << name << "!\n";

	return 0;
}