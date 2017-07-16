#include<iostream>
#include<list>
using namespace std;

struct ListNode
{
	int _data;
	struct ListNode* _next;
	ListNode(int x)
		:_data(x)
		, _next(NULL)
	{}
};
typedef ListNode Node;
//判环，如果带环求出相遇节点
Node* ListIsCircle(Node* head)
{
	if (head == NULL)
		return NULL;
	Node* slow = head;
	Node* fast = head;
	while (fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;
		if (fast == slow)
			return slow;
	}
	return NULL;
}

Node* CircleEnterNode(Node* head,Node* meet)
{
	if (head == NULL)
		return NULL;
	Node* cur1 = meet;
	Node* cur2 = head;
	while (cur1)
	{
		cur1 = cur1->_next;
	}
	while (cur2)
	{
		cur2 = cur2->_next;
	}
	if (cur1 == cur2)
		return cur1;
}


//判断两条链表是否相交
bool ListIsCross(Node* head1, Node* head2)
{
	if (head1 == NULL || head2 == NULL)
		return false;

	Node* cur1 = head1;
	Node* tail1 = NULL;
	Node* cur2 = head2;
	Node* tail2 = NULL;
	while (cur1)
	{
		tail1 = cur1;
		cur1 = cur1->_next;
	}
	while (cur2)
	{
		tail2 = cur2;
		cur2 = cur2->_next;
	}
	if (tail1 == tail2)
		return true;
	else
		return false;
}

//求相交的两条不带环单链表的交点
//方法一：重新构造环，让链表1的尾节点的_next指向另一条链表的第一个节点，然后转化为求环的入口点
Node* DoubleListCross1(Node* head1, Node* head2)
{
	if (ListIsCross(head1, head2))
	{
		//两条链表相交
		Node* cur1 = head1;
		while (cur1)
		{
			cur1 = cur1->_next;
		}
		cur1->_next = head2;      //构造环
		Node* meet=ListIsCircle(head1);    //找出这个新环的相遇点
		return CircleEnterNode(head1,meet);
	}
	return NULL;
}

//方法二：
Node* DoubleListCross2(Node* head1, Node* head2)
{
	if (head1 == NULL || head2 == NULL)
		return NULL;
	Node* cur1 = head1;
	int count1 = 0;
	Node* cur2 = head2;
	int count2 = 0;
	while (cur1)
	{
		++count1;
		cur1 = cur1->_next;
	}
	while (cur2)
	{
		++count2;
		cur2 = cur2->_next;
	}
	int ret=count2 - count1;
	cur1 = head1;
	cur2 = head2;
	//先让长链表走ret步
	if (ret > 0)
	{
		while (ret!=0)
		{
			cur1 = cur1->_next;
			--ret;
		}
		while (cur1 && cur2)
		{
			cur2 = cur2->_next;
			cur1 = cur1->_next;
			if (cur1 == cur2)
				return cur1;
		}
	}
	else
	{
		while (ret != 0)
		{
			cur2 = cur2->_next;
			++ret;
		}
		while (cur1 && cur2)
		{
			cur1 = cur1->_next;
			cur2 = cur2->_next;
			if (cur1 == cur2)
				return cur1;
		}
	}
	return NULL;
}

void Test()
{
	Node* p1 = new Node(3);
	Node* p2 = new Node(4);
	Node* p3 = new Node(5);
	Node* p4 = new Node(6);
	p1->_next = p2;
	p2->_next = p3;
	p3->_next = p4;

	Node* n1 = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(5);
	Node* n4 = new Node(6);
	n1->_next = n2;
	n2->_next = p3;
	p3->_next = p4;

	cout << ListIsCross(p1, n1)<<endl;   //判断两条不带环的单链表是否相交
	//Node* ret = DoubleListCross1(p1, n1);  //求交点
	Node* ret=DoubleListCross2(p1, n1);
	cout << ret->_data << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}