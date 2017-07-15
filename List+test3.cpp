#include<iostream>
using namespace std;

namespace ObjList
{
	typedef struct ListNode
	{
		struct ListNode* _next;
		int _data;
		ListNode(int x)
			:_next(NULL)
			, _data(x)
		{}
	}Node;
	Node* JudgeIsCircle(Node* head)     //时间复杂度为：O(N)
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

	int CircleLenth(Node* meet)       //时间复杂度为：O(N)
	{
		int count = 0;
		Node* cur = meet;
		while (cur)
		{
			cur = cur->_next;
			++count;
			if (cur == meet)
				break;
		}
		return count;
	}

	Node* EnterNode(Node* head, Node* meet)     //时间复杂度为O(N)
	{
		//一个指针指向头，一个指向相遇点，它们同时走，相遇点即为环的入口点
		if (head == NULL)
			return NULL;

		Node* front = head;
		Node* back = meet;
		while (front != back)
		{
			front = front->_next;
			back = back->_next;
		}
		return front;   //相遇了任意返回一个节点
	}

	void Test()
	{
		Node* p1 = new Node(1);
		Node* p2 = new Node(2);
		Node* p3 = new Node(3);
		Node* p4 = new Node(4);
		Node* p5 = new Node(5);
		Node* p6 = new Node(6);
		Node* p7 = new Node(7);
		p1->_next = p2;
		p2->_next = p3;
		p3->_next = p4;
		p4->_next = p5;
		p5->_next = p6;
		p6->_next = p7;
		//p7->_next = p3;   //构造环
		p7->_next = p7;     //指向自己的环


		Node* ret = JudgeIsCircle(p1);
		cout << "相遇点：" << ret->_data << endl;

		int CircleLen = CircleLenth(ret);
		cout << "环长：" << CircleLen << endl;

		Node* s = EnterNode(p1, ret);
		cout << "环的入口点：" << s->_data << endl;
	}
}

int main()
{
	ObjList::Test();
	system("pause");
	return 0;
}


//只能在堆上构造对象
class A
{
public:
	static A* GetHeapObj()      //对象只能从堆上来
	{
		if (_obj == NULL)
			_obj = new A();
		return _obj;
	}
	static void Print()
	{
		cout << A().count << endl;
	}
private:
	A(const A& a);   //防拷贝
private:
	A()
	{}
	static A* _obj;
	int count = 10;
};
A* A::_obj = 0;

int main()
{
	A::GetHeapObj();
	A::Print();
	system("pause");
	return 0;
}


//只能在栈上构造对象
class B
{
public:
	static B GetStackObj(int n)
	{
		cout << n << endl;
		return B(n);
	}
	
private:
	B(const B& b);    //防拷贝
private:
	B(int a)
		:_count(a)
	{}
	int _count;
};

int main()
{
	B::GetStackObj(20);    
	system("pause");
	return 0;
}
