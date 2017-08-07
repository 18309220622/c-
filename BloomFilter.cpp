#pragma once
#include"BitMap.hpp"
#include<string>
template<class T>
struct _HashFun1
{
	size_t BKDRHash(const char* str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};

template<class T>
struct _HashFunc2
{
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return SDBMHash(key.c_str());
	}
};

template<typename T>
struct _HashFunc3
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}
};
template<typename T>
struct _HashFunc4
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}
};

template<typename T>
struct _HashFunc5
{
	size_t RSHash(const char *str)
	{
		if (!*str)        // �����ɱ�����ӣ��Ա�֤���ַ������ع�ϣֵ0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}
};

template<typename T = string,
	typename HashFunc1 = _HashFun1<T>,
	typename HashFunc2 = _HashFunc2<T>,
	typename HashFunc3 = _HashFunc3<T>,
	typename HashFunc4 = _HashFunc4<T>,
	typename HashFunc5 = _HashFunc5<T> >
class BloomFilter
{
public:
	BloomFilter(const size_t range)
		: _size(range)
		, _bm(range)
	{}
	//�Բ�¡�������������ã�����ԭ���ͨ���ַ�����ϣ����������ļ���λ��������״̬��
	void BloomSet(const T& key)
	{
		size_t index1 = HashFunc1()(key.c_str()) % _size;
		size_t index2 = HashFunc2()(key.c_str()) % _size;
		size_t index3 = HashFunc3()(key.c_str()) % _size;
		size_t index4 = HashFunc4()(key.c_str()) % _size;
		size_t index5 = HashFunc5()(key.c_str()) % _size;

		_bm.Set(index1);
		cout << index1 << endl;

		_bm.Set(index2);
		cout << index2 << endl;

		_bm.Set(index3);
		cout << index3 << endl;

		_bm.Set(index4);
		cout << index4 << endl;

		_bm.Set(index5);
		cout << index5 << endl << endl;

	}
	
	bool BloomTest(const T& key)
	{
		size_t index1 = HashFunc1()(key.c_str()) % _size;
		if (_bm.Test(index1) == 0)
		{
			return false;
		}
		size_t index2 = HashFunc2()(key.c_str()) % _size;
		if (_bm.Test(index2) == 0)
		{
			return false;
		}
		size_t index3 = HashFunc3()(key.c_str()) % _size;
		if (_bm.Test(index3) == 0)
		{
			return false;
		}
		size_t index4 = HashFunc4()(key.c_str()) % _size;
		if (_bm.Test(index4) == 0)
		{
			return false;
		}
		size_t index5 = HashFunc5()(key.c_str()) % _size;
		if (_bm.Test(index5) == 0)
		{
			return false;
		}
		return true;
	}

protected:
	BitMap _bm;
	size_t _size;
};
int main()
{
	BloomFilter<> bf(100);
	bf.BloomSet("ƻ��");
	bf.BloomSet("HashTable");
	bf.BloomSet("BloomFilter");
	bf.BloomSet("�㽶");
	bf.BloomSet("����");

	cout << "Is Exist?" << bf.BloomTest("HashTable") << endl;   //1
	cout << "Is Exist?" << bf.BloomTest("BloomFilter") << endl; //1
	cout << "Is Exist?" << bf.BloomTest("HashT") << endl;       //0
	cout << "Is Exist?" << bf.BloomTest("HashTable1") << endl;  //0
	cout << "Is Exist?" << bf.BloomTest("ƻ��") << endl;        //1
	cout << "Is Exist?" << bf.BloomTest("����") << endl;        //1

	system("pause");
	return 0;
}

//1.��¡������������׼ȷ�Ļ��ǲ�������׼ȷ�ģ�
//��¡��������鵽�����ڵ�����һ��������,��鵽���ܴ��ڵ����ݣ��ǲ�һ�����ڵģ�
//��Ϊ����������ֵռ�������λ�ã��������������

//2.��¡��������ȱ�㣿
//��¡���������ŵ��ǣ���ʡ�ռ䣬��ѯʱ��ԶԶ����һ����㷨����¡�������洢�ռ�Ͳ��� / ��ѯʱ
//�䶼�ǳ���O(1)������, ɢ�к����໥֮��û�й�ϵ��������Ӳ������ʵ�֡���¡����������Ҫ�洢Ԫ��
//������Ϊ�����洢���������ݵ�״̬����ĳЩ�Ա���Ҫ��ǳ��ϸ�ĳ��������ơ�

//��¡��������ȱ�㣺�������У����Ŵ����Ԫ���������ӣ���������֮���ӡ�

//3.�����չBloomFilterʹ����֧��ɾ��Ԫ�صĲ����������ʵ��һ��֧��ɾ���Ĳ�¡������.
// һ������²��ܴӲ�¡��������ɾ��Ԫ�أ���Ϊ��ĳһ��λ��0�ܿ��ܻ�Ӱ����������ݵ��жϣ�����
//�������뵽��λ�������������飬ÿ����һ��Ԫ����Ӧ�ļ������� 1, ����ɾ��Ԫ��ʱ������������
//�Ϳ����ˡ�Ȼ��Ҫ��֤��ȫ��ɾ��Ԫ�ز�����˼򵥡��������Ǳ��뱣֤ɾ����Ԫ�ص�ȷ�ڲ�¡������
//����. ��һ�㵥ƾ������������޷���֤�ġ��������������Ҳ��������⡣

//public:
//void ReSet(const T& key)
//{
	//size_t index1 = HashFunc1()(key.c_str()) % _bm._size;
	//size_t index2 = HashFunc2()(key.c_str()) % _bm._size;
	//size_t index3 = HashFunc3()(key.c_str()) % _bm._size;
	//size_t index4 = HashFunc4()(key.c_str()) % _bm._size;
	//size_t index5 = HashFunc5()(key.c_str()) % _bm._size;
    //_bm.Set(index1);
    //_bm.Set(index2);
    //_bm.Set(index3);
    //_bm.Set(index4);
    //_bm.Set(index5);
    //if(_bm[index1]>0)    //��ʾ��λ�ѱ����ù�
    //{
    //    --_bm[index1];
     //}
     //if(_bm[index2]>0)
     //{
    //    --_bm[index2];
     //}
     //if(_bm[index3]>0)
    //{
    //    --_bm[index3];
    //}
    //if(_bm[index4]>0)
    //{
    //    --_bm[index4];
    //}
    //if(_bm[index5]>0)
    //{
    //   --_bm[index5];
    //}
//protected: 
	//vector<short> _bm;