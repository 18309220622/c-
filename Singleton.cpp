#include<iostream>
using namespace std;
#include<mutex>
#include<assert.h>
//不考虑线程安全的一个单例类
#include<windows.h>

class AutoLock
{
public:
	AutoLock(mutex& mtx) :_mtx(mtx)
	{
		_mtx.lock();
	}
	~AutoLock()
	{
		_mtx.unlock();
	}
private:
	//这里传引用是因为加锁解锁是对锁其本身的操作，而不是对它的一份拷贝的操作
	mutex& _mtx;   //其次也不能加const，是因为加锁解锁会改变内部的引用计数；
};


//懒汉模式
//class Singleton
//{
//public:
//	// 获取唯一对象实例的接口函数
//	//这个接口本来就是去获得一个对象的，所以还有对象之前必须用静态成员函数形式去调用
//	//static修饰的静态成员函数是属于整个类的，通过类域来调接口
//	static Singleton* GetInstance()
//	{
//		// 使用双重检查，提高效率，避免高并发场景下每次获取实例对象都进行加锁
//		if (_inst == NULL)
//		{
//			//_mtx.lock();
//			AutoLock lock(_mtx);
//			if (_inst == NULL)
//			{
//				Singleton* tmp = new Singleton();
//				//加入内存栅栏进行处理，防止编译器重排栅栏后面的赋值到内存栅栏之前
//				MemoryBarrier();
//				_inst = tmp;
//			}
//			//_mtx.unlock();	
//		}
//		return _inst;
//	}
//	void Print()
//	{
//		cout << "_count=" << _count << endl;
//	}
//private:
//	//防拷贝，如果一个对象从接口获得，然后再掉拷贝构造就不符合单例模式的规则
//	Singleton(const Singleton&);
//	Singleton& operator=(const Singleton&);
//private:
//	// 构造函数定义为私有，限制只能在类内创建对象
//	Singleton() :_count(1)
//	{}
//	int _count;
//	static mutex _mtx;
//	static Singleton* _inst;   //因为静态成员函数不能调用非静态成员函数
//	//所以该数据成员也必须加上static
//};
//Singleton* Singleton::_inst = NULL;   //静态成员函数必须在类外初始化

//恶汉模式实现一
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		assert(_inst);
//		return _inst;
//	}
//	void Print()
//	{
//		cout << "_data="<<_data << endl;
//	}
//private:
//	Singleton(const Singleton&); //防拷贝
//	Singleton& operator=(const Singleton&);
//	Singleton() :_data(10)
//	{}
//	int _data;
//	//指向实例的指针定义为静态私有，这样定义静态成员函数获取对象实例
//	static Singleton* _inst;
//};
////利用静态成员变量初始化在调main函数之前的特性实现
//Singleton* Singleton::_inst = new Singleton; 
//
//int main()
//{
//	Singleton::GetInstance()->Print();
//	system("pause");
//	return 0;
//}

class Singleton
{
public:
	static Singleton* GetInstance()
	{
		static Singleton inst;
		return &inst;
	}
	void Print()
	{
		cout << "_data=" << _data << endl;
	}
private:
	Singleton(const Singleton&); //防拷贝
	Singleton& operator=(const Singleton&);
	Singleton() :_data(10)  //私有构造函数
	{}
	int _data;
};

int main()
{
	Singleton::GetInstance()->Print();
	
	system("pause");
	return 0;
}