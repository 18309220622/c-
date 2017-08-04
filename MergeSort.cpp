#include<iostream>
using namespace std;

void _Merge(int* a,int* tmp,int begin1,int end1, int begin2,int end2)
{
	int pos = begin1;    //记录起始位置
	int index = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
		    tmp[index++] = a[begin2++];	
	}
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	memcpy(a+pos,tmp+pos,sizeof(int)*(end2-pos+1));
}
void _DivPart(int* a,int* tmp, int begin, int end)  //切分小区间
{
	if (begin >= end)
		return;         //递归返回条件
	int mid = begin + ((end - begin) >> 1);  //注意优先级问题，一般移位运算符优先级比较低
	_DivPart(a, tmp, 0, mid); 
	_DivPart(a, tmp, mid+1,end);

	_Merge(a,tmp,begin,mid,mid+1,end);
}
void MergeSort(int* a, int len)
{
	if (a == NULL)
		return;
	int* tmp = new int[len];
	_DivPart(a,tmp,0,len-1);
	delete[] tmp;
}
void Test()
{
	int a[] = {6,4,2,7,0,5,6,1,9};
	int len = sizeof(a) / sizeof(a[0]);
	MergeSort(a, len);
	for (size_t i = 0; i < len; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}

//Linux下awk工具默认以空格或Tab键作为列分隔符，先由awk从文本文件中获取第三列，然后交由sort工具
//对第三列数据进行排序。其中$NF表示提取文件中最后一列值，这里和$3的功能一样。
//awk '{print $3}' file | sort
//awk '{print $NF}' file | sort
