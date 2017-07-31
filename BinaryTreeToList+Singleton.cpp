#include<iostream>
#include<assert.h>
using namespace std;

struct BinaryTreeNode
{
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	int _data;
	BinaryTreeNode(int data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};
class SearchBinaryTree
{
	typedef BinaryTreeNode Node;
public:
	SearchBinaryTree(int* a, size_t size)
		:_root(NULL)
	{
		assert(a);
		for (size_t i = 0; i<size; ++i)
		{
			Insert(a[i]);
		}
	}
	bool Insert(const int data)
	{
		if (_root == NULL)
		{
			_root = new Node(data);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_data > data)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_data < data)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;   //该数值已经存在
		}
		//出了循环后就找到一个空位置准备插入
		cur = new Node(data); 
		if (parent->_data > data)
		{
			parent->_left = cur;
			return true;
		}	
		if (parent->_data < data)
		{
			parent->_right = cur;
			return true;
		}
		else
			return false;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	//二叉搜索树转化为双向链表
	Node* TreeToList()
	{
		Node* HeadOfList = _root;
		Node* LastNodeOfList = NULL;
		Convert(_root,LastNodeOfList);
		while (HeadOfList && HeadOfList->_left)
		{
			HeadOfList = HeadOfList->_left;
		}
		return HeadOfList;     //链表的头结点即为二叉搜索树的最左节点
	}
	void PrintDoubleList(Node *ListHead)//打印出双向链表
	{
		Node* ptr = ListHead;
		cout << "Visit the double list from left" << endl;
		for (; ptr; ptr = ptr->_right)
			cout<< ptr->_data<<" "; 
		cout << endl;
		
		/*cout<<"Visit the double list from right"<<endl;
		for (ptr = ListTail; ptr; ptr = ptr->_left)
			cout<<ptr->_data;
		cout << endl;*/
	}
private:
	void Convert(Node* root, Node*& LastNodeOfList)
	{
		if (root == NULL)
			return;
		Node* cur = root;
		if (cur->_left)
			Convert(root->_left, LastNodeOfList);
		cur->_left = LastNodeOfList;
		if (LastNodeOfList)
			LastNodeOfList->_right = cur;   //构成双向链表
		LastNodeOfList = cur;
		if (cur->_right)
			Convert(root->_right, LastNodeOfList);
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
private:
	Node* _root;
};

void Test()
{
	int arr[10] = { 5, 2, 4, 6, 9, 0, 3, 7, 8, 1 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	SearchBinaryTree t(arr, sz);
	t.InOrder();
	t.PrintDoubleList(t.TreeToList());
}
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}


//高效的单例模式
#include<mutex>
#include<windows.h>
//避免产生死锁，根据RAII机制写出AutoLock来回收资源
class AutoLock
{
public:
	AutoLock(mutex& mtx)
		:_mtx(mtx)
	{
		_mtx.lock();
	}
	~AutoLock()
	{
		_mtx.unlock();
	}
private:
	mutex& _mtx;  //加锁解锁是对锁本身的一个操作，而不是它的一份拷贝，所以用引用；
	              //其次，加锁解锁时会改变其内部的引用计数，所以不应加const
};
//懒汉模式
class Singleton
{
public:
	static Singleton* GetInst()
	{
		if (_inst == NULL)
		{
			//_mt.lock();
			AutoLock lock(_mt);
			if (_inst == NULL)
			{
				Singleton* tmp = new Singleton();
				MemoryBarrier();    //加入内存栅栏，防止CPU优化执行顺序
				_inst = tmp;
			}
			//_mt.unlock();
		}
		return _inst;
	}
protected:
	Singleton(const Singleton& s);  //防拷贝构造
private:
	Singleton()
	{}
	static Singleton* _inst;
	static mutex _mt;
};
Singleton* Singleton::_inst=0;
mutex Singleton::_mt;

//饿汉模式
//1.利用静态成员函数的初始化在调main函数之前的性质实现
#include<assert.h>
class Singleton
{
public:
	static Singleton* GetInst()   //在main调这个函数之前已经创建好了对象
	{
		assert(_inst);
		return _inst;
	}
protected:
	Singleton(const Singleton& s);  //防拷贝构造
private:
	Singleton()
	{}
	static Singleton* _inst;
};
Singleton* Singleton::_inst = new Singleton();

//2.临时才创建对象
class Singleton
{
public:
	static Singleton* GetInst()   
	{
		static Singleton inst;
		return &inst;
	}
protected:
	Singleton(const Singleton& s);  //防拷贝构造
private:
	Singleton()
	{}
};
int main()
{
	Singleton::GetInst();
	system("pause");
	return 0;
}

//（1）懒汉模式需要考虑线程安全，死锁，指令优化等问题

//（2）饿汉模式一是利用静态成员变量初始化是在调main函数之前的特性实现
//二是在获取该实例时才临时创建，这两种方式没有加锁，没有双重检查，也不用考虑异常捕获造成的内存泄漏。

//（3）两种模式各有优缺，饿汉模式不适合动态联编的情况，静态编译是将链接库都加载到该目标代码中
//饿汉模式不会存在问题，但是动态编译是运行起来才将链接文件加载进来，
//这会儿用饿汉模式可能对象的初始化会存在问题。