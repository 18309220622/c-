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
				return false;   //����ֵ�Ѿ�����
		}
		//����ѭ������ҵ�һ����λ��׼������
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
	//����������ת��Ϊ˫������
	Node* TreeToList()
	{
		Node* HeadOfList = _root;
		Node* LastNodeOfList = NULL;
		Convert(_root,LastNodeOfList);
		while (HeadOfList && HeadOfList->_left)
		{
			HeadOfList = HeadOfList->_left;
		}
		return HeadOfList;     //�����ͷ��㼴Ϊ����������������ڵ�
	}
	void PrintDoubleList(Node *ListHead)//��ӡ��˫������
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
			LastNodeOfList->_right = cur;   //����˫������
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


//��Ч�ĵ���ģʽ
#include<mutex>
#include<windows.h>
//�����������������RAII����д��AutoLock��������Դ
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
	mutex& _mtx;  //���������Ƕ��������һ������������������һ�ݿ��������������ã�
	              //��Σ���������ʱ��ı����ڲ������ü��������Բ�Ӧ��const
};
//����ģʽ
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
				MemoryBarrier();    //�����ڴ�դ������ֹCPU�Ż�ִ��˳��
				_inst = tmp;
			}
			//_mt.unlock();
		}
		return _inst;
	}
protected:
	Singleton(const Singleton& s);  //����������
private:
	Singleton()
	{}
	static Singleton* _inst;
	static mutex _mt;
};
Singleton* Singleton::_inst=0;
mutex Singleton::_mt;

//����ģʽ
//1.���þ�̬��Ա�����ĳ�ʼ���ڵ�main����֮ǰ������ʵ��
#include<assert.h>
class Singleton
{
public:
	static Singleton* GetInst()   //��main���������֮ǰ�Ѿ��������˶���
	{
		assert(_inst);
		return _inst;
	}
protected:
	Singleton(const Singleton& s);  //����������
private:
	Singleton()
	{}
	static Singleton* _inst;
};
Singleton* Singleton::_inst = new Singleton();

//2.��ʱ�Ŵ�������
class Singleton
{
public:
	static Singleton* GetInst()   
	{
		static Singleton inst;
		return &inst;
	}
protected:
	Singleton(const Singleton& s);  //����������
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

//��1������ģʽ��Ҫ�����̰߳�ȫ��������ָ���Ż�������

//��2������ģʽһ�����þ�̬��Ա������ʼ�����ڵ�main����֮ǰ������ʵ��
//�����ڻ�ȡ��ʵ��ʱ����ʱ�����������ַ�ʽû�м�����û��˫�ؼ�飬Ҳ���ÿ����쳣������ɵ��ڴ�й©��

//��3������ģʽ������ȱ������ģʽ���ʺ϶�̬������������̬�����ǽ����ӿⶼ���ص���Ŀ�������
//����ģʽ����������⣬���Ƕ�̬���������������Ž������ļ����ؽ�����
//�����ö���ģʽ���ܶ���ĳ�ʼ����������⡣