#include<iostream>
using namespace std;

namespace List
{
	struct ListNode
	{
		int _data;
		struct ListNode* _next;
		ListNode(int x)
			:_data(x)
			,_next(NULL)
		{}
	};
	typedef ListNode Node;
	Node* MergeList(Node* head1,Node* head2)
	{
		if (head1 == NULL)
			return head2;
		if (head2 == NULL)
			return head1;
		if (head1 == head2)
			return head1;
		//确定合并链表的头
		Node* cur1 = head1;
		Node* cur2 = head2;
		Node* NewHead = NULL;
		Node* Tail = NULL;    //方便尾插
		if (cur1->_data < cur2->_data)
		{
			NewHead = cur1;
			cur1 = cur1->_next;
		}
		else
		{
			NewHead = cur2;
			cur2 = cur2->_next;
		}
		Tail = NewHead;   
		while (cur1  && cur2 )
		{
			if (cur1->_data < cur2->_data)
			{
				Tail->_next = cur1;
				cur1 = cur1->_next;
			}
			else
			{
				Tail->_next = cur2;
				cur2 = cur2->_next;
			}
			Tail = Tail->_next;
		}
		if (cur1)        //将链表1中剩余的元素都连到Tail后面
		{
			Tail->_next = cur1;
		}
		if (cur2)
		{
			Tail->_next = cur2;
		}
		return NewHead;
	}

	Node* MergeListR(Node* head1, Node* head2)
	{
		if (head1 == NULL)
			return head2;
		if (head2 == NULL)
			return head1;
		if (head1 == head2)
			return head1;

		if (head1->_data < head2->_data)
		{
			head1->_next=MergeListR(head1->_next, head2);
			return head1;
		}
		else
		{
			head2->_next = MergeListR(head1, head2->_next);
			return head2;
		}
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
		Node* p2 = new Node(3);
		Node* p3 = new Node(5);
		Node* p4 = new Node(7);
		Node* p5 = new Node(9);
		p1->_next = p2;
		p2->_next = p3;
		p3->_next = p4;
		p4->_next = p5;

		Node* n1 = new Node(2);
		Node* n2 = new Node(4);
		Node* n3 = new Node(6);
		Node* n4 = new Node(8);
		Node* n5 = new Node(10);
		n1->_next = n2;
		n2->_next = n3;
		n3->_next = n4;
		n4->_next = n5;

		//Node* ret=MergeList(p1, n1);
		Node* ret=MergeListR(p1, n1);
		Print(ret);
	}
}
//int main()
//{
//	List::Test();
//	system("pause");
//	return 0;
//}

//1.构造函数方法求和
namespace ObjSum
{
	class Sum
	{
	public:
		Sum()
		{
			++i;
			sum += i;
		}
		static void PrintSum()   //静态成员变量只能静态成员函数取访问
		{
			cout << sum << endl;
		}
	private:
		static size_t sum;
		static size_t i;
	};
	size_t Sum::sum = 0;
	size_t Sum::i = 0;
}

//int main()
//{
//	ObjSum::Sum* arr = new ObjSum::Sum[100];   //new在开辟数组的同时调用构造函数进行初始化
//	ObjSum::Sum::PrintSum();
//	delete[] arr;
//	arr = NULL;
//	system("pause");
//	return 0;
//}

//2.递归方法
int Solution(int n)
{
	int sum = n;
	bool ret = ((n > 0) && (sum+=Solution(n-1)));
	return sum;
}
int main()
{
	int ret=Solution(100);
	printf("ret:%d\n",ret);
	system("pause");
	return 0;
}






