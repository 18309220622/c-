#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;

bool JudgeStackLeg(const int* pPush,const int* pPop,size_t InSize,size_t OutSize)
{
	assert(pPush && pPop);
	assert(InSize && OutSize);
	if (InSize != OutSize)      //�����ջԪ�ظ����ͳ�ջԪ�ظ������ȣ���ô�϶����Ϸ�
		return false;

	stack<int> s;
	size_t j = 0;
	for (size_t i = 0; i < InSize; ++i)
	{
		s.push(pPush[i]);
		while (j < OutSize)
		{
			if (!s.empty() && s.top() == pPop[j])   //�����ʱ��ջԪ��ǡ������ջ���е�ĳ��Ԫ�ؾ�������ջ
			{
				s.pop();
				++j;
			}
			else
				break;
		} 
	 }
	if (!s.empty())      //ջ�л���Ԫ����ô�Ͳ��Ϸ�
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

//����һ������������λ��1�ĸ���
int Numberof1(int n)
{
	int count = 0;
	while (n)
	{
		++count;   //��0��������һ��1
		n = (n - 1)&n;  //���nΪ0111,n-1Ϊ0110,����ȡ��һ��1
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