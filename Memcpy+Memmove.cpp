#include<iostream>
#include<assert.h>
using namespace std;
//memcpy�ڽ��п���ʱ���������ڴ�����ǲ��������
void* Memcopy(void* dst, const void* src, size_t count)
{
	char* pdst = (char*)dst;     //Ϊ���ܹ��ڿ���ʱһ���ֽ�һ���ֽڵĿ�������ǿת
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

//memmove��memcpy����������memmove֧��������Ļ�������������ڴ��Ŀ����������Ӻ���ǰ���У�
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
	Memmove(a + 2, a, 2 * sizeof(int));   //countΪ2��int�����ݣ�����a�����е��������ݷŵ�a+2��λ�ô�
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

//�������ļ����ֱ���100�ڸ�URL������ֻ��1G�ڴ棬����ҵ������ļ��������ֱ������ȷ�㷨�ͽ���
//�㷨������Ƴ����������
//100�ڸ�URL�������һ��URL��10���ֽ���Ļ�����ô�����Ҫ100��*10�ֽڣ�����������Ҫ100G��������100*1024*1024*1024��
//1.��ȷ�㷨����ͨ����ϣ�зֵķ�ʽ�����Ȱ�100G�����зֳ�1000���ļ���Ȼ�������ַ�����ϣ�㷨���
//�����ٺ��ļ���������ȡģ�������Ѳ�ͬ��URL�ŵ���ͬ��ŵ��ļ����ͬ��URLͨ����ͬ���ַ�����ϣ
//�㷨�϶��������ͬ��ŵ��ļ������ֻ��Ҫ����ͬ��ŵ��ļ����ؽ��ڴ�ȡ�Ƚϼ��ɣ�����ҵ�����
//�ļ��Ľ�����

//2.�����㷨������ͨ����¡���������������������ļ��ֱ�ΪA��B����Ҫ֪������1G����Ӧ����86
//�ڸ�����λ���ң�1024*1024*1024*8����Ȼ�����ǰ�A�ļ����URL���в�ͬ�ļ����ַ�����ϣ�㷨������
//1G�ڴ��Ϲ��첼¡����λ��Ȼ����B�ļ����URL������ͬ���ַ�����ϣ�㷨��1G�Ľ��в�¡Test�������
//�ڣ���ô���ǽ����������㷨�϶��������и��ʡ�
