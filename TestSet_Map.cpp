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
//	    cout << "不存在该种水果！" << endl;
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
//		it = ret.first; */   //这样在下面的插入过程中是最高效的，it是指向20的地方
//	mySet.insert(it,23);
//	mySet.insert(it,24);
//	mySet.insert(it,22);
//	int arr[] = {5,11,15};
//	mySet.insert(arr,arr+3);    //插入一段区间
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
//	if (it!=mySet.end())  //一定要判断，否则迭代器失效会造成内存泄露
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
//	string fruits[] = {"西瓜","苹果","葡萄","西瓜","香蕉","苹果","西瓜","葡萄"};
//	for (int i = 0; i < sizeof(fruits) / sizeof(fruits[0]); ++i)
//	{
//		//先查找，找到则只需改val值，否则插入
//		ItMap = countMap.find(fruits[i]);
//		if (ItMap != countMap.end())
//		{
//			//找到
//			ItMap->second++;
//		}
//		countMap.insert(make_pair(fruits[i],1));   //第一次插入，val置为1
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
//	string fruits[] = {"西瓜","苹果","葡萄","西瓜","香蕉","苹果","西瓜","葡萄"};
//	for (int i = 0; i < sizeof(fruits) / sizeof(fruits[0]); ++i)
//	{
//		ret = countMap.insert(make_pair(fruits[i],1));
//		if (ret.second == false)  //插入失败，说明已经存在
//			ret.first->second++;  //ret.first的first成员为map<string, int>::iterator
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
	string fruits[] = { "西瓜", "苹果", "葡萄", "西瓜", "香蕉", "苹果", "西瓜", "葡萄" };
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