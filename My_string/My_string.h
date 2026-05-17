#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>
#include <assert.h>
#include <algorithm>
#pragma once
using namespace std;
namespace jmp
{
	class string
	{
		friend ostream& operator<<(ostream& out, const string& s);
		friend istream& operator>>(istream& in, string& s);
		//friend void swap(string& x, string& y);//调自己String内部的就可以不用友元
	public:
		typedef char* iterator;

		iterator begin();
		iterator end();

		typedef const char* const_iterator;
		const_iterator begin() const;//const 修饰的是 this 所指向的对象内容，使得通过 this 不能修改成员变量
		const_iterator end() const;

		//string();
		string(const char* str = "");
		const char* c_str() const;
		~string();
		string(const string& s);
		string& operator=(string s);
		void swap(string& s);

		size_t size() const;
		char& operator[](size_t i);
		const char& operator[](size_t i) const;
		////已下为新增函数
		void reserve(size_t n);

		void push_back(char ch);
		void pop_back();

		void append(const char* str); 
		string& operator+=(char ch);
		string& operator+=(const char* str);


		string& insert(size_t pos, char ch);
		string& insert(size_t pos, const char* str);
		string& erase(size_t pos = 0, size_t len = npos);

		size_t find(char ch, size_t pos = 0) const; 
		size_t find(const char* str, size_t pos = 0)const;

		string substr(size_t pos, size_t len = npos) const; 
		void clear();

		bool operator<(const string& s) const; 
		bool operator<=(const string& s) const;
		bool operator>(const string& s) const; 
		bool operator>=(const string& s) const;
		bool operator==(const string& s) const; 
		bool operator!=(const string& s) const;
	private:
		char* _str ;
		size_t _size = 0;
		size_t _capacity = 0;

		// _size< 16 串存在buff数组中
		// _size >= 16 串存在_str指向的数组中
		char _buff[16];//
	public:
		static const size_t npos = -1;
	};
	ostream& operator<<(ostream& out, const string& s); 
	istream& operator>>(istream& in, string& s);
	istream& getline(istream& is, string& str, char delim = '\n'); 
	void swap(string& x, string& y);
};
