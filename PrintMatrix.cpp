#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	    vector<int> printMatrix(vector<vector<int> > matrix) {
		
		vector<int> res;
        int rows = matrix.size();
		int cols = matrix[0].size();
		//���ԭ����Ϊ�գ��򷵻ؿ�vector-->res
		if (matrix.empty())
			return res;

		int left = 0;
		int right = cols - 1;
		int top = 0;
		int below = rows - 1;
		while (left <= right && top <= below)
		{
			//ע���ĸ��սǵ�Ŀ��ƣ���ֹ�ظ���ӡ
			//from left to right
			for (int i = left; i <= right; i++)
			{
				//�в��䣬�б�
				res.push_back(matrix[top][i]);
			}
			//from top to below
			for (int i = top + 1, i <= below; i++)
			{
				//�б䣬�в���
				res.push_back(matrix[i][right]);
			}
			//from right to left
			if (top != below)
			{
				for (int i = right - 1; i >= left; i--)
				{
					//�в��䣬�б�
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

			//����������һȦ�ģ�����ʣ�µ���Ҫ�ı�left,right,top,below
			left++; right--;
			top++; below--;
		}
		return res;
	}
};