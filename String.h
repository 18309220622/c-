#pragma once

#include<iostream>    
#include<cstring>  
#include<assert.h>
using namespace std;

class String   
{  
    friend ostream& operator<<(ostream& os,const String& s);  
    friend istream& operator>>(istream& is,String& s);  
public:  
    String(const char* str="")
		:_sz(strlen(str))  
        ,_capacity(strlen(str)+1)  
        ,_str(new char[strlen(str)+1])  
    {  
          strcpy(_str,str);  
    }  
    String(const String& s)
		:_sz(s._sz)  
        ,_capacity(strlen(s._str)+1)  
        ,_str(new char[strlen(s._str)+1])  
  
    {  
        strcpy(_str,s._str);  
    }  
    ~String()  
    {  
        if(_str!=NULL)  
        {  
            delete[] _str;  
            _str=NULL;  
            _sz=0;  
            _capacity=0;  
  
        }  
    }  
    //String& operator=(const String& s)  
    //{  
    //  if(this!=&s)  
    //  {  
    //      delete[] _str;                     //_str存放'\0'，先将这块空间释放  
    //      _str=new char[strlen(s._str)+1];  //再为_str开辟能存放s._str的足够空间  
    //      strcpy(_str,s._str);     
    //  }  
    //  return *this;  
    //}  
    String& operator=(String s)  
    {  
		if(this!=&s)
		{
			std::swap(_str,s._str);  
            std::swap(_sz,s._sz);  
            std::swap(_capacity,s._capacity);  
		}
        return *this;  
    }  
  
    char* c_str()  
    {  
        return _str;  
    }  
    char& operator[](int index)  
    {  
        return _str[index];  
    }  
    void PushBack(char c)  
    {  
        CheckCapacity(1);  
        _str[_sz]=c;  
        _sz++;  
        _str[_sz]='\0';  
    }  
    String operator+(const String& s)  
    {  
        String tmp;  
        tmp._str=new char[strlen(_str)+strlen(s._str)+1];  
        strcpy(tmp._str,_str);  
        strcat(tmp._str,s._str);  
        return tmp;  
    }  
    String& operator+=(const String& s)  
    {  
        char* tmp=_str;  
        _str=new char[strlen(_str)+strlen(s._str)+1];  
        if(NULL==tmp)  
        {  
            exit(EXIT_FAILURE);  
        }  
        strcpy(_str,tmp);  
        strcat(_str,s._str);  
        return *this;  
    }  
    String& insert(int pos,const char* str)//在指定位置插入字符串  
    {  
        assert(pos<=_sz);          //条件为真继续往下执行  
        int len=strlen(str);  
        CheckCapacity(_sz+len+1);  
        int start=_sz;  
        while(start>=pos)  
        {  
            _str[start+1]=_str[start];  
            start--;  
        }  
        for(int i=0;i<len;i++)  
        {  
            _str[pos]=str[i];  
            pos++;  
        }  
        return *this;  
    }  
    bool operator==(const String& s)  
    {  
        if(strcmp(_str,s._str)==0)  
        {  
            return true;  
        }  
        else  
            return false;  
    }  
private:  
    void CheckCapacity(int count)  
    {  
        if(_sz+count>=_capacity)  
        {  
            int newcapacity=(2*_capacity>_capacity+count)  
                ?(2*_capacity):(_capacity+count);  
            char* tmp=new char[newcapacity];  
            if(NULL==tmp)  
            {  
                exit(EXIT_FAILURE);  
            }  
            strcpy(tmp,_str);  
            delete[] _str;  
            _str=tmp;  
            _capacity=newcapacity;  
        }  
    }  
private:  
    char* _str;  
    int _sz;  
    int _capacity;  
};  
ostream& operator<<(ostream& os,const String& s)  
{  
    os<<s._str<<endl;  
    return os;  
}  
istream& operator>>(istream& is,String& s)  
{  
    is>>s._str;  
    return is;  
}  