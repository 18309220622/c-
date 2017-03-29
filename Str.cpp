#include<cstdio>
#include<cstdlib>
#include<assert.h>


char* Strrchr(const char* str,int ch)
{
	assert(str);
	const char* pstr=str;
	char* ptr=NULL;
	while(*pstr)
	{
		if(*pstr==ch)
		{
			ptr=(char*)pstr;    //记住第一次出现的位置,如果第二次再出现则更新即可
		}
		pstr++;
	}
	return ptr;
}

int main()
{
	char* str="abbabcdefsab";
	char* ret=Strrchr(str,'d');
	printf("%s\n",ret);
	system("pause");
	return 0;
}

//char* Strchr(const char* str,int ch)
//{
//	assert(str);
//	const char* pstr=str;
//	while(*pstr)
//	{
//		if(*pstr==ch)
//		{
//			return (char*)pstr; 
//		}
//		else
//			pstr++;
//	}
//	return 0;
//}
//int main()
//{
//	char* str="abcdabc";
//	char* ret=Strchr(str,'c');
//	printf("%s\n",ret);
//	system("pause");
//	return 0;
//}

//char* Strrstr(const char* str,const char* arr)
//{
//	assert(str);
//	assert(arr);
//	const char* pstr=str;
//	const char* parr=arr;
//	const char* first=NULL;
//	const char* second=NULL;
//	while(*pstr)
//	{
//		first=pstr;
//		while(*pstr && *parr && *pstr==*parr)
//		{
//			pstr++;
//			parr++;
//		}
//		if(*parr=='\0')
//			second=first;
//
//		pstr=first+1;
//		parr=arr;
//	}
//	if(*pstr=='\0')
//		return (char*)second;
//
//	return 0;
//}
//
//int main()
//{
//	//char* str="where here go!";
//	char* str="here go!";
//	char* arr="ere";
//	char* ret=Strrstr(str,arr);
//	printf("%s\n",ret);
//	system("pause");
//	return 0;
//}

//char* Strstr(const char* str,const char* arr)
//{
//	assert(str);
//	assert(arr);
//	const char* pstr=str;
//	const char* parr=arr;
//	const char* start=NULL;
//	while(*pstr)
//	{
//		start=pstr;
//		while(*pstr && *parr && *pstr==*parr)
//		{
//			pstr++;
//			parr++;
//		}
//		if(*parr=='\0')
//		{
//			return (char*)start;
//		}
//		pstr=start+1;
//		parr=arr;
//	}
//	return 0;
//}
//
//int main()
//{
//	char* str="hello world!";
//	char* arr="ell";
//	char* ret=Strstr(str,arr);
//	printf("%s",ret);
//	system("pause");
//	return 0;
//}
