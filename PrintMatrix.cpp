#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	    vector<int> printMatrix(vector<vector<int> > matrix) {
		
		vector<int> res;
        int rows = matrix.size();
		int cols = matrix[0].size();
		//如果原数组为空，则返回空vector-->res
		if (matrix.empty())
			return res;

		int left = 0;
		int right = cols - 1;
		int top = 0;
		int below = rows - 1;
		while (left <= right && top <= below)
		{
			//注意四个拐角点的控制，防止重复打印
			//from left to right
			for (int i = left; i <= right; i++)
			{
				//行不变，列变
				res.push_back(matrix[top][i]);
			}
			//from top to below
			for (int i = top + 1, i <= below; i++)
			{
				//行变，列不变
				res.push_back(matrix[i][right]);
			}
			//from right to left
			if (top != below)
			{
				for (int i = right - 1; i >= left; i--)
				{
					//行不变，列变
					res.push_back(matrix[below][i]);
				}
			}

			//from below to top
			if (left != right)
			{
				for (int i = below - 1; i>top; i--)
				{
					res.push_back(matrix[i][left]);
				}
			}

			//以上是走完一圈的，控制剩下的需要改变left,right,top,below
			left++; right--;
			top++; below--;
		}
		return res;
	}
};