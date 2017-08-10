#include<iostream>
#include<assert.h>
using namespace std;
//模拟实现C库的atoi和itoa
#include<stdio.h>  
#include<stdlib.h>  
#include<assert.h>   
int status = 0;                     //设置全局变量来记录是不是正常返回    
int my_atoi(const char *str)
{
	long long num = 0;
	int flag = 1;              //设置标记    
	assert(str);
	while (*str == ' ')         //跳过字符串开头的空格    
	{
		str++;
	}
	while (*str == '\0')      //如果全部字符串中都是空格    
	{
		status = 1;            //将state设置成1，表示异常返回    
		return 0;
	}
	if (*str == '-')          //跳过空格后，再判断有没有'-'和'+'    
	{
		flag = -1;            //如果是‘-’，则将flag设置成-1    
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while ((*str) && (*str >= '0') && (*str <= '9'))          //判断是不是数字字符    
	{
		if ((num >= (signed int)0x80000000) && (num <= (signed int)0x7FFFFFFF)) //判断有没有溢出    
		{
			num = num * 10 + flag*(*str - '0');      //将标记位加上去    
			str++;
		}
		else                                         //如果溢出，则跳出    
			break;
	}
	if (*str != '\0')
	{
		status = 1;
		return 0;                        //异常情况  
	}
	return (int)num;
}
//int main()
//{
//	//const char *str = "0";
//	//const char* str = "     -12344abcd678";
//	//const char* str = "     -12344";
//	//const char* str = "     bb1234";
//	const char* str = "     1234";
//	int  ret = my_atoi(str);
//	if (status == 1)
//	{
//		printf("异常返回\n");
//	}
//	printf("%d\n", ret);
//	system("pause");
//	return 0;
//}

//itoa() :char *itoa(int value, char *string, int radix);
//原型说明：
//value：欲转换的数据。
//string：目标字符串的地址。
//radix：转换后的进制数，可以是10进制、16进制等，范围必须在 2 - 36。

//功能：将整数value 转换成字符串存入string 指向的内存空间, radix 为转换时所用基数(保存到字符
//串中的数据的进制基数)。
//返回值：函数返回一个指向 str，无错误返回。
char* my_itoa(int val, char* str, int radix)
{
	char range[37] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char arr[100] = { 0 };

	int sum = val;   
	char *ptr = str;
	int i = 0;

	if (radix<2 || radix>36)//如果进制转化范围是2-36之外的就转化错误  
	{
		cout << "change error!" << endl;
		return str;
	}

	if (val<0)   //不能实现负数的转换
	{
		cout << "change error!" << endl;
		return str;
	}

	while (sum>0)
	{
		arr[i++] = range[sum%radix];
		sum /= radix;
	}

	for (int j = i - 1; j >= 0; j--)
	{
		*ptr++ = arr[j];
	}
	*ptr = '\0';
	return str;
}
int main()
{
	int num = 1000;     //想要转化的数字
	char arr[100] = { 0 };
	for (int j = 2; j <= 36; j++)   //对100转化为2-36范围的进制数值
	{
		my_itoa(num, arr, j);
		cout << arr << endl;
	}
	system("pause");
	return 0;
}
//给一个超过100G的log file, log中存着IP地址, 设计算法找到出现次数最多的100个IP地址？
//利用哈希切分的思想，把100G大小的log file分为1000份，那么每一个文件差不多就是100M左右，然后
//再利用哈希函数除留余数的方法分到对应的编号文件中，然后得出每个文件中出现次数最多的IP
//最后采用建100个数的小堆，用其他900个小文件中出现最多次数的进行与堆顶数据进行比较，从而得出
//这1000个ip中出现次数最多100个IP地址。