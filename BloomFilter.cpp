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
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
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
	//对布隆过滤器进行设置，根据原理对通过字符串哈希函数所计算的几个位进行设置状态。
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
	bf.BloomSet("苹果");
	bf.BloomSet("HashTable");
	bf.BloomSet("BloomFilter");
	bf.BloomSet("香蕉");
	bf.BloomSet("葡萄");

	cout << "Is Exist?" << bf.BloomTest("HashTable") << endl;   //1
	cout << "Is Exist?" << bf.BloomTest("BloomFilter") << endl; //1
	cout << "Is Exist?" << bf.BloomTest("HashT") << endl;       //0
	cout << "Is Exist?" << bf.BloomTest("HashTable1") << endl;  //0
	cout << "Is Exist?" << bf.BloomTest("苹果") << endl;        //1
	cout << "Is Exist?" << bf.BloomTest("橘子") << endl;        //1

	system("pause");
	return 0;
}

//1.布隆过滤器存在是准确的还是不存在是准确的？
//布隆过滤器检查到不存在的数据一定不存在,检查到可能存在的数据，是不一定存在的，
//因为可能是其他值占据了这个位置，存在误判情况。

//2.布隆过滤器优缺点？
//布隆过滤器的优点是：节省空间，查询时间远远超过一般的算法，布隆过滤器存储空间和插入 / 查询时
//间都是常数O(1)。另外, 散列函数相互之间没有关系，方便由硬件并行实现。布隆过滤器不需要存储元素
//本身，因为它所存储的是它数据的状态，在某些对保密要求非常严格的场景有优势。

//布隆过滤器的缺点：存在误判，随着存入的元素数量增加，误算率随之增加。

//3.如何扩展BloomFilter使得它支持删除元素的操作？请设计实现一个支持删除的布隆过滤器.
// 一般情况下不能从布隆过滤器中删除元素，因为把某一个位置0很可能会影响对其他数据的判断，我们
//很容易想到把位数组变成整数数组，每插入一个元素相应的计数器加 1, 这样删除元素时将计数器减掉
//就可以了。然而要保证安全地删除元素并非如此简单。首先我们必须保证删除的元素的确在布隆过滤器
//里面. 这一点单凭这个过滤器是无法保证的。另外计数器回绕也会造成问题。

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
    //if(_bm[index1]>0)    //表示该位已被设置过
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