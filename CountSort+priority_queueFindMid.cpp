#include<iostream>
#include<assert.h>
#include<queue>
using namespace std;
//int a[] = {12,13,12,13,19,18,15,12,15,16,17}，要求对数组a进行排序，要求时间复杂度为O(N)
void CountSort(int* a,int size)
{
	assert(a && size > 0);
	int max = a[0];
	int min = a[0];
	//找出这组数据中最大值和最小值
	for (size_t i = 1; i<size; ++i)
	{
		if (a[i]>max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	//确定数据范围为了后面给桶开辟空间
	int range = max - min + 1;
	int* bucket = new int[range];
	memset(bucket,0,sizeof(int)*range);
	for (size_t i = 0; i<size; ++i)
	{
		bucket[a[i] - min]++;    //比如：在这组数据中最小的是12，那么就放到0下标处
	}
	int index = 0;
	for (size_t i = 0; i < range; ++i)
	{
		for (size_t j = 0; j < bucket[i]; ++j) //每个桶里有多少个数据，将这些数据再一一放入数组
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

//求一个无序数组的中位数。
//如：{ 2, 5, 4, 9, 3, 6, 8, 7, 1 }的中位数为5，{ 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 }的中位数为4和5。
//要求：不能使用排序，时间复杂度尽可能低。
//考虑堆或者快排思想解决。
//使得返回位置左边的数比该位置的数小，右边的数比该位置上的数大
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
	swap(a[left],a[end]);    //交换的是end位置上的数据，而不是key
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
		if (mid < div)    //如果mid<div,那么就递归到div左半边去找
			div = PartSort(a, begin, div-1);
		else              //否则到div的右边去找
			div = PartSort(a, div+1, end);
	}
	return a[mid];   //直到div==mid，就找到了这个中位数
}
//int main()
//{
//	//int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1 };
//	int a[]={ 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
//	int len = sizeof(a) / sizeof(a[0]);
//	int mid=FindMid(a, len);
//	cout << "该数组的中位数为：" << mid << endl;
//	system("pause");
//	return 0;
//}

//如：{ 2, 5, 4, 9, 3, 6, 8, 7, 1 }的中位数为5;
//{ 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 }的中位数为4和5。
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
		if (i % 2 == 0)    //偶数位置上的数入max_heap
		{
			max_heap.push(array[i]);
		}
		else
		{
			min_heap.push(array[i]);
		}

		if (!min_heap.empty() && !max_heap.empty()) //保证min_heap中所有的元素都大于max_heap中的元素
		{
			int tmp = max_heap.top();
			min_heap.push(tmp);
			max_heap.pop();

			tmp = min_heap.top();     //优先级队列的top就是数组下标为0的堆顶元素
			max_heap.push(tmp);
			min_heap.pop();
		}
	}
	if (size % 2 == 0) //偶数  
	{
		cout << "偶数个元素时中位数是：" << max_heap.top() << " " << min_heap.top() << endl;
	}
	else
	{
		cout << "奇数个元素时中位数是：" << max_heap.top() << endl;
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