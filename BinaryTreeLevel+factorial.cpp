#include<iostream>
using namespace std;

//1.��N�Ľ׳˽��ĩβ�м���0
int GetZeroOfFactorial1(int N)
{
	if (N == 0 || N == 1)
		return 1;
	int count = 0;
	for (int i = 1; i <= N; ++i)
	{
		int j = i;
		while (j % 5 == 0)
		{
			count++;
			j /= 5;
		}
	}
	return count;
}
int GetZeroOfFactorial2(int N)
{
	if (N == 0 || N == 1)
		return 1;
	int count = 0;
	while (N)
	{
		count += (N / 5);
		N /= 5;
	}
	return count;
}
int GetZeroOfFactorial3(int N)
{
	//�������̫��ͻ�洢���£���ô���ǿ��Ը���һ����׼ֵ���������ֵ��ֻ����ǰ��λ
	if (N == 0 || N == 1)
		return 1;

	const int Max = 1000000;
	int count = 0;
	int sum = 1;
	for (int i = N; i >= 1; --i)
	{
		sum *= i;
		while (sum % 10 == 0)   //ͳ��0�ĸ���
		{
			sum /= 10;
			count++;
		}
		if (sum >= Max)    //����׳��Ѿ����ڹ涨�����ֵ��ֻ�����λ
		{
			sum %= Max;
		}
	}
	while (sum % 10 == 0)
	{
		sum /= 10;
		count++;
	}
	return count;
}
//int main()
//{
//	//int ret=GetZeroOfFactorial1(5);
//	//int ret = GetZeroOfFactorial2(5);
//	//int ret = GetZeroOfFactorial2(13);
//	//int ret = GetZeroOfFactorial3(5);
//	//int ret = GetZeroOfFactorial3(11);
//	int ret = GetZeroOfFactorial1(13);
//	cout << ret << endl;
//	system("pause");
//	return 0;
//}

#include<assert.h>
#include<queue>
//2.�������Ĳ������
struct BinaryTreeNode
{
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	int _key;
	BinaryTreeNode(const int& key)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
	{}
};
class BinaryTree
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree(const int* arr, size_t size, const int& invalid)
	{
		assert(arr);
		size_t index = 0;
		_root = _CreateBinaryTree(arr, size, invalid, index);
	}
	void LevelOrder()
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		queue<Node*> q;
		q.push(cur);
		while (!q.empty())
		{
			cur = q.front();
			cout << cur->_key << " ";
			q.pop();
			if (cur->_left)
				q.push(cur->_left);
			if (cur->_right)
				q.push(cur->_right);
		}
		cout << endl;
	}
private:
	Node* _CreateBinaryTree(const int* arr, size_t size, const int& invalid, size_t& index)
	{
		Node* root = NULL;  //�������ĸ��ڵ�
		if (index < size && arr[index] != invalid)
		{
			root= new Node(arr[index]);
			root->_left = _CreateBinaryTree(arr, size, invalid, ++index);  //����������
			root->_right = _CreateBinaryTree(arr, size, invalid, ++index); //����������
		}
		return root;
	}
private:
	Node* _root;
};

void test()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree b1(a, 10, '#');
	cout << "����" << endl;
	b1.LevelOrder();
}
int main()
{
	test();
	system("pause");
	return 0;
}