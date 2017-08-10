#include<iostream>
#include<assert.h>
using namespace std;
//ģ��ʵ��C���atoi��itoa
#include<stdio.h>  
#include<stdlib.h>  
#include<assert.h>   
int status = 0;                     //����ȫ�ֱ�������¼�ǲ�����������    
int my_atoi(const char *str)
{
	long long num = 0;
	int flag = 1;              //���ñ��    
	assert(str);
	while (*str == ' ')         //�����ַ�����ͷ�Ŀո�    
	{
		str++;
	}
	while (*str == '\0')      //���ȫ���ַ����ж��ǿո�    
	{
		status = 1;            //��state���ó�1����ʾ�쳣����    
		return 0;
	}
	if (*str == '-')          //�����ո�����ж���û��'-'��'+'    
	{
		flag = -1;            //����ǡ�-������flag���ó�-1    
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while ((*str) && (*str >= '0') && (*str <= '9'))          //�ж��ǲ��������ַ�    
	{
		if ((num >= (signed int)0x80000000) && (num <= (signed int)0x7FFFFFFF)) //�ж���û�����    
		{
			num = num * 10 + flag*(*str - '0');      //�����λ����ȥ    
			str++;
		}
		else                                         //��������������    
			break;
	}
	if (*str != '\0')
	{
		status = 1;
		return 0;                        //�쳣���  
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
//		printf("�쳣����\n");
//	}
//	printf("%d\n", ret);
//	system("pause");
//	return 0;
//}

//itoa() :char *itoa(int value, char *string, int radix);
//ԭ��˵����
//value����ת�������ݡ�
//string��Ŀ���ַ����ĵ�ַ��
//radix��ת����Ľ�������������10���ơ�16���Ƶȣ���Χ������ 2 - 36��

//���ܣ�������value ת�����ַ�������string ָ����ڴ�ռ�, radix Ϊת��ʱ���û���(���浽�ַ�
//���е����ݵĽ��ƻ���)��
//����ֵ����������һ��ָ�� str���޴��󷵻ء�
char* my_itoa(int val, char* str, int radix)
{
	char range[37] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char arr[100] = { 0 };

	int sum = val;   
	char *ptr = str;
	int i = 0;

	if (radix<2 || radix>36)//�������ת����Χ��2-36֮��ľ�ת������  
	{
		cout << "change error!" << endl;
		return str;
	}

	if (val<0)   //����ʵ�ָ�����ת��
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
	int num = 1000;     //��Ҫת��������
	char arr[100] = { 0 };
	for (int j = 2; j <= 36; j++)   //��100ת��Ϊ2-36��Χ�Ľ�����ֵ
	{
		my_itoa(num, arr, j);
		cout << arr << endl;
	}
	system("pause");
	return 0;
}
//��һ������100G��log file, log�д���IP��ַ, ����㷨�ҵ����ִ�������100��IP��ַ��
//���ù�ϣ�зֵ�˼�룬��100G��С��log file��Ϊ1000�ݣ���ôÿһ���ļ�������100M���ң�Ȼ��
//�����ù�ϣ�������������ķ����ֵ���Ӧ�ı���ļ��У�Ȼ��ó�ÿ���ļ��г��ִ�������IP
//�����ý�100������С�ѣ�������900��С�ļ��г����������Ľ�����Ѷ����ݽ��бȽϣ��Ӷ��ó�
//��1000��ip�г��ִ������100��IP��ַ��