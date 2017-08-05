#include<iostream>
using namespace std;

//void BubbleSort(int* a, int len)
//{
//	if (a == NULL || len <= 0)
//		return;
//	size_t i, j;
//	bool flag = true;     //��������
//	for (i = 0; i < len - 1; ++i)
//	{
//		flag = true;
//		for (j = 0; j < len - i - 1; ++j)
//		{
//			if (a[j]>a[j + 1])
//			{
//				std::swap(a[j], a[j + 1]);
//				flag = false;
//			}
//		}
//		if (flag == true)
//			break;
//	}
//}
//void BubbleSortOp(int* a, int len)
//{
//	if (a == NULL || len <= 0)
//		return;
//	bool flag = true;    //��ʾ����
//	size_t i, j;
//	size_t index;          //��¼���һ�ν�����λ��
//	size_t range=len-1;    //��¼ÿ�αȽ����ݵķ�Χ
//	for (i = 0; i < len - 1; ++i)
//	{
//		flag = true;
//		index = 0;
//		for (j = 0; j < range; ++j)
//		{
//			if (a[j]>a[j + 1])
//			{
//				swap(a[j],a[j+1]);
//				flag = false;
//				index = j;      //�������ѭ��˵��index����ľͶ�������
//			}
//		}
//		if (flag == true)    //�Ƚϵ�һ��������û�н�����˵���Ѿ��������
//			break;
//		range = index;
//	}
//}
//int main()
//{
//	int a[] = {8,8,5,4,3,2,8,6,9,0,11};
//	int len = sizeof(a) / sizeof(a[0]);
//	//BubbleSort(a, len);
//	BubbleSortOp(a, len);
//	for (size_t i = 0; i < len; ++i)
//	{
//		cout << a[i] << " ";
//	}
//	cout << endl;
//	system("pause");
//	return 0;
//}


//�������������˼���Ƿ��Σ������ȶ�һ����������е�������Ȼ�󽫴������ֽ��зָ�
//�ٽ��е�������ֱ���������ʣ�µ���Ԫ�ؾͲ��ٷָ��ˣ�С���������˷�����һ�������������ˣ�Ҳ���ǵݹ�˼�롣
//����һ��ǰ��ָ�뷨
#include<assert.h>
int PartSort1(int* a, int begin, int end)
{
	int key = a[end];
	int left = begin;
	int right = end;
	while (left < right)
	{
		//�����ѡ��ȹؼ��ִ�ģ��ұ�ѡ��ȹؼ���С�ģ�Ȼ����н�����ʹ�ùؼ�����߱ȹؼ���
		//С���ұ߶��ȹؼ��ִ�
		while (left < right && a[left] <= key)
			++left;
		while (left < right && a[right] >= key)
			--right;
		if (left < right)
			swap(a[left],a[right]);
	}
	//left==right
	swap(a[left], a[end]);
	return left;
}
//�ڿӷ���ѡ���ʵ�ֵ������У�
//������һ���ӣ����籣�����ұߵ�ֵ�����һ��λ�ô����γ���һ���ӣ�Ȼ�������ѡ��һ���ȸ�ֵ���
//������У���ʱ������γ���һ���ӣ��������ұ�ѡ��һ���ȱ���������ֵС��������У�ֱ��left,right
//���������������
int PartSort2(int* a, int begin, int end)
{
	int tmp = a[end];
	int left = begin;
	int right = end;
	while (left < right)
	{
		while (left < right && a[left] <= tmp)   //���ڵ����ע�⣡����
			++left;
		a[right] = a[left];    //��ʱrightָ��len-1��λ��
		
		while (left < right && a[right] >= tmp)
			--right;
		a[left]=a[right];    //�ո�left�γ���һ����
	}
	//left==right
	a[left] = tmp;
	return left;
}
//��������ǰ��ָ�뷨
int PartSort3(int* a, int begin, int end)
{
	int prev = begin - 1;
	int cur = begin;
	while (cur < end)
	{
		if (a[cur] < a[end])
		{
			++prev;
			if (prev != cur)
				swap(a[prev], a[cur]);
		}
		++cur;
	}
	++prev;
	swap(a[prev], a[end]);
	return prev;
}
void QuickSort(int* a, int begin, int end)
{
	assert(a);
	//int div=PartSort1(a,begin,end);  
	//int div=PartSort2(a,begin,end);  
	int div = PartSort3(a, begin, end);
	if (div - 1 > begin)
		QuickSort(a, begin, div - 1);      //[begin,div-1] div [div+1,end]

	if (div + 1 < end)
		QuickSort(a, div + 1, end);
}

#include<stack>
#include<assert.h>
#include<cstdlib>
void QuickSortNonR(int* a, int begin, int end)
{
	stack<int> s;
	s.push(end);
	s.push(begin);
	while (!s.empty())
	{
		int left = s.top();
		s.pop();
		int right = s.top();
		s.pop();

		//int div=PartSort1(a,left,right);  
		//int div=PartSort2(a,left,right);  
		int div = PartSort3(a, left, right);
		if (left < div)
		{
			s.push(div - 1);
			s.push(left);
		}
		if (div + 1 < right)
		{
			s.push(right);
			s.push(div + 1);
		}
	}
}

int main()
{
	int a[] = {8,8,5,4,3,2,8,6,9,0,11};
	int len = sizeof(a) / sizeof(a[0]);
	QuickSort(a, 0,len-1);
	//QuickSortNonR(a, 0, len - 1);
	for (size_t i = 0; i < len; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}

//�����������������ÿ��ѡ���Ĺؼ��ֽӽ���λ���������е�ʱ���ΪO(N * 1ogN)��
//���������������
//������������������ǵ������ظ�����һ�������е�ʱ��(����˵�����б�������)
//��ʱ��������ʱ��ͱ�ΪO(N*N)��
//Ϊ�˱���������������ͨ���������ַ�ʽ�������Ż���
//��1������ȡ�з�
//����ȡ��,�ɱ���ÿ��ȡ�����������Ļ���С�ģ����ȡ���ؼ���Ϊ�м�ֵ������Ч��  
//ʹ����С�ľ����ŵ�ǰ��ȥ��ʹ������ľ�����ŵ�����ȥ ��
//��2�����ٵݹ�ջʹ�õ��Ż������������ʵ����Ҫ���ĵݹ�ջ�Ŀռ䣬�����������¶���ͨ��ʹ��
//ϵͳ�ݹ�ջ����ɵݹ���⡣��ϵͳջ��Ƶ����ȡ��Ӱ�쵽�����Ч�ʡ�
//�����������С��ģ�����ݼ����ܲ��Ǻܺ�, û�в������ܸߡ� ���������㷨ʹ���˷��μ�����������
//˵������ݼ���Ҫ��ΪС�����ݼ������д��� �����ݼ���Сʱ�����ؼ����ݹ���ÿ��������㷨��ʹ
//�ò�����������������STL��sort�����õĿ��� + ��������ģ�ʹ�������µ�ʱ�临�Ӷ�Ҳ
//��O(N*lgN)����һ�Ľ���֤���ȳ���ʹ�ÿ��������㷨Ҫ��Ч�Ķࡣ
//�����ֵ������к�С��ʱ��һ����ΪС��13��Ԫ�ص�ʱ�򣬲����������ڿ���.��Ϊ��������������
//�л��־���һ�ö�����һ���������и���С��13��ʱ����ʹ�ÿ��ŵĻ����൱�������˶�������󼸲�
//�Ľڵ���Ŀ��Ҳ�������˵ݹ�Ĵ��������������ڵ�������С��13��Ԫ�ص�ʱ���ȡֱ�Ӳ���������Щ��
//���н�������
