#include<set>
#include<map>
#include<iostream>
#include<string>
using namespace std;

//void TestSet()
//{
//	set<string> mySet;
//	string fruits[] = {"apple","banana","pear","strawberry","grape"};
//	for (int i = 0; i < sizeof(fruits) / sizeof(fruits[0]); i++)
//	{
//		mySet.insert(fruits[i]);
//	}
//	set<string>::iterator it = mySet.begin();
//	//if (it == mySet.find("apple"))
//	if (it == mySet.find("watermelon"))
//		cout << *it << endl;
//	else
//	    cout << "�����ڸ���ˮ����" << endl;
//}

//void TestSet()
//{
//	set<int> mySet;
//	set<int>::iterator it;
//	pair<set<int>::iterator, bool> ret;
//	for (int i = 0; i < 5; ++i)
//		mySet.insert(i*10);
//
//	it = mySet.find(20);
//	/*ret=mySet.insert(20);
//	if (ret.second == false)
//		it = ret.first; */   //����������Ĳ�������������Ч�ģ�it��ָ��20�ĵط�
//	mySet.insert(it,23);
//	mySet.insert(it,24);
//	mySet.insert(it,22);
//	int arr[] = {5,11,15};
//	mySet.insert(arr,arr+3);    //����һ������
//	it = mySet.begin();
//	while(it != mySet.end())
//	{
//		cout << *it << " ";
//		++it;
//	}            //0 5 10 11 15 20 22 23 24 30 40
//	cout << endl;
//	set<int>::iterator first;
//	set<int>::iterator second;
//	first = mySet.lower_bound(10);
//	second = mySet.upper_bound(21);
//	mySet.erase(first,second);
//
//	it = mySet.find(10);  
//	if (it!=mySet.end())  //һ��Ҫ�жϣ����������ʧЧ������ڴ�й¶
//		mySet.erase(it);
//
//	it = mySet.begin();
//	while (it != mySet.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//}


//void TestMap()
//{
//	map<string, int> countMap;
//	map<string, int>::iterator ItMap;
//	string fruits[] = {"����","ƻ��","����","����","�㽶","ƻ��","����","����"};
//	for (int i = 0; i < sizeof(fruits) / sizeof(fruits[0]); ++i)
//	{
//		//�Ȳ��ң��ҵ���ֻ���valֵ���������
//		ItMap = countMap.find(fruits[i]);
//		if (ItMap != countMap.end())
//		{
//			//�ҵ�
//			ItMap->second++;
//		}
//		countMap.insert(make_pair(fruits[i],1));   //��һ�β��룬val��Ϊ1
//	}
//	ItMap = countMap.begin();
//	while (ItMap != countMap.end())
//	{
//		cout << ItMap->first <<"  "<< ItMap->second << endl;
//		++ItMap;
//	}
//}

//void TestMap()
//{
//	map<string, int> countMap;
//	map<string, int>::iterator ItMap;
//	pair<map<string, int>::iterator, bool> ret;
//	string fruits[] = {"����","ƻ��","����","����","�㽶","ƻ��","����","����"};
//	for (int i = 0; i < sizeof(fruits) / sizeof(fruits[0]); ++i)
//	{
//		ret = countMap.insert(make_pair(fruits[i],1));
//		if (ret.second == false)  //����ʧ�ܣ�˵���Ѿ�����
//			ret.first->second++;  //ret.first��first��ԱΪmap<string, int>::iterator
//	}
//	ItMap = countMap.begin();
//	while (ItMap != countMap.end())
//	{
//		cout << ItMap->first << "  " << ItMap->second << endl;
//		++ItMap;
//	}
//}
void TestMap()
{
	map<string, int> countMap;
	map<string, int>::iterator ItMap;
	pair<map<string, int>::iterator, bool> ret;
	string fruits[] = { "����", "ƻ��", "����", "����", "�㽶", "ƻ��", "����", "����" };
	for (int i = 0; i < sizeof(fruits) / sizeof(fruits[0]); ++i)
	{
		countMap[fruits[i]]++;
	}
	ItMap = countMap.begin();
	while (ItMap != countMap.end())
	{
		cout << ItMap->first << "  " << ItMap->second << endl;
		++ItMap;
	}
}

int main()
{
	//TestSet();
	TestMap();
	system("pause");
	return 0;
}