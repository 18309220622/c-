#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;

bool JudgeStackLeg(const int* pPush,const int* pPop,size_t InSize,size_t OutSize)
{
	assert(pPush && pPop);
	assert(InSize && OutSize);
	if (InSize != OutSize)      //如果入栈元素个数和出栈元素个数不等，那么肯定不合法
		return false;

	stack<int> s;
	size_t j = 0;
	for (size_t i = 0; i < InSize; ++i)
	{
		s.push(pPush[i]);
		while (j < OutSize)
		{
			if (!s.empty() && s.top() == pPop[j])   //如果此时出栈元素恰好是入栈序列的某个元素就让它出栈
			{
				s.pop();
				++j;
			}
			else
				break;
		} 
	 }
	if (!s.empty())      //栈中还有元素那么就不合法
	{
		return false;
	}
	return true;
}
void test()
{
	int inStack[] = { 1, 2, 3, 4, 5 };
	int outStack[] = { 4, 5, 3, 2, 1 };       //legality  
	//int outStack[]={4,3,5,1,2};        //no  

	size_t szin = sizeof(inStack) / sizeof(inStack[0]);
	size_t szout = sizeof(outStack) / sizeof(outStack[0]);
	cout << JudgeStackLeg(inStack, outStack, szin, szout) << endl;
}
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}

//计算一个整数二进制位中1的个数
int Numberof1(int n)
{
	int count = 0;
	while (n)
	{
		++count;   //非0数至少有一个1
		n = (n - 1)&n;  //如果n为0111,n-1为0110,相与取出一个1
	}
	return count;
}
int main()
{
	//int ret = Numberof1(7);
	int ret = Numberof1(11);
	cout << ret << endl;
	system("pause");
	return 0;
}