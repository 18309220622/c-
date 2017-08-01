#include<iostream>
#include<assert.h>
#include<queue>
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
typedef BinaryTreeNode Node;
bool JudgeIsCompleteBinary(Node* root)
{
	if (root == NULL)
		return false;
	queue<Node*> q;
	Node* cur = root;
	q.push(cur);
	while (!q.empty())
	{
		Node* Front = q.front();
		if (Front->_left && Front->_right)  //����ڵ�����Һ��Ӿ����ڣ���ô�ͽ��ýڵ�pop,���ҽ��������Һ��������
		{
			q.pop();
			q.push(Front->_left);
			q.push(Front->_right);
		}
		if (Front->_left == NULL && Front->_right)
			return false;
		if ((Front->_left && Front->_right == NULL) || (Front->_left == NULL && Front->_right == NULL))
		{
			//��Ҫ���������ж�
			q.pop();  //��pop��Top�ڵ�
			while (!q.empty())
			{
				Node* front = q.front();
				if (front->_left == NULL && front->_right == NULL)
					q.pop();
				else
					return false;
			}
				return true;
		}
	}
}
	//       1
	//   2       3
	// 4    5  6   7
void Test1()
{
	Node* root1 = new Node(1);
	Node* root2 = new Node(2);
	Node* root3 = new Node(3);
	Node* root4 = new Node(4);
	Node* root5 = new Node(5);
	Node* root6 = new Node(6);
	Node* root7 = new Node(7);
	root1->_left = root2;
	root1->_right = root3;
	root2->_left = root4;
	root2->_right = root5;
	root3->_left = root6;
	root3->_right = root7;
	cout << JudgeIsCompleteBinary(root1) << endl;
}
//       1
//   2       3
// 4    5       6
void Test2()
{
	Node* root1 = new Node(1);
	Node* root2 = new Node(2);
	Node* root3 = new Node(3);
	Node* root4 = new Node(4);
	Node* root5 = new Node(5);
	Node* root6 = new Node(6);
	root1->_left = root2;
	root1->_right = root3;
	root2->_left = root4;
	root2->_right = root5;
	root3->_right = root6;
	cout << JudgeIsCompleteBinary(root1) << endl;
}

//       1
//    2     3
// 4    5   
void Test3()
{
	Node* root1 = new Node(1);
	Node* root2 = new Node(2);
	Node* root3 = new Node(3);
	Node* root4 = new Node(4);
	Node* root5 = new Node(5);
	root1->_left = root2;
	root1->_right = root3;
	root2->_left = root4;
	root2->_right = root5;
	cout << JudgeIsCompleteBinary(root1) << endl;
}
//        1
//    2      3
// 4   5   6 
void Test4()
{
	Node* root1 = new Node(1);
	Node* root2 = new Node(2);
	Node* root3 = new Node(3);
	Node* root4 = new Node(4);
	Node* root5 = new Node(5);
	Node* root6 = new Node(6);
	root1->_left = root2;
	root1->_right = root3;
	root2->_left = root4;
	root2->_right = root5;
	root3->_left = root6;
	cout << JudgeIsCompleteBinary(root1) << endl;
}
//����
void Test5()
{
	cout << JudgeIsCompleteBinary(NULL) << endl;
}
//int main()
//{
//	//Test1();
//	//Test2();
//	//Test3();
//	//Test4();
//	Test5();
//	system("pause");
//	return 0;
//}



//��������������ڵ������������ȡ�Ҫ�������������������������������������
//1��������ÿ���ڵ���parent����������
//2����������������������
//3��������ͨ����������������ʵ��ʱ�临�Ӷ�ΪO��N����

#include<stack>
namespace ObjTreeAncestor1
{
	struct TreeNode
	{
		TreeNode* _left;
		TreeNode* _right;
		TreeNode* _parent;
		int _data;
		TreeNode(const int& data)
			:_left(NULL)
			, _right(NULL)
			, _parent(NULL)
			, _data(data)
		{}
	};
	typedef TreeNode Node;
	Node* FindDoubleNodeSameAncestor(Node* root, Node* node1, Node* node2)
	{
		if (root == NULL)
			return NULL;
		Node* cur1 = node1;
		Node* cur2 = node2;
		stack<Node*> s1;
		stack<Node*> s2;
		while (cur1)
		{   //�Ӹýڵ�һ·ѹ��ֱ�����ڵ�Ϊֹ
			s1.push(cur1);
			cur1 = cur1->_parent;
		}
		while (cur2)
		{
			s2.push(cur2);
			cur2 = cur2->_parent;
		}
		Node* ret = NULL;
		while(!s1.empty() && !s2.empty() && s1.top() == s2.top())
		{
			ret = s1.top();
			s1.pop();
			s2.pop();
		}
		return ret;
	}
	//       1
	//   2       3
	// 4    5  
	void Test()
	{
		Node* root1 = new Node(1);
		Node* root2 = new Node(2);
		Node* root3 = new Node(3);
		Node* root4 = new Node(4);
		Node* root5 = new Node(5);
		root1->_left = root2;
		root2->_parent = root1;
		root1->_right = root3;
		root3->_parent = root1;
		root2->_left = root4;
		root4->_parent = root2;
		root2->_right = root5;
		root5->_parent = root2;
		Node* ret1 = FindDoubleNodeSameAncestor(root1, root2, root3);
		cout << ret1->_data << endl;   //1
		Node* ret2 = FindDoubleNodeSameAncestor(root1, root4, root3);
		cout << ret2->_data << endl;   //1
		Node* ret3 = FindDoubleNodeSameAncestor(root1, root4, root5);
		cout << ret3->_data << endl;   //2
	}
}

namespace ObjTreeAncestor2
{
	struct BinaryTreeNode
	{
		BinaryTreeNode* _left;
		BinaryTreeNode* _right;
		int _data;
		BinaryTreeNode(const int& data)
			:_data(data)
			, _left(NULL)
			, _right(NULL)
		{}
	};
	typedef BinaryTreeNode Node;
	Node* FindDoubleNodeSameAncestor(Node* root, Node* node1, Node* node2)
	{
		if (root == NULL)
			return NULL;
		if ((root->_data > node1->_data && root->_data < node2->_data)
			|| (root->_data < node1->_data && root->_data > node2->_data))
			return root;
		else if (root->_data > node1->_data && root->_data > node2->_data)
			return FindDoubleNodeSameAncestor(root->_left,node1,node2);
		else
			return FindDoubleNodeSameAncestor(root->_right, node1, node2);
	}
	//����������
	//       4
	//   2       6
	// 1    3  5   7
	void Test()
	{
		Node* root1 = new Node(4);
		Node* root2 = new Node(2);
		Node* root3 = new Node(6);
		Node* root4 = new Node(1);
		Node* root5 = new Node(3);
		Node* root6 = new Node(5);
		Node* root7 = new Node(7);
		root1->_left = root2;
		root1->_right = root3;
		root2->_left = root4;
		root2->_right = root5;
		root3->_left = root6;
		root3->_right = root7;
		Node* ret1 = FindDoubleNodeSameAncestor(root1, root5, root6);
		cout << ret1->_data << endl;  //4
		Node* ret2 = FindDoubleNodeSameAncestor(root1, root4, root5);
		cout << ret2->_data << endl;   //2
		Node* ret3 = FindDoubleNodeSameAncestor(root1, root4, root7);
		cout << ret3->_data << endl;  //4
	}
}

//3.��ͨ������,û��parentָ�룬���Ҳ��Ƕ���������
namespace ObjTreeAncestor3
{
	struct TreeNode
	{
		TreeNode* _left;
		TreeNode* _right;
		int _data;
		TreeNode(const int& data)
			:_data(data)
			, _left(NULL)
			, _right(NULL)
		{}
	};
	typedef TreeNode Node;

	bool NodePath(Node* root,Node* node,stack<Node*>& path)  //��������ʱջ���Ѿ�ѹ���˽ڵ��·��
	{
		if (root == NULL)
			return false;
		path.push(root);
		if (root == node)
			return true;
		if (NodePath(root->_left, node, path))   //�ڵ�����������
			return true;
		//else
			//path.pop();
		if (NodePath(root->_right, node, path))   //�ڵ�����������
			return true;
		
		path.pop();    //��������������оͰ�ѹ��ջ�еĽڵ�pop����
		return false;
	}
	Node* FindDoubleNodeSameAncestor(Node* root, Node* node1, Node* node2)
	{
		if (root == NULL || node1==NULL || node2==NULL)
			return NULL;
		stack<Node*> path1;    //���node1������·���ڵ�
		stack<Node*> path2;    //���node2������·���ڵ�
		if (!NodePath(root, node1, path1) || !NodePath(root, node2, path2))
			return NULL;
	
		while (path1.size() != path2.size())
		{
			if (path1.size() > path2.size())
				path1.pop();
			else
				path2.pop();
		}
		while (!path1.empty() && !path2.empty() && path1.top() != path2.top())
		{
			path1.pop();
			path2.pop();
		}
		if (path1.top()==path2.top())
			return path1.top();

		return NULL;
	}
	//       1
	//   2       3
	// 4    5  6
	void Test()
	{
		Node* node1 = new Node(1);
		Node* node2 = new Node(2);
		Node* node3 = new Node(3);
		Node* node4 = new Node(4);
		Node* node5 = new Node(5);
		Node* node6 = new Node(6);
		node1->_left = node2;
		node1->_right = node3;
		node2->_left = node4;
		node2->_right = node5;
		node3->_left = node6;
		Node* ret = FindDoubleNodeSameAncestor(node1, node4, node5);
		cout << ret->_data << endl;
		Node* ret1 = FindDoubleNodeSameAncestor(node1, node3, node4);
		cout << ret1->_data << endl;
		Node* ret2 = FindDoubleNodeSameAncestor(node1, node5, node6);
		cout << ret2->_data << endl;
	}
}
int main()
{
	//ObjTreeAncestor1::Test();
	//ObjTreeAncestor2::Test();
	ObjTreeAncestor3::Test();
	system("pause");
	return 0;
}