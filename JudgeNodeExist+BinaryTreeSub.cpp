#include<iostream>
#include<assert.h>
using namespace std;

struct BinaryTreeNode
{
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	int _data;
	BinaryTreeNode(const int data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};
class BinaryTree
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree(int* arr,size_t size,int invalid)
	{
		assert(arr);
		size_t index = 0;
		_root=_CreateBinaryTree(arr,size,invalid,index);
	}
	//判断一个节点是否在一棵二叉树中
	bool JudgeNodeExist(Node* pNode)
	{
		return _NodeIsExist(_root,pNode);
	}
	//判断一颗二叉树是是否是另一颗树的子树。比如tree2是tree1的子树
	static bool JudgeSubTree(Node* root1,Node* root2)
	{
		bool result = false;
		if (root1 != NULL && root2 != NULL)
		{
			//先在root1中找与root2相同的根节点，然后再递归到根节点相同的子树中去找
			if (root1->_data == root2->_data)
				result = DoesRoot1HasRoot2(root1,root2);
			if (!result)
				result = DoesRoot1HasRoot2(root1->_left, root2);
			if (!result)
				result = DoesRoot1HasRoot2(root1->_right, root2);
		}
		return result;
	}
	Node* GetRoot()
	{
		return _root;
	}
private:
	bool _NodeIsExist(Node*& root,Node* pNode)
	{
		if (root==NULL || pNode == NULL)
			return false;
		if (pNode->_data == root->_data)
			return true;
		if (_NodeIsExist(root->_left, pNode))   //如果在左子树就已经找到了就不用再在右子树去找了
			return true;
		else
			return _NodeIsExist(root->_right, pNode);
	}
	static bool DoesRoot1HasRoot2(Node* root1, Node* root2)
	{
		if (root1 == NULL)     
			return false;
		if (root2 == NULL)    //如果root2这棵树匹配完了，说明这颗树是子树。
			return true;
		if (root1->_data != root2->_data)
			return false;
		return DoesRoot1HasRoot2(root1->_left, root2->_left) \
			&& DoesRoot1HasRoot2(root1->_right,root2->_right);
	}
	Node* _CreateBinaryTree(int* arr, size_t size, int& invalid, size_t& index)
	{
		Node* root = NULL;
		if (index < size && arr[index] != invalid)
		{
			root = new Node(arr[index]);
			root->_left=_CreateBinaryTree(arr, size, invalid, ++index);
			root->_right=_CreateBinaryTree(arr, size, invalid, ++index);
		}
		return root;
	}
private:
	Node* _root;
};
void test()
{
	int a1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree b1(a1, 10, '#');
	int a2[5] = { 2, 3, '#', '#', 4 };
	BinaryTree b2(a2,5,'#');
	bool ret = BinaryTree::JudgeSubTree(b1.GetRoot(), b2.GetRoot());
	cout << ret << endl;
	bool ret1 = b1.JudgeNodeExist(b1.GetRoot());   //1
	cout << ret1 << endl;
	bool ret2 = b1.JudgeNodeExist(b1.GetRoot()->_left); //2
	cout << ret2 << endl;
	bool ret3 = b1.JudgeNodeExist(b1.GetRoot()->_right);  //5
	cout << ret3 << endl;
	bool ret4 = b1.JudgeNodeExist(b1.GetRoot()->_right->_right);
	cout << ret4 << endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}