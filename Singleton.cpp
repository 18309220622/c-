#include<iostream>
using namespace std;
#include<mutex>
#include<assert.h>
//�������̰߳�ȫ��һ��������
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
	//���ﴫ��������Ϊ���������Ƕ����䱾��Ĳ����������Ƕ�����һ�ݿ����Ĳ���
	mutex& _mtx;   //���Ҳ���ܼ�const������Ϊ����������ı��ڲ������ü�����
};


//����ģʽ
//class Singleton
//{
//public:
//	// ��ȡΨһ����ʵ���Ľӿں���
//	//����ӿڱ�������ȥ���һ������ģ����Ի��ж���֮ǰ�����þ�̬��Ա������ʽȥ����
//	//static���εľ�̬��Ա����������������ģ�ͨ�����������ӿ�
//	static Singleton* GetInstance()
//	{
//		// ʹ��˫�ؼ�飬���Ч�ʣ�����߲���������ÿ�λ�ȡʵ�����󶼽��м���
//		if (_inst == NULL)
//		{
//			//_mtx.lock();
//			AutoLock lock(_mtx);
//			if (_inst == NULL)
//			{
//				Singleton* tmp = new Singleton();
//				//�����ڴ�դ�����д�����ֹ����������դ������ĸ�ֵ���ڴ�դ��֮ǰ
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
//	//�����������һ������ӽӿڻ�ã�Ȼ���ٵ���������Ͳ����ϵ���ģʽ�Ĺ���
//	Singleton(const Singleton&);
//	Singleton& operator=(const Singleton&);
//private:
//	// ���캯������Ϊ˽�У�����ֻ�������ڴ�������
//	Singleton() :_count(1)
//	{}
//	int _count;
//	static mutex _mtx;
//	static Singleton* _inst;   //��Ϊ��̬��Ա�������ܵ��÷Ǿ�̬��Ա����
//	//���Ը����ݳ�ԱҲ�������static
//};
//Singleton* Singleton::_inst = NULL;   //��̬��Ա���������������ʼ��

//��ģʽʵ��һ
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
//	Singleton(const Singleton&); //������
//	Singleton& operator=(const Singleton&);
//	Singleton() :_data(10)
//	{}
//	int _data;
//	//ָ��ʵ����ָ�붨��Ϊ��̬˽�У��������徲̬��Ա������ȡ����ʵ��
//	static Singleton* _inst;
//};
////���þ�̬��Ա������ʼ���ڵ�main����֮ǰ������ʵ��
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
	Singleton(const Singleton&); //������
	Singleton& operator=(const Singleton&);
	Singleton() :_data(10)  //˽�й��캯��
	{}
	int _data;
};

int main()
{
	Singleton::GetInstance()->Print();
	
	system("pause");
	return 0;
}