#include<iostream>
#include<assert.h>
using namespace std;
void SelectSort(int* a, int len)
{
	assert(a);
	int left = 0;
	int right = len - 1;
	while (left < right)
	{
		int min = left;    //记录最小值的下标
		int max = left;    //记录最大值的下标
		for (int i = left; i <= right; ++i)
		{
			if (a[i] > a[min])
				min = i;
			if (a[i] < a[max])
				max = i;
		}
		std::swap(a[left],a[min]);
		if (max == left)
			max = min;

		std::swap(a[right],a[max]);

		++left;
		--right;
	} 
}

void AdjustDown(int* a,int len,int root)
{
	int parent = root;
	int child = 2 * parent + 1;
	while (child < len)
	{
		if (child + 1 < len && a[child] < a[child + 1])
			++child;
		if (a[child]>a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}
void HeapSort(int* a, int len)
{
	assert(a);
	for (int i=(len - 2) / 2; i >= 0; --i)
	{
		AdjustDown(a,len,i);
	}
	int end = len - 1;  //记录最后一个元素的下标
	while (end>=0)
	{
		std::swap(a[0],a[end]);
		AdjustDown(a,end,0);      //第二个参数代表需要下调的元素个数，第三个参数是从哪开始调
		--end;
	}
}
//int main()
//{
//	int arr[] = { 1, 4, 6, 2, 3, 6 };
//	//SelectSort(arr, 6);
//	HeapSort(arr, 6);
//	for (int i = 0; i<6; i++)
//	{
//		cout << arr[i] << " ";
//	}
//	cout << endl;
//	system("pause");
//	return 0;
//}

//本公司现在要给公司员工发波福利，在员工工作时间会提供大量的水果供员工补充营养。
//由于水果种类比较多，但是却又不知道哪种水果比较受欢迎，然后公司就让每个员工报告了
//自己最爱吃的k种水果，并且告知已经将所有员工喜欢吃的水果存储于一个数组中。
//然后让我们统计出所有水果出现的次数，并且求出大家最喜欢吃的前k种水果。
#include<vector>
#include<string>
#include<map>
#include<queue>
struct Less
{
	bool operator()(map<string,int>::iterator it1,map<string,int>::iterator it2)
	{
		return it1->second < it2->second;
	}
};
void GetFavoriateFruits(const vector<string>& fruits, size_t k)
{
	map<string, int> countMap;
	map<string, int>::iterator countMapIt;
	//方法一：
	//for (size_t i = 0; i < fruits.size(); ++i)
	//{
	//	countMapIt=countMap.find(fruits[i]);
	//	if (countMapIt != countMap.end())
	//	{
	//		countMapIt->second++;    //该水果已经存在则只需要次数++
	//	}
	//	countMap.insert(make_pair(fruits[i],1));
	//}
	//方法二：
	//pair<map<string, int>::iterator, bool> ret;
	//for (size_t i = 0; i < fruits.size(); ++i)
	//{
	//	ret = countMap.insert(make_pair(fruits[i],1));
	//	if (ret.second == false)    //插入失败说明该水果已经存在
	//	{
	//		ret.first->second++;   //ret.first是map<string, int>::iterator
	//	}
	//}
	//方法三：利用operator[]来实现，内部其实也调用的是insert
	for (size_t i = 0; i < fruits.size(); ++i)
	{
		countMap[fruits[i]]++;
	}
	//打印出各种水果以及它们所对应出现的次数
	countMapIt = countMap.begin();
	while (countMapIt != countMap.end())
	{
		cout << countMapIt->first << " " << countMapIt->second << endl;
		++countMapIt;
	}
	//前k种水果，优先级队列的内部实现就是通过建堆(用vector里的元素)
	priority_queue< vector<map<string, int>::iterator>, Less> q;
	countMapIt = countMap.begin();
	while (countMapIt != countMap.end())
	{
		q.push(countMapIt);
		++countMapIt;
	}
	for (size_t i = 0; i < k; ++i)
	{
		cout << "哪种水果：" << q.top()->first << " " << "出现的次数:" << q.top()->second << endl;
		q.pop();
	}
}
void Test()
{
	vector<string> fruits;
	fruits.push_back("苹果");
	fruits.push_back("香蕉");
	fruits.push_back("西瓜");
	fruits.push_back("苹果");
	fruits.push_back("菠萝");
	fruits.push_back("苹果");
	fruits.push_back("香蕉");
	fruits.push_back("香蕉");
	fruits.push_back("葡萄");
	fruits.push_back("荔枝"); 
	fruits.push_back("荔枝");
	fruits.push_back("猕猴桃");
	GetFavoriateFruits(fruits, 5);
}
int main()
{
	Test();
	system("pause");
	return 0;
}