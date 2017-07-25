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
class BinaryTree
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree(const int* arr,size_t size,int invalid)
	{
		assert(arr);
		size_t index = 0;
		_root=_CreateBinaryTree(arr,size,invalid,index);
	}
	size_t BinaryTreeHeight()
	{
		return _BinaryTreeHeight(_root);
	}
	~BinaryTree()
	{
		_DestoryTree(_root);
	}
private:
	Node* _CreateBinaryTree(const int* arr, size_t size, int& invalid, size_t index)
	{
		Node* root = NULL;
		if (index < size && arr[index]!=invalid)
		{
			root = new Node(arr[index]);
			root->_left = _CreateBinaryTree(arr, size, invalid, ++index);  //递归创建左子树
			root->_right = _CreateBinaryTree(arr, size, invalid, ++index);  //递归创建右子树
		}
		return root;
	}
	size_t  _BinaryTreeHeight(Node* root)
	{
		if (root == NULL)
			return 0;
		size_t LeftHeight=_BinaryTreeHeight(root->_left);
		size_t RightHeight = _BinaryTreeHeight(root->_right);
		return LeftHeight > RightHeight ? LeftHeight + 1 : RightHeight + 1;
	}
	void _DestoryTree(Node*& root)
	{
		if (root == NULL)
			return;
		_DestoryTree(root->_left);
		_DestoryTree(root->_right);
		delete root;
		root = NULL;
	}
private:
	Node* _root;
};
void Test1()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree b1(a, 10, '#');
	cout << "该二叉树高度："<<b1.BinaryTreeHeight() << endl;;
}
//int main()
//{
//	Test1();
//	system("pause");
//	return 0;
//}

namespace ObjList
{
	struct ListNode
	{
		ListNode* _next;
		int _data;
		ListNode(int data)
			:_next(NULL)
			, _data(data)
		{}
	};
	typedef ListNode Node;
	//给出一个链表和一个数k，比如链表1→2→3→4→5→6，k=2，翻转后2→1→4→3→6→5
	//若k=3,翻转后3→2→1→6→5→4，若k=4，翻转后4→3→2→1→5→6
	//可见，这是链表的部分逆置，满足一个k的逆置，不满足一个k的链在后面即可
	Node* RotateList(Node* head,size_t k)
	{
		if (head == NULL || k <=1 )
			return head;

		Node* cur = head;
		Node* NewHead = NULL;  //指向逆置后的头节点
		Node* PartTail = head;  //最后指向部分逆置的尾节点
		for (size_t i = 0; i < k; ++i)  //这里不可用while(k--)，因为下次递归进来的时候k值就变了
		{
			if (PartTail)
				PartTail = PartTail->_next;
			else
				return head;
		}
		Node* NextPartTail = RotateList(PartTail,k);  //进行下一次分组
		Node* tmp = NULL;
		while (cur!=PartTail)
		{
			tmp = cur;
			cur = cur->_next;
			if (NewHead == NULL)      //头插tmp
				tmp->_next = NextPartTail;
			else
				tmp->_next = NewHead;

			NewHead = tmp;
		}
		return NewHead;
	}
	
	void PrintList(Node* head)
	{
		if (head == NULL)
			return;
		Node* cur = head;
		while (cur)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
	void Test()
	{
		Node* p1 = new Node(1);
		Node* p2 = new Node(2);
		Node* p3 = new Node(3);
		Node* p4 = new Node(4);
		Node* p5 = new Node(5);
		Node* p6 = new Node(6);
		p1->_next = p2;
		p2->_next = p3;
		p3->_next = p4;
		p4->_next = p5;
		p5->_next = p6;
		PrintList(p1);
		//Node* ret1=RotateList(p1,2);
		//PrintList(ret1);
		Node* ret2 = RotateList(p1, 3);
		PrintList(ret2);
		//Node* ret3 = RotateList2(p1, 4);
		//PrintList(ret3);
	}
}
int main()
{
	ObjList::Test();
	system("pause");
	return 0;
}
