#include<iostream>
#include<assert.h>
using namespace std;
//memcpy在进行拷贝时所给两块内存必须是不相关联的
void* Memcopy(void* dst, const void* src, size_t count)
{
	char* pdst = (char*)dst;     //为了能够在拷贝时一个字节一个字节的拷贝所以强转
	const char* psrc = (const char*)src;
	assert(dst);
	assert(src);
	while (count--)
	{
		*pdst++ = *psrc++;
	}
	return dst;
}
void Test1()
{
	char* src = "hello world";
	char arr[20];
	Memcopy(arr, src, strlen(src));
	arr[strlen(src)] = '\0';
	printf("%s\n", arr);
}
void Test2()
{
	int a[] = { 1, 2, 3, 4, 5, 6 };
	Memcopy(a, a + 3, 3 * sizeof(int));
	for (int i = 0; i<6; ++i)
	{
		printf("%d", a[i]);   //4 5 6 4 5 6  
	}
}
//int main()
//{
//	//Test1();
//	Test2();
//	system("pause");
//	return 0;
//}

//memmove与memcpy的区别在于memmove支持相关联的或不相关联的两块内存间的拷贝（拷贝从后向前进行）
void* Memmove(void* dst, const void* src, size_t count)
{
	assert(dst);
	assert(src);
	char* pdst = (char*)dst;
	const char* psrc = (const char*)src;
	if ((pdst > psrc) && (pdst < psrc + count))
	{
		while (count--)
		{
			*(pdst + count) = *(psrc+count);
		}
	}
	else     //pdst<psrc
	{
		while (count--)
		{
			*pdst++ = *psrc++;
		}
	}
	return dst;
}
void Test()
{
	int a[] = {1,2,3,4,5,6,7,8};
	Memmove(a + 2, a, 2 * sizeof(int));   //count为2个int型数据，拷贝a数组中的两个数据放到a+2的位置处
	for (size_t i = 0; i < 8; ++i)
	{
		cout << a[i]<<" ";       //1 2 1 2 5 6 7 8 
	}
	cout << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}

//给两个文件，分别有100亿个URL，我们只有1G内存，如何找到两个文件交集？分别给出精确算法和近似
//算法。（设计出解决方案）
//100亿个URL如果按照一个URL是10个字节算的话，那么大概需要100亿*10字节，这样大致需要100G容量。（100*1024*1024*1024）
//1.精确算法可以通过哈希切分的方式，首先把100G容量切分成1000个文件，然后利用字符串哈希算法求得
//整数再和文件数量进行取模操作，把不同的URL放到不同编号的文件里，相同的URL通过相同的字符串哈希
//算法肯定会进入相同编号的文件里，这样只需要将相同编号的文件加载进内存取比较即可，最后找到两个
//文件的交集。

//2.近似算法：可以通过布隆过滤器，假设现在两个文件分别为A，B，需要知道的是1G所对应的是86
//亿个比特位左右（1024*1024*1024*8），然后我们把A文件里的URL进行不同的几种字符串哈希算法，先在
//1G内存上构造布隆设置位，然后拿B文件里的URL进行相同的字符串哈希算法和1G的进行布隆Test。如果存
//在，那么就是交集，这种算法肯定会有误判概率。
