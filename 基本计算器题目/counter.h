#pragma once
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
//class Solution
//{
//public:
//	int operatorPrecedence(char ch)
//	{
//		struct opPD
//		{
//			char _op;
//			int _pd;
//		};
//		static opPD arr[] = { {'+',1},{'-',1},{'*',2},{'/',2} };//这个运算符优先级比较可以学习一下 这个思想不错
//		for (auto& e : arr)//这个& 加不加都可以 循环里只涉及 比较运算 无关
//		{
//			if (e._op == ch)
//			{
//				return e._pd;
//			}
//		}
//		assert(false);
//		return -1;
//	}
//
//	void toRPN(const string& num, size_t& i,vector<string>& v)//清除哪些地方入栈 哪些地方进入顺序表
//	{
//		stack<char> st;
//
//		while (i<num.size())
//		{
//			if (isdigit(num[i]))
//			{
//				string nums;
//				while (i<num.size()&&isdigit(num[i]))
//				{
//					nums += num[i];
//					++i;
//				}
//				v.push_back(nums);
//			}
//			else if (num[i]=='(')
//			{
//				++i;//判到括号 i要++ 为了到数字那里去 进行接下来的判断
//				toRPN(num, i, v);//括号里面的式子当做子式进行再判断
//			}
//			else if (num[i] == ')')
//			{
//				while (!st.empty())
//				{
//					v.push_back(string(1,st.top()));//这里的把栈中的运算字符取出来
//					st.pop();
//				}//这个操作同样在 全部式子里弄完之后 也要有的 否则可能剩余一些运算符在栈里面没拿出来
//				i++;
//				return;
//			}
//			else
//			{   //这还在循环里面 就不要加循环来遍历了
//				if(st.empty()|| operatorPrecedence(st.top())< operatorPrecedence(num[i]))//看优先级
//				{
//					st.push(num[i]);//当前更大就入栈
//					i++;
//				}
//				else
//				{
//					v.push_back(string(1, st.top()));//更小就先计算里面的 就等同于给他弹出来 
//					st.pop();
//				}
//			}
//		}
//		while (!st.empty())
//		{
//			v.push_back(string(1,st.top()));
//			st.pop();
//		}//与子式一样需要检查栈里面的元素
//	}
//};


class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        for (auto str : tokens)
        { // 遍历每个vector<string>对象
            if (str == "+" || str == "-" || str == "*" ||
                str == "/")
            { // 如果是运算符就直接 开始取运算数开始运算
                long long right = st.top();
                st.pop();
                long long left = st.top();
                st.pop();
                switch (str[0])
                {
                case '+':
                    st.push(left + right);
                    break;
                case '-':
                    st.push(left - right);
                    break;
                case '*':
                    st.push(left * right);
                    break;
                case '/':
                    st.push(left / right);
                    break;
                default:
                    break;
                }
            }
            else
            { // 如果非运算符就入栈 把string转化为整形插入
                st.push(stoll(str));
            }
        }
        return st.top();
    }

    int operatorPrecedence(char ch)
    {
        struct opPD
        {
            char _op;
            int _pd;
        };
        static opPD arr[] = {
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2} }; // 这个运算符优先级比较可以学习一下 这个思想不错
        for (auto& e : arr) // 这个& 加不加都可以 循环里只涉及 比较运算 无关
        {
            if (e._op == ch) {
                return e._pd;
            }
        }
        assert(false);
        return -1;
    }

    void toRPN(const string& s, size_t& i, vector<string>& v) // 明白哪些地方入栈 哪些地方进入顺序表
    {
        stack<char> st;
        while (i < s.size())
        {
            if (isdigit(s[i]))
            {
                string ss;
                while (i < s.size() && isdigit(s[i]))
                {
                    ss += s[i];
                    ++i;
                }
                v.push_back(ss);
            }
            else if (s[i] == '(')
            {
                ++i; // 判到括号 i要++ 为了到数字那里去 进行接下来的判断
                toRPN(s, i, v); // 括号里面的式子当做子式进行再判断
            }
            else if (s[i] == ')')
            {
                while (!st.empty())
                {
                    v.push_back(string(1, st.top())); // 这里的把栈中的运算字符取出来
                    st.pop();
                } // 这个操作同样在 全部式子里弄完之后 也要有的
                  // 否则可能剩余一些运算符在栈里面没拿出来
                i++;
                return;
            }
            else
            { // 这还在循环里面 就不要加循环来遍历了
                if (st.empty() || operatorPrecedence(st.top()) < operatorPrecedence(s[i])) // 看优先级
                {
                    st.push(s[i]); // 当前更大就入栈
                    i++;
                }
                else
                {
                    v.push_back(string(1, st.top())); // 更小就先计算里面的 就等同于给他弹出来
                    st.pop();
                }
            }
        }
        while (!st.empty())
        {
            v.push_back(string(1, st.top()));
            st.pop();
        } // 与子式一样需要检查栈里面的元素
    }

    int calculate(string s)
    {
        string news;
        for (auto ch : s)
        {
            if (ch != ' ')
            {
                news += ch;
            }
        }
        news.swap(s);
        news.clear();
        //交换后的s是没有空格的 后面可以放心操作
        for (size_t i = 0; i < s.size(); i++)
        {
            if (s[i] == '-' && (i == 0 || (!isdigit(s[i - 1]) && s[i - 1] != ')')))//i==0是看开头的负数，后面的括号是判断符号前一位是运算符还是数
            {
                news += "0-";
            }
            else
            {
                news += s[i];
            }
        }
        cout << news << endl;
        size_t i = 0;
        vector<string> v;
        toRPN(news, i, v);//后面用的是新的news来计算的
        return evalRPN(v);
    }
};