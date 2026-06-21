#pragma once//在这个基础上进行修改
using namespace std;
template<class K,class V>
struct BSTNode
{
	pair<K,V> _kv;
	BSTNode<K,V>* _left;
	BSTNode<K,V>* _right;

	BSTNode(const pair<K,V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
	{ }
};

// key
template<class K,class V>
class BSTree
{
	typedef BSTNode<K,V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		return true;
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return nullptr;
	}

	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				// 准备删除-----找到了需要删除的 
				if (cur->_left == nullptr)
				{
					if (cur != _root)
					{
						// 左为空，父亲指向我的右
						if (cur == parent->_left)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
					else
					{
						_root = cur->_right;
					}

					delete cur;
				}
				else if (cur->_right == nullptr)
				{
					if (cur != _root)
					{
						// 右为空，父亲指向我的左
						if (cur == parent->_left)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					else
					{
						_root = cur->_left;
					}

					delete cur;
				}
				else
				{
					// 左右都不为空，找子树中适合的节点替代我---这里统一找右子树最小的来替换 然后删除所以要理解后面的操作
					Node* minRightParent = cur;
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						minRightParent = minRight;
						minRight = minRight->_left;
					}

					swap(cur->_kv, minRight->_kv);

					if (minRight == minRightParent->_left)
						minRightParent->_left = minRight->_right;
					else
						minRightParent->_right = minRight->_right;

					delete minRight;
				}

				return true;
			}
		}

		return false;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

private:
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_kv.first << ":"<<root->_kv.second<<" ";
		_InOrder(root->_right);
	}

private:
	Node* _root = nullptr;
};
