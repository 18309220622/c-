#include<iostream>
using namespace std;


//复杂链表的复制
namespace ListObject
{
	struct ComplexNode
	{
		int _data;
		struct ComplexNode* _next;
		struct ComplexNode* _random;
		ComplexNode(int x) :_data(x)
			, _next(NULL)
			, _random(NULL)
		{}
	};

	ComplexNode* ComplexListClone(ComplexNode* head)
	{
		if (head == NULL)
			return NULL;
		ComplexNode* cur = head;
		while (cur)   //复制节点插入到每个节点的后面
		{
			ComplexNode* tmp = new ComplexNode(cur->_data);
			tmp->_next = cur->_next;
			cur->_next = tmp;
			cur = cur->_next->_next;    //新增了一个复制过来的节点
		}
		cur = head;
		//遍历链表改变随机指针指向
		while (cur)
		{
			ComplexNode* next = cur->_next;
			if (cur->_random)
			{
				next->_random = cur->_random->_next;
				//新复制结点的随机指针就是原始结点的随机指针指向的结点的下一个结点  
			}
			else     //cur->_random==NULL
				next->_random = NULL;

			cur = next->_next;
		}

		//进行拆分，奇数位置上的为原始链表，偶数位置上的为复制链表
		cur = head;
		ComplexNode* pCloneHead = NULL;   //记录复制链表的头
		ComplexNode* pCloneNode = NULL;   //记录复制链表的节点
		if(cur)
		{
			pCloneHead = pCloneNode = cur->_next;  //复制链表的头
			cur->_next = pCloneNode->_next;     //让cur->_next先指向原链表的第二个节点
			cur = cur->_next;                   //cur此时指向原链表的第二个节点
		}
		while (cur)
		{
			pCloneNode->_next = cur->_next;  //把偶数位置的结点链接起来就是复制出来的新链表  
			pCloneNode = pCloneNode->_next;
			cur->_next = pCloneNode->_next;  //把奇数位置的结点链接起来就是原始链表  
			cur = cur->_next;
		}
		return pCloneHead;
	}

	void Print(ComplexNode* head)
	{
		ComplexNode* cur = head;
		while (cur)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
}

void Test()
{
	ListObject::ComplexNode* p1 = new ListObject::ComplexNode(1);
	ListObject::ComplexNode* p2 = new ListObject::ComplexNode(2);
	ListObject::ComplexNode* p3 = new ListObject::ComplexNode(3);
	ListObject::ComplexNode* p4 = new ListObject::ComplexNode(4);
	ListObject::ComplexNode* p5 = new ListObject::ComplexNode(5);
	ListObject::ComplexNode* p6 = new ListObject::ComplexNode(6);
	//把节点连接起来
	p1->_next = p2;
	p2->_next = p3;
	p3->_next = p4;
	p4->_next = p5;
	p5->_next = p6;
	ListObject::Print(p1);
	ListObject::ComplexNode* pNode = NULL;
	pNode=ListObject::ComplexListClone(p1);
	ListObject::Print(pNode);
}
int main()
{
	Test();
	system("pause");
	return 0;
}