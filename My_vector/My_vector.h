#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

namespace jmp
{
	template <class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin()
		{
			return _start;
		}
		const_iterator begin() const
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator end() const
		{
			return _finish;
		}

		const_iterator cbegin() const
		{
			return _start;
		}

		const_iterator cend() const
		{
			return _finish;
		}
		// construct and destroy------注意浅拷贝和深拷贝 更有利于理解底层
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{

		}
		vector(int n, const T& value = T())
			: _start(nullptr)//初始化列表是好习惯
			, _finish(nullptr)//写了是为了更严谨，尤其是当成员在初始化列表中能直接构造时，效率更高；也避免了某些成员（如引用）无法在函数体内赋值的情况
			, _endOfStorage(nullptr)//不论这里写不写 初始化列表总是要走的 写了代码健壮性更高
		{
			T* vec = new T[n];
			for (size_t i = 0; i < n; i++)
			{
				vec[i] = value;
			}
			_start = vec;
			_finish = vec + n;
			_endOfStorage = vec + n;
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			size_t n = last - first;
			T* vec = new T[n];
			size_t i = 0;
			while (first != last)
			{
				vec[i] = *first;
				first++;
				i++;
			}
			_start = vec;
			_finish = vec + n;
			_endOfStorage = vec + n;
		}
		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			size_t n = v.size();
			T* vec = new T[n];
			for (size_t i = 0; i < v.size(); i++)
			{
				vec[i] = v[i];
			}
			_start = vec;
			_finish = vec + n;
			_endOfStorage = vec + n;
		}
		vector<T>& operator= (vector<T> v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endOfStorage, v._endOfStorage);
			return *this;
		}
		~vector()
		{
			delete[] _start;//下面两个之所以不用delete是因为他们三指向的是同一块空间 是释放一次即可
			_start = nullptr;
			_finish = nullptr;
			_endOfStorage = nullptr; //释放后立即置空是防止“重复释放野指针”的好习惯
		}

		// capacity
		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _endOfStorage - _start;
		}
		//void reserve(size_t n)//只放大 不缩小
		//{
		//	if (n <= capacity()) return;
		//	size_t si = size();
		//	T* New_vec = new T[n];
		//	memcpy(New_vec, _start, si);//这里只进行了浅拷贝 虽然开辟了新内存可以存储成员变量 ，
		//	//但是一旦出现非pod数据 里面的 指针变量的指向还会是原来的空间 可能导致后面对同一块空间释放两次 导致报错
		//	delete[] _start;
		//	_start = New_vec;
		//	_finish = New_vec + si;
		//	_endOfStorage = New_vec + n;
		//}
		void reserve(size_t n)//只放大 不缩小
		{
			if (n <= capacity()) return;
			size_t si = size();
			//T* New_vec = new T[n];
			T* New_vec = static_cast<T*>(::operator new(n * sizeof(T))); // 分配原始内存
			for (size_t i = 0; i < si; ++i) 
			{
				new (New_vec + i) T(std::move(_start[i])); // placement new 移动构造
			}
			// 销毁旧对象
			for (size_t i = 0; i < si; ++i) 
			{
				_start[i].~T();
			}
			::operator delete(_start); // 释放旧内存
			_start = New_vec;
			_finish = New_vec + si;
			_endOfStorage = New_vec + n;
		}
		void resize(size_t n, const T& value = T())
		{
			if (n < size()) 
			{
				// 析构多余元素
				for (size_t i = n; i < size(); ++i) 
				{
					_start[i].~T();
				}
				_finish = _start + n;
			}
			else if (n > size()) 
			{
				if (n > capacity()) 
				{
					reserve(n);// 扩容（会移动旧元素，更新 _start, _finish, _endOfStorage）
					//有现成的扩容直接用
				}
				// 构造新增元素
				for (size_t i = size(); i < n; ++i) 
				{
					new (_start + i) T(value);
				}
				_finish = _start + n;
			}
		}
		///////////////access///////////////////////////////
		T& operator[](size_t pos)
		{
			assert(pos>=size());
			return *(_start + pos);
		}
		const T& operator[](size_t pos)const
		{
			assert(pos >= size());
			return *(_start + pos);
		}
		///////////////modify/////////////////////////////
		//void push_back(const T& x)
		//{
		//	if (size() + 1 >= capacity())
		//	{
		//		size_t  old_size = size();
		//		size_t new_capacity = (capacity() == 0 ? 4 : capacity() * 2);
		//		T* new_arr = new T[new_capacity];
		//		//memcpy(new_arr, _start, sizeof(T)* old_size);
		//		for (size_t i = 0; i < old_size; ++i)
		//		{
		//			new_arr[i] = _start[i];
		//		}
		//		delete[] _start;
		//		_start = new_arr;
		//		_finish = new_arr+ old_size;
		//		_endOfStorage= new_arr+ new_capacity;
		//	}
		//	*(_finish) = x;
		//	_finish++;
		//}
		void push_back(const T& x)
		{
			if (size() + 1 >= capacity())
			{
				size_t new_capacity = (capacity() == 0 ? 4 : capacity() * 2);
				reserve(new_capacity);
			}
			*(_finish) = x;
			_finish++;
		}
		bool empty()
		{
			if (size() == 0) return true;
			return false;  //这个返回值不要忘了 条件发生与不发生
		}
		void pop_back()
		{
			assert(!empty());
			--_finish;
			_finish->~T();
		}
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endOfStorage, v._endOfStorage);
		}
		iterator insert(iterator pos, const T& x)//既然给的是迭代器 那我传为下标不就可以了 
		{
			if (size() + 1 >= capacity())
			{
				size_t new_capacity = (capacity() == 0 ? 4 : capacity() * 2);
				reserve(new_capacity);
			}
			size_t index = pos - _start;//如果pos是指向下标为三的元素 那么-pos之后是下标为3的位置 所以符合转化要求
			for (size_t i = size(); i > index; --i)//往前移动还是往后移动 要清楚
			{
				_start[i] = _start[i - 1];
			}
			*(_start+index) = x;//size不用管因为有人给计算出来
			_finish++;
			return _start + index;
		}
		iterator erase(iterator pos)
		{
			assert(!empty());
			size_t index = pos - _start;
			for (size_t i = index;i < size()-1; ++i)
			{
				_start[i] = _start[i+1];
			}
			_finish--;
			_start[size() - 1].~T();   // 析构被“删除”的元素//优化环境下平凡析构不会被调用 断点直接失效 在非优化下则会生效
			return _start + index;
		}
	private:
		iterator _start; // 指向数据块的开始
		iterator _finish; // 指向有效数据的尾
		iterator _endOfStorage; // 指向存储容量的尾
	};

};