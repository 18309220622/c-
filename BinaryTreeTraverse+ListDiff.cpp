#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;
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
	BinaryTree(int* arr, size_t size, int invalid)
	{
		assert(arr);
		size_t index = 0;
		_root = _CreateBinaryTree(arr, size, invalid, index);
	}
	void PrevOrderNoR()
	{
		if (_root == NULL)
			return;
		stack<Node*> s;
		Node* cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				cout << cur->_key << " ";
				s.push(cur);
				cur = cur->_left;   //��������ȫ����ջ
			}
			Node* Top = s.top();
			s.pop();
			cur = Top->_right;   //�����Һ���Ҳ����ջ
		}
	}
	void InOrderNoR()
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			cur = s.top();
			cout << cur->_key << " ";
			s.pop();
			cur = cur->_right;
		}
	}
	void PostOrderNoR()
	{
		if (_root == NULL)
			return;
		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* Top = s.top();
			if (Top->_right == NULL || Top->_right == prev)
			{
				prev = Top;
				cout << Top->_key << " ";
				s.pop();
			}
			else
				cur = Top->_right;
		}
	}

	void PostOrder_NonR()   //�ǵݹ�������
	{
		//������������������ٸ��ڵ�  (��ջ)3��4��2��6��5��1
		Node* cur = _root;
		Node* prev = NULL;
		stack<Node*> s;
		s.push(cur);
		while (!s.empty())
		{
			cur = s.top();

			if ((cur->_left == NULL && cur->_right == NULL)
				|| (prev != NULL) && (prev == cur->_left || prev == cur->_right))
			{
				cout << cur->_key << " ";
				s.pop();
				prev = cur;
			}
			else
			{
				if (cur->_right)
				{
					s.push(cur->_right);
				}
				if (cur->_left)
				{
					s.push(cur->_left);
				}
			}
		}
	}
private:
	Node* _CreateBinaryTree(int* arr, size_t size, int& invalid, size_t& index)
	{
		Node* root = NULL;
		if (index < size && arr[index] != invalid)
		{
			root = new Node(arr[index]);
			root->_left = _CreateBinaryTree(arr, size, invalid, ++index);
			root->_right = _CreateBinaryTree(arr, size, invalid, ++index);
		}
		return root;
	}
private:
	Node* _root;
};

int main()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree b(a, 10, '#');
	cout << "��������ǰ��ǵݹ������";
	b.PrevOrderNoR();
	cout << endl;
	cout << "������������ǵݹ������";
	b.InOrderNoR();
	cout << endl;
	cout << "�������ĺ���ǵݹ������";
	b.PostOrderNoR();
	cout << endl;
	cout << "�������ĺ���ǵݹ������";
	b.PostOrder_NonR();
	cout << endl;
	system("pause");
	return 0;
}

//��֪����A��B��Ԫ�طֱ��ò���ͷ���ĵ�����洢
//����difference()������⼯��A��B�Ĳ��������������ڼ���A�ĵ������С�
//���磬������A = { 5, 10, 20, 15, 25, 30 }������B = { 5, 15, 35, 25 }
//��ɼ����A = { 10, 20, 30 }��
#include<list>
namespace List
{
	struct ListNode
	{
		int _elem;
		ListNode* _next;
		ListNode(int elem)
			:_elem(elem)
			, _next(NULL)
		{}
	};
	typedef ListNode Node;
	void DiffDoubleList(Node** LA, Node* LB)
	{
		//ȡ������LA��ÿһ��Ԫ�أ�Ȼ���ڼ���LB��Ѱ��,�ҵ���ɾ���˽ڵ�
		Node* pA = *LA;
		Node* pB = LB;
		Node* prev = NULL;
		Node* del = NULL;
		while (pA)
		{
			while (pB && pA->_elem != pB->_elem)
			{
				pB = pB->_next;
			}
			//����whileѭ��˵��Ҫô����LBΪ�գ�ҪôLA�ҵ���LB��ͬԪ�صĽڵ�
			if (pB)
			{
				//��ʼ��LA��ɾ����LB��ͬ�Ľڵ�Ԫ��
				if (prev == NULL)
					*LA = pA->_next;
				else
					prev->_next = pA->_next;

				del = pA;
				pA = pA->_next;
				free(del);
			}
			while (pA && pA->_elem != pB->_elem)
			{
				prev = pA;
				pA = pA->_next;
			}
		}
	}
	void PrintList(Node* head)
	{
		if (head == NULL)
			return;
		Node* cur = head;
		while (cur)
		{
			cout << cur->_elem << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
	void Test()
	{
		Node* p1 = new Node(5);
		Node* p2 = new Node(10);
		Node* p3 = new Node(20);
		Node* p4 = new Node(15);
		Node* p5 = new Node(25);
		Node* p6 = new Node(30);
		p1->_next = p2;
		p2->_next = p3;
		p3->_next = p4;
		p4->_next = p5;
		p5->_next = p6;

		Node* n1 = new Node(5);
		Node* n2 = new Node(15);
		Node* n3 = new Node(35);
		Node* n4 = new Node(25);
		n1->_next = n2;
		n2->_next = n3;
		n3->_next = n4;

		PrintList(p1);
		DiffDoubleList(&p1, n1);
		PrintList(p1);
	}
}
//int main()
//{
//	List::Test();
//	system("pause");
//	return 0;
//}
