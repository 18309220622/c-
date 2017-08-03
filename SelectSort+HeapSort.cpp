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
		int min = left;    //��¼��Сֵ���±�
		int max = left;    //��¼���ֵ���±�
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
	int end = len - 1;  //��¼���һ��Ԫ�ص��±�
	while (end>=0)
	{
		std::swap(a[0],a[end]);
		AdjustDown(a,end,0);      //�ڶ�������������Ҫ�µ���Ԫ�ظ����������������Ǵ��Ŀ�ʼ��
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

//����˾����Ҫ����˾Ա��������������Ա������ʱ����ṩ������ˮ����Ա������Ӫ����
//����ˮ������Ƚ϶࣬����ȴ�ֲ�֪������ˮ���Ƚ��ܻ�ӭ��Ȼ��˾����ÿ��Ա��������
//�Լ���Ե�k��ˮ�������Ҹ�֪�Ѿ�������Ա��ϲ���Ե�ˮ���洢��һ�������С�
//Ȼ��������ͳ�Ƴ�����ˮ�����ֵĴ�����������������ϲ���Ե�ǰk��ˮ����
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
	//����һ��
	//for (size_t i = 0; i < fruits.size(); ++i)
	//{
	//	countMapIt=countMap.find(fruits[i]);
	//	if (countMapIt != countMap.end())
	//	{
	//		countMapIt->second++;    //��ˮ���Ѿ�������ֻ��Ҫ����++
	//	}
	//	countMap.insert(make_pair(fruits[i],1));
	//}
	//��������
	//pair<map<string, int>::iterator, bool> ret;
	//for (size_t i = 0; i < fruits.size(); ++i)
	//{
	//	ret = countMap.insert(make_pair(fruits[i],1));
	//	if (ret.second == false)    //����ʧ��˵����ˮ���Ѿ�����
	//	{
	//		ret.first->second++;   //ret.first��map<string, int>::iterator
	//	}
	//}
	//������������operator[]��ʵ�֣��ڲ���ʵҲ���õ���insert
	for (size_t i = 0; i < fruits.size(); ++i)
	{
		countMap[fruits[i]]++;
	}
	//��ӡ������ˮ���Լ���������Ӧ���ֵĴ���
	countMapIt = countMap.begin();
	while (countMapIt != countMap.end())
	{
		cout << countMapIt->first << " " << countMapIt->second << endl;
		++countMapIt;
	}
	//ǰk��ˮ�������ȼ����е��ڲ�ʵ�־���ͨ������(��vector���Ԫ��)
	priority_queue< vector<map<string, int>::iterator>, Less> q;
	countMapIt = countMap.begin();
	while (countMapIt != countMap.end())
	{
		q.push(countMapIt);
		++countMapIt;
	}
	for (size_t i = 0; i < k; ++i)
	{
		cout << "����ˮ����" << q.top()->first << " " << "���ֵĴ���:" << q.top()->second << endl;
		q.pop();
	}
}
void Test()
{
	vector<string> fruits;
	fruits.push_back("ƻ��");
	fruits.push_back("�㽶");
	fruits.push_back("����");
	fruits.push_back("ƻ��");
	fruits.push_back("����");
	fruits.push_back("ƻ��");
	fruits.push_back("�㽶");
	fruits.push_back("�㽶");
	fruits.push_back("����");
	fruits.push_back("��֦"); 
	fruits.push_back("��֦");
	fruits.push_back("⨺���");
	GetFavoriateFruits(fruits, 5);
}
int main()
{
	Test();
	system("pause");
	return 0;
}