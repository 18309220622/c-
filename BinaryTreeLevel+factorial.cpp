#include<iostream>
using namespace std;

//1.求N的阶乘结果末尾有几个0
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
	//如果数据太大就会存储不下，那么我们可以给出一个标准值，超过这个值就只储存前几位
	if (N == 0 || N == 1)
		return 1;

	const int Max = 1000000;
	int count = 0;
	int sum = 1;
	for (int i = N; i >= 1; --i)
	{
		sum *= i;
		while (sum % 10 == 0)   //统计0的个数
		{
			sum /= 10;
			count++;
		}
		if (sum >= Max)    //如果阶乘已经大于规定的最大值就只储存后几位
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
//2.二叉树的层序遍历
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
		Node* root = NULL;  //二叉树的根节点
		if (index < size && arr[index] != invalid)
		{
			root= new Node(arr[index]);
			root->_left = _CreateBinaryTree(arr, size, invalid, ++index);  //创建左子树
			root->_right = _CreateBinaryTree(arr, size, invalid, ++index); //创建右子树
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
	cout << "层序：" << endl;
	b1.LevelOrder();
}
int main()
{
	test();
	system("pause");
	return 0;
}