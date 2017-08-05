#include<iostream>
#include<assert.h>
#include<queue>
using namespace std;
//int a[] = {12,13,12,13,19,18,15,12,15,16,17}��Ҫ�������a��������Ҫ��ʱ�临�Ӷ�ΪO(N)
void CountSort(int* a,int size)
{
	assert(a && size > 0);
	int max = a[0];
	int min = a[0];
	//�ҳ��������������ֵ����Сֵ
	for (size_t i = 1; i<size; ++i)
	{
		if (a[i]>max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	//ȷ�����ݷ�ΧΪ�˺����Ͱ���ٿռ�
	int range = max - min + 1;
	int* bucket = new int[range];
	memset(bucket,0,sizeof(int)*range);
	for (size_t i = 0; i<size; ++i)
	{
		bucket[a[i] - min]++;    //���磺��������������С����12����ô�ͷŵ�0�±괦
	}
	int index = 0;
	for (size_t i = 0; i < range; ++i)
	{
		for (size_t j = 0; j < bucket[i]; ++j) //ÿ��Ͱ���ж��ٸ����ݣ�����Щ������һһ��������
		{
			a[index++] = min + i;
		}
	}
	delete[] bucket;
}
int main()
{
	int a[] = { 12, 13, 12, 13, 19, 18, 15, 12, 15, 16, 17 };
	int len = sizeof(a) / sizeof(a[0]);
	CountSort(a, len);
	for (size_t i = 0; i < len; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}

//��һ�������������λ����
//�磺{ 2, 5, 4, 9, 3, 6, 8, 7, 1 }����λ��Ϊ5��{ 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 }����λ��Ϊ4��5��
//Ҫ�󣺲���ʹ������ʱ�临�ӶȾ����ܵ͡�
//���Ƕѻ��߿���˼������
//ʹ�÷���λ����ߵ����ȸ�λ�õ���С���ұߵ����ȸ�λ���ϵ�����
int PartSort(int* a, int begin, int end)  
{
	int key = a[end];
	int left = begin;
	int right = end;
	while (left < right)
	{
		while (left < right && a[left] <= key)
			++left;
		while (left < right && a[right] >= key)
			--right;
		if (left < right)
			swap(a[left],a[right]);
	}
	//left==right
	swap(a[left],a[end]);    //��������endλ���ϵ����ݣ�������key
	return left;
}
int FindMid(int* a, int len)
{
	assert(a);
	int begin = 0;
	int end = len - 1;
	int mid = begin + ((end - begin) >> 1);
	int div = PartSort(a,begin,end);
	while (div != mid)
	{
		if (mid < div)    //���mid<div,��ô�͵ݹ鵽div����ȥ��
			div = PartSort(a, begin, div-1);
		else              //����div���ұ�ȥ��
			div = PartSort(a, div+1, end);
	}
	return a[mid];   //ֱ��div==mid�����ҵ��������λ��
}
//int main()
//{
//	//int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1 };
//	int a[]={ 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
//	int len = sizeof(a) / sizeof(a[0]);
//	int mid=FindMid(a, len);
//	cout << "���������λ��Ϊ��" << mid << endl;
//	system("pause");
//	return 0;
//}

//�磺{ 2, 5, 4, 9, 3, 6, 8, 7, 1 }����λ��Ϊ5;
//{ 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 }����λ��Ϊ4��5��
struct Com
{
	int operator()(int left,int right)
	{
		return left > right;
	}
};
void FindMidByHeap(int array[], int size)
{
	assert(array && size > 0);
	priority_queue<int> max_heap;
	priority_queue<int, vector<int>, Com> min_heap;

	for (int i = 0; i < size; ++i)
	{
		if (i % 2 == 0)    //ż��λ���ϵ�����max_heap
		{
			max_heap.push(array[i]);
		}
		else
		{
			min_heap.push(array[i]);
		}

		if (!min_heap.empty() && !max_heap.empty()) //��֤min_heap�����е�Ԫ�ض�����max_heap�е�Ԫ��
		{
			int tmp = max_heap.top();
			min_heap.push(tmp);
			max_heap.pop();

			tmp = min_heap.top();     //���ȼ����е�top���������±�Ϊ0�ĶѶ�Ԫ��
			max_heap.push(tmp);
			min_heap.pop();
		}
	}
	if (size % 2 == 0) //ż��  
	{
		cout << "ż����Ԫ��ʱ��λ���ǣ�" << max_heap.top() << " " << min_heap.top() << endl;
	}
	else
	{
		cout << "������Ԫ��ʱ��λ���ǣ�" << max_heap.top() << endl;
	}
}
int main()
{
	//int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1 };   //5
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };  //4,5  
	int len = sizeof(a) / sizeof(a[0]);             
	FindMidByHeap(a, len);
	system("pause");
	return 0;
}