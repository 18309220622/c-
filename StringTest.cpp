#include"String.h"

void test1()  
{  
    String s1("abcdef");  
    String s2(s1);  
    String s3;  
    s3=s1;  
    cout<<s1<<endl;  
    cout<<s2<<endl;  
    cout<<s3<<endl;  
}  
void test2()  
{  
    String s1="hello";  
    cout<<*(s1.c_str()+1)<<endl;    //取出第二个字符  
    cout<<strlen(s1.c_str())<<endl;  
    cout<<s1[2]<<endl;  
    s1[4]='a';  
    cout<<s1<<endl;  
}  
void test3()  
{  
    String s1="abcdef";  
    s1.PushBack('k');  
    cout<<s1<<endl;  
}  
void test4()  
{  
    String s1("aacd");  
    String s2("mmnp");  
    String s3;  
    s3=s1+s2;  
    s1+=s2;  
    cout<<s1<<endl;  
    cout<<s3<<endl;  
}  
void test5()  
{  
    String s="aaabb";  
	s.insert(2,"cd");  
    cout<<s.c_str()<<endl;  
}  
int main()  
{  
	//test1();
	//test2();
	//test3();
	test4();
    //test5();  
    system("pause");  
    return 0;  
}  