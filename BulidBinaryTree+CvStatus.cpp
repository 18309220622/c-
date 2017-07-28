#include<iostream>
#include<assert.h>
using namespace std;

struct TreeNode
{
	int _data;
	TreeNode* _left;
	TreeNode* _right;
	TreeNode(int data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};
class BinaryTree
{
	typedef TreeNode Node;
public:
	BinaryTree(int* prevArr, int* InArr, int length)
	{
		_ReBulidBinaryTree(_root,prevArr,InArr,length);
	}
	void PrevOrder()
	{
		_PreVOrder(_root);
		cout << endl;
	}
private:
	void _ReBulidBinaryTree(Node*& root,int* prevArr,int* InArr,int length)
	{
		if (prevArr == NULL || InArr == NULL || length <= 0)
			return ;
		root = new Node(prevArr[0]);    //ǰ������ĵ�һ���ڵ�������ĸ��ڵ�
		int index = 0;
		for (; index < length; ++index)
		{
			if (InArr[index] == prevArr[0])
				break;
		}
		//��ʱindex��ָ����������ĸ��ڵ㴦
		int leftSub = index;   //�����������Ľڵ�����index��0��ʼ����ָ����ڵ㣬��ô�ڴ�ǰ��ĸ��������������ڵ�����
		int rightSub = length - index-1;
		_ReBulidBinaryTree(root->_left, prevArr + 1, InArr,leftSub);  //�ݹ鴴��������
		_ReBulidBinaryTree(root->_right, prevArr +index+1 ,InArr+index+1, rightSub);
	}
	void _PreVOrder(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		_PreVOrder(root->_left);
		_PreVOrder(root->_right);
	}
private:
	Node* _root;
};

//int main()
//{
//	int PrevOrder[] = { 1, 2, 3, 4, 5, 6 };
//	int InOrder[] = { 3, 2, 4, 1, 6, 5 };
//	BinaryTree b(PrevOrder, InOrder, 6);
//	b.PrevOrder();
//	system("pause");
//	return 0;
//}


namespace ObjC_multiModal
{
	typedef void (*FUNC)();   //����һ������ָ��
	void F_A()
	{
		cout << "A::F_A()" << endl;
	}
	void F_B()
	{
		cout << "B::F_B()" << endl;
	}
	struct A
	{
		FUNC f;
		int _a;
	};
	struct B
	{
		struct A _cb;
		int _b;
	};

	void Fun(A* ptr)
	{
		ptr->f();
	}
}
int main()
{
	ObjC_multiModal::A aa;
	ObjC_multiModal::B bb;
	aa.f = ObjC_multiModal::F_A;    //�Ƚ��к���ָ��ĳ�ʼ��
	bb._cb.f = ObjC_multiModal::F_B;
	ObjC_multiModal::A* ptr = &aa;
	ptr->f();                   //ptrָ���࣬�͵�����ĺ���
	ObjC_multiModal::Fun(&aa);

	ptr = (ObjC_multiModal::A*)&bb;
	ptr->f();                   //ptrָ�����࣬�͵�����ĺ���
	ObjC_multiModal::Fun((ObjC_multiModal::A*)&bb);
	system("pause");
	return 0;
}
