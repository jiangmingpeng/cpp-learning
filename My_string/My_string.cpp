#include "My_string.h"
namespace jmp
{
	string::iterator string::begin()
	{
		return _str;
	}

	string::iterator string::end()
	{
		return _str + _size;//表示最后一个有效数据的后一个位置
	}


	string::const_iterator string::begin() const
	{
		return _str;
	}
	string::const_iterator string::end() const
	{
		return _str + _size;//表示最后一个有效数据的后一个位置
	}

	string::string(const char* str )//用户初始化的内容
		:_size(strlen(str))
	{
		_capacity = _size;
		_str = new char[_size+1];//+1为\0腾出一块空间 
		strcpy(_str, str);//char * strcpy ( char * destination, const char * source );
	}

	string::string(const string& s)
		:_size(s._size)
		,_capacity(s._capacity)
	{
		_str = new char[_capacity+1];
		memcpy(_str, s._str, s._size+1);
	}

	void string::swap(string& s)
	{
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}

	string& string::operator=(string s)
	{
		swap(s);
		return *this;
	}

	const char* string::c_str() const
	{
		return _str;//本质是为了调用函数来得到_str的内容 因为正常不能访问私有内容
	}

	string::~string()
	{
		delete[] _str;//匹配使用
		_str = nullptr;
		_size = _capacity = 0;//析构函数的作用不能忘
	}

	size_t string::size() const
	{
		return _size;
	}

	void string::reserve(size_t n)//只放大不缩小
	{
		if (n <= _capacity) return;//只放大不缩小 并不意味着要报错 只是没有强制性；				
		char* new_str = new char[n + 1];//多给一个空间给‘\0’
		if (_str)
		{
			memcpy(new_str, _str, _size + 1); // 拷贝原有内容(包括\0'))
			delete[] _str;
		}
		_str = new_str;//可以采用先移动 再销毁 然后再次指向移动的新位置 从而达到改变this内容的效果
		_capacity = n;

	}

	void string::push_back(char ch)
	{
		if (_size == _capacity)
		{
			size_t _newcapacity = (_capacity == 0 ? 4 : _capacity * 2);
			char* new_str = new char[_newcapacity];
			if (_str) //有字符就得拷贝到新的空间内
			{
				strcpy(new_str, _str); // 拷贝原数据（包括结尾的\0）
				delete[] _str;
			}
			_str = new_str;
			_capacity = _newcapacity;
		}
		_str[_size] = ch;//把\0的位置填上ch
		_str[_size + 1] = '\0';//ch后面把\0加上
		_size++;
	}

	void string::pop_back()
	{
		assert(_size > 0);//删除的话要确保有内容可删 否则断言报错
		_size--;
		_str[_size] = '\0';
	}

	void string::append(const char* str)
	{
		if (str == nullptr) return;//这些都是细节
		size_t len = strlen(str);
		if (len == 0) return;//这些都是细节
		if (_size + len > _capacity)
		{
			size_t new_capacity = (_size + len) * 2;// 或简单_size + len
			char* new_str = new char[new_capacity + 1];//倘若空间不够的问题要记得考虑
			if (_str)
				memcpy(new_str, _str, _size);
			delete[] _str;
			_str = new_str;
			_capacity = new_capacity;
		}
		memcpy(_str + _size, str, len + 1);
		_size += len;
	}

	string& string::operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}
	string& string::operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	string& string::insert(size_t pos, char ch)
	{
		assert(pos <= _size);
		if (_size + 1 > _capacity)
			reserve(_size + 1);
		//memmove(_str + pos + 1,_str + pos,_size - pos + 1);// 后移包括 \0'
		//应该从后往前挪动 否则会造成覆盖
		for (size_t i = _size; i > pos-1; i--)
		{
			_str[i + 1] = _str[i];
		}
		_str[pos] = ch;
		_size++;
		return *this;
	}
	string& string::insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)
			reserve(_size + len + 1);//为\0留空间
		memmove(_str + pos + len, _str + pos, _size - pos + 1);// 后移包括 \0'
		//把_str+pos 后面的所有字符（包括\0） 都从_str + pos + len这个位置开始填充（移动覆盖）
		memcpy(_str + pos, str, len);
		_size+=len;
		return *this;
	}

	size_t string::find(char ch, size_t pos) const
	{
		assert(pos <= _size);
		for (size_t i = pos; i < _size; i++)
		{
			if (_str[i] == ch)
				return i;
		}
		return npos;
	}
	size_t string::find(const char* str, size_t pos)const
	{
		if (str == nullptr) return npos;
		assert(pos <= _size);
		size_t len = strlen(str);
		if (len == 0) return pos;
		if (pos + len > _size) return npos;
		for (size_t i = pos; i <= _size - len; ++i)
		{
			if (strncmp(_str + i, str, len) == 0)//比较前n个字符是否相同
			{
				return i;
			}
		}
		return npos;
	}

	string string::substr(size_t pos, size_t len) const
	{
		assert(pos <= _size);
		size_t count = len;
		if (count == npos || pos + count > _size)
		{
			count = _size - pos;//考虑没有传值或者传值过头的情况 以便正常遍历
		}
		string new_str;
		new_str.reserve(count);
		for (size_t i = 0; i < count; i++)
		{
			new_str += _str[pos+i];
		}
		return new_str;
	}

	string& string::erase(size_t pos, size_t len)
	{
		assert(pos <= _size);
		if (npos == len || pos + len > _size)
		{
			len = _size - pos;
		}
		if (len == 0) return *this;
		memmove(_str + pos, _str + pos + len, _size - pos-len + 1);
		_size -= len;
		return *this;
	}

	void string::clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}


	char& string::operator[](size_t i)
	{
		assert(i < _size);
		return *(_str + i);
	}
	const char& string::operator[](size_t i) const
	{
		assert(i < _size);
		return *(_str + i);
	}
}

bool  jmp::string::operator<(const string& s) const
{
	return strcmp(_str, s._str) < 0;
}
bool jmp::string::operator<=(const string& s) const
{
	return strcmp(_str, s._str) <= 0;

}
bool jmp::string:: operator>(const string& s) const
{
	return strcmp(_str, s._str) > 0;

}
bool jmp::string::operator>=(const string& s) const
{
	return strcmp(_str, s._str) >=0;

}
bool jmp::string::operator==(const string& s) const
{
	return strcmp(_str, s._str) == 0;
}
bool jmp::string::operator!=(const string& s) const
{
	return strcmp(_str, s._str) != 0;
}

ostream& jmp::operator<<(ostream& out, const string& s)
{
	out << s.c_str();//输出就直接输出字符串类型即可
	return out;
}
istream& jmp::operator>>(istream& in, string& s)
{
    // 先清空，然后读入到临时缓冲区，再赋值给 s
    // 简单实现：in >> s._str 不安全。可以用 getline 或临时 string
	char buf[1024];
	in >> buf; // 可能越界
	s = buf;
	return in;
}
istream& jmp::getline(istream& is, string& str, char delim)
{
	str.clear();
	char ch;
	while (is.get(ch))
	{
		if (ch == delim)
		{
			break;
		}
		str.push_back(ch);//每次读取一个字符都尾插上去
	}
	return is;
}

void jmp::swap(string& x, string& y)
{
	x.swap(y);
}




