#include<iostream>
#include<stack>
using namespace std;

struct ListNode
{
	struct ListNode* _next;
	struct ListNode* _random;
	int _data;
	ListNode(int x)
		:_next(NULL)
		, _random(NULL)
		, _data(x)
	{}
};
typedef ListNode Node;

//1.删除无头单链表的非尾节点（替换法删除）
bool DeleteNotTailNode(Node* pos)
{
	if (pos==NULL || pos->_next==NULL)  //保证pos存在且不是尾节点
		return false;

	Node* tmp = pos->_next;    
	pos->_data = tmp->_data;
	pos->_next = tmp->_next;
	delete tmp;
	tmp = NULL;
	return true;
}
//2.倒序打印单链表，借助栈
void PrintTailToHead(Node* head)
{
	stack<Node*> s;
	Node* cur = head;
	while (cur)
	{
		s.push(cur);
		cur = cur->_next;
	}
	while (!s.empty())
	{
		cout << s.top()->_data << " ";
		s.pop();
	}
	cout << endl;
}
//递归方法倒序打印单链表
void PrintTailToHeadR(Node* head)
{
	if (head == NULL)
		return;     //递归返回条件
	PrintTailToHeadR(head->_next);
	cout << head->_data << " ";
}

//3.复杂链表的复制,分三步，
//拷贝节点插在每个节点的后面；
//遍历链表更新随机指针的指向；
//拆分
Node* ComplexListCopy(Node* head)
{
	if (head == NULL)
		return NULL;
	Node* cur = head;
	//拷贝节点插在每个节点的后面
	while (cur)
	{
		Node* tmp = new Node(cur->_data);
		tmp->_next = cur->_next;
		cur->_next = tmp;
		cur = cur->_next->_next;     //新增了节点，要越过复制的节点
	}
	cur = head;
	//更新随机指针指向
	while (cur)
	{
		if (cur->_random)
			cur->_next->_random = cur->_random;
		else
			cur->_next->_random = NULL;

		cur = cur->_next->_next;     //新增了节点，要越过复制的节点
	}
	//拆分
	cur = head;
	Node* CopyListHead = cur->_next;
	Node* CopyListTail = CopyListHead;
	cur->_next = cur->_next->_next;
	cur = cur->_next;
	while (cur)
	{
		Node* next = cur->_next; 
	    cur->_next = next->_next;
		CopyListTail->_next = next;
		CopyListTail = next;
		cur = cur->_next;
	}
	return CopyListHead;
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
	//PrintTailToHead(p1);
	//PrintTailToHeadR(p1);
	bool ret1=DeleteNotTailNode(p3);
	cout << ret1 << endl;
	bool ret2=DeleteNotTailNode(p6);
	cout << ret2 << endl;
}
void Test1()
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
	p5->_random = p2;   //置随机指针
	p3->_random = p4;
	p5->_random = p5;
	p6->_random = NULL;
	PrintList(p1);
	Node* ret=ComplexListCopy(p1);
	PrintList(ret);
}
int main()
{
	//Test();
	Test1();
	system("pause");
	return 0;
}