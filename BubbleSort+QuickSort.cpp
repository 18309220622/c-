#include<iostream>
using namespace std;

//void BubbleSort(int* a, int len)
//{
//	if (a == NULL || len <= 0)
//		return;
//	size_t i, j;
//	bool flag = true;     //代表有序
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
//	bool flag = true;    //表示有序
//	size_t i, j;
//	size_t index;          //记录最后一次交换的位置
//	size_t range=len-1;    //记录每次比较数据的范围
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
//				index = j;      //出了这个循环说明index后面的就都有序了
//			}
//		}
//		if (flag == true)    //比较的一趟下来都没有交换的说明已经是有序的
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


//快速排序的整体思想是分治，即首先对一个大区间进行单趟排序，然后将大区间又进行分割
//再进行单趟排序，直到这个区间剩下单个元素就不再分割了，小区间有序了返到上一层大区间就有序了，也就是递归思想。
//方法一：前后指针法
#include<assert.h>
int PartSort1(int* a, int begin, int end)
{
	int key = a[end];
	int left = begin;
	int right = end;
	while (left < right)
	{
		//在左边选择比关键字大的，右边选择比关键字小的，然后进行交换，使得关键字左边比关键字
		//小，右边都比关键字大
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
//挖坑法（选合适的值填入坑中）
//先设置一个坑，比如保存最右边的值，最后一个位置处就形成了一个坑，然后在左边选择一个比该值大的
//填入坑中，这时左边又形成了一个坑，所以在右边选择一个比保存下来的值小的填入坑中，直到left,right
//相遇就排序完成了
int PartSort2(int* a, int begin, int end)
{
	int tmp = a[end];
	int left = begin;
	int right = end;
	while (left < right)
	{
		while (left < right && a[left] <= tmp)   //等于的情况注意！！！
			++left;
		a[right] = a[left];    //此时right指向len-1的位置
		
		while (left < right && a[right] >= tmp)
			--right;
		a[left]=a[right];    //刚刚left形成了一个坑
	}
	//left==right
	a[left] = tmp;
	return left;
}
//方法三：前后指针法
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

//快速排序的最好情况是每次选出的关键字接近中位数，其运行的时间就为O(N * 1ogN)；
//快速排序的最坏情况：
//快速排序的最坏的情况就是当分组重复生成一个空序列的时候(比如说，序列本就有序)
//这时候其运行时间就变为O(N*N)。
//为了避免最坏的情况，可以通过以下两种方式来进行优化：
//（1）三数取中法
//三数取中,可避免每次取到的数是最大的或最小的，如果取到关键字为中间值则可提高效率  
//使比它小的尽快排到前面去，使比它大的尽快的排到后面去 。
//（2）减少递归栈使用的优化，快速排序的实现需要消耗递归栈的空间，而大多数情况下都会通过使用
//系统递归栈来完成递归求解。对系统栈的频繁存取会影响到排序的效率。
//快速排序对于小规模的数据集性能不是很好, 没有插入性能高。 快速排序算法使用了分治技术，最终来
//说大的数据集都要分为小的数据集来进行处理。 当数据集较小时，不必继续递归调用快速排序算法，使
//用插入排序代替快速排序。STL中sort就是用的快排 + 插入排序的，使得最坏情况下的时间复杂度也
//是O(N*lgN)．这一改进被证明比持续使用快速排序算法要有效的多。
//当划分的子序列很小的时候，一般认为小于13个元素的时候，插入排序优于快排.因为快速排序对数组进
//行划分就像一棵二叉树一样，当序列个数小于13的时候，再使用快排的话就相当于增加了二叉树最后几层
//的节点数目，也就增加了递归的次数，所以我们在当子序列小于13个元素的时候采取直接插入来对这些子
//序列进行排序。
