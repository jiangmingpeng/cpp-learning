#define _CRT_SECURE_NO_WARNINGS
#include "reverse_iterator.h"
#include "My_list.h"

namespace JMP
{
	void test01()
	{
		list<int> ls;
		ls.push_back(1);
		ls.push_back(2);
		ls.push_back(3);
		ls.push_back(4);
		ls.push_back(5);
		std::list<int> cc;
		list<int>::iterator it = ls.begin();
		for (auto e : ls)
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;
		const list<int> ls2(ls);
		list<int>::const_reverse_iterator ti = ls2.rbegin();
		for (auto e : ls2)
		{
			cout << *ti << " ";
			ti++;
			//*ti = +; 指向对象不能被修改
		}
	}
}

int main()
{
	JMP::test01();




	return 0;
}