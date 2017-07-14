#include<iostream>
#include<cstdlib>
using namespace std;

namespace ListFindNode
{
	typedef struct ListNode
	{
		ListNode* _next;
		int _data;
		ListNode(int x)
			:_next(NULL)
			, _data(x)
		{}
	}Node;

	//1.链表的逆置
	Node* ReverseList(Node* head)
	{
		if (head == NULL)
			return NULL;
		Node* tmp = NULL;
		Node* cur = head;
		Node* NewHead = NULL;
		while (cur)
		{
			tmp = cur;
			cur = cur->_next;
			tmp->_next = NewHead;   //头插
			NewHead = tmp;          //更新头节点
		}
		return NewHead;
	}
	//2.找链表中间节点
	Node* FindMidNode(Node* head)
	{
		if (head == NULL)
			return NULL;
		Node* slow = head;
		Node* fast = head;
		while (fast && fast->_next)
		{
			slow = slow->_next;
			fast = fast->_next->_next;
		}
		return slow;
	}
	//3.找链表倒数第k个节点
	Node* FindKNode(Node* head,size_t k)
	{
		if (head == NULL || k<=0 )
			return NULL;
		Node* front = head;
		Node* back = head;

		for (int i = 0; i < k - 1; i++)
		{
			if (front->_next)
				front = front->_next;
			else
				return NULL;       //说明给出的k都比链表长度还要大
		}
		//让front一直走到链表尾，前后指针一直相差k-1步
		while (front->_next)
		{
			front = front->_next;
			back = back->_next;
		}
		return back;
	}

	void Print(Node* head)
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
		Node* p2 = new Node(5);
		Node* p3 = new Node(6);
		Node* p4 = new Node(3);
		Node* p5 = new Node(4);
		//Node* p6 = new Node(9);
		p1->_next = p2;
		p2->_next = p3;
		p3->_next = p4;
		p4->_next = p5;
		//p5->_next = p6;
		//Node* ret = FindMidNode(p1);
		//Node* ret = FindKNode(p1, 1);
		//Node* ret = FindKNode(p1, 5);
		//Node* ret = FindKNode(p1, 7);
		//cout << ret->_data << endl;

		Print(p1);
		Node* ret = ReverseList(p1);
		Print(ret);
	}
}
//int main()
//{
//	ListFindNode::Test();
//	system("pause");
//	return 0;
//}

//2.不用加减符号求两数和
namespace ADD
{
	int Add(int n1, int n2)
	{
		int sum = 0;
		int carray = 0;
		while (n2)
		{
		    sum = n1^n2;   //
			carray = (n1&n2) << 1; //进位
			n1 = sum;
			n2 = carray;
		}
		return n1;
	}
}
int main()
{
	int ret=ADD::Add(10,20);
	cout << ret << endl;
	system("pause");
	return 0;
}
