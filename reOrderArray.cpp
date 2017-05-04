#include<iostream>
#include<vector>

void reOrderArray(std::vector<int> &array) {
        if(array.size()==0 || array.size()==1)
            return ;
        
        std::vector<int> res;
        for(int i=0;i< array.size();++i)
            {
            if(array[i] % 2 == 1)
                {
                res.push_back(array[i]);
            }
        }
        
        for(int i=0;i< array.size();++i)
            {
            if(array[i]%2==0)
                res.push_back(array[i]);
        }
        array=res;
    }

int main()
{
	std::vector<int> arr;
	for(int i=1;i<8;i++)
	{
		arr.push_back(i);
	}
	reOrderArray(arr);
	for(int i=0;i<arr.size();++i)
	{
		std::cout<<arr[i]<<" ";
	}
	std::cout<<std::endl;
	system("pause");
	return 0;
}