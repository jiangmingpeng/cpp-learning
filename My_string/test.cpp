#include "My_string.h"
//using namespace std;
namespace jmp
{
	void test01()
	{
		string ch("hahhahaha");//构造和析构没问题
		const string chh("hahhahaha");
		string::const_iterator it2 = chh.begin();//针对有const修饰的类对象迭代器没问题 可以修改迭代器但不能修改迭代器所指向的内容
		string::iterator it1 = ch.begin();//针对没有const修饰的类对象迭代器没问题
		int i = 0;
		char arr[100];
		while (it1 != ch.end())
		{
			arr[i] = *it1;
			it1++;
			i++;
		}
		int n = ch.size();//size没问题
		char const hc = ch[1];//[]没问题
		ch[2] = 'y';//这里的的对于const的直接体现从类对象去看
		/*hc = 'v';*/
	}
	void test02()
	{
		string ch ("shijian bu shi da an");
		//ch = ch;
		string hc = ch;//用ch初始化hc
		string chh ;//用空字符初始化chh
		chh = ch;//调用赋值运算符 给对象赋值
		//chh.reserve(200);//如果发生异地扩容 chh的*str的指向可能发生改变
		chh.push_back('d');
		chh.pop_back();
		string::iterator it = chh.end();
		chh += 'm';
		chh.append("hahhahha");
		chh += "  sbsbbsbsbsbsbssbbss";
		//chh.erase();//显示内容 同样也是以\0为标准
		chh.insert(1,'B');
		chh.insert(0, "AAA");
		int en =chh.find('B');
		chh.erase(1);
	}
	void test03()
	{
		string ch = "shijian444";
		string chh = "shijian 1";
		cout << (ch >= chh) << endl;
		swap(ch, chh);
		ch.swap(chh);//全局和内部都没问题
		cout << ch<<endl;
		string hc = "ssssss";
		getline(cin,hc);
		cout << hc << endl;
		
	}


}
int main()
{
	//jmp::test01();
	//jmp::test02();
	jmp::test03();
	return 0;
}

//int main()
//
//{
//
//	string str("Hello Bit.");
//
//	str.reserve(111);//不会改变字符串的长度 改变的是容量 在vs2019、2022中，string在实现时，当n小于string对象的实际容量时，容量是不会被缩小的
//
//	str.resize(5);
//
//	str.reserve(50);
//
//	cout << str.size() << ":" << str.capacity() << endl;
//
//	return 0;
//
//}

