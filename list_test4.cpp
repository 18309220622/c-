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

//1.ɾ����ͷ������ķ�β�ڵ㣨�滻��ɾ����
bool DeleteNotTailNode(Node* pos)
{
	if (pos==NULL || pos->_next==NULL)  //��֤pos�����Ҳ���β�ڵ�
		return false;

	Node* tmp = pos->_next;    
	pos->_data = tmp->_data;
	pos->_next = tmp->_next;
	delete tmp;
	tmp = NULL;
	return true;
}
//2.�����ӡ����������ջ
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
//�ݹ鷽�������ӡ������
void PrintTailToHeadR(Node* head)
{
	if (head == NULL)
		return;     //�ݹ鷵������
	PrintTailToHeadR(head->_next);
	cout << head->_data << " ";
}

//3.��������ĸ���,��������
//�����ڵ����ÿ���ڵ�ĺ��棻
//��������������ָ���ָ��
//���
Node* ComplexListCopy(Node* head)
{
	if (head == NULL)
		return NULL;
	Node* cur = head;
	//�����ڵ����ÿ���ڵ�ĺ���
	while (cur)
	{
		Node* tmp = new Node(cur->_data);
		tmp->_next = cur->_next;
		cur->_next = tmp;
		cur = cur->_next->_next;     //�����˽ڵ㣬ҪԽ�����ƵĽڵ�
	}
	cur = head;
	//�������ָ��ָ��
	while (cur)
	{
		if (cur->_random)
			cur->_next->_random = cur->_random;
		else
			cur->_next->_random = NULL;

		cur = cur->_next->_next;     //�����˽ڵ㣬ҪԽ�����ƵĽڵ�
	}
	//���
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
	p5->_random = p2;   //�����ָ��
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