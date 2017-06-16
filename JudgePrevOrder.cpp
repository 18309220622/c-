#include<iostream>
using namespace std;

class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		//后序遍历 左子树--根结点--右子树
		if (sequence.empty())
			return false;
		int len = sequence.size();
		return JudgePrevOrder(sequence, 0, len);
	}
	bool JudgePrevOrder(vector<int>& sequence, int start, int len)
	{
		int root = sequence[len + start - 1];  //先找到根节点
		//根据二叉搜索树的性质得知，左子树的节点值均小于根节点的，右子树的节点值均大于根节点的

		//先找到属于左子树的节点和右子树的
		int i = start;
		for (; i<len + start - 1; ++i)   //根节点已除外
		{
			if (sequence[i]>root)
				break;
		}

		int j = i;
		for (; j<start + len - 1; ++j)
		{
			if (sequence[j]<root)
				return false;
		}
		//判断左子树是不是二叉搜索树
		if (i>0)
			bool left = JudgePrevOrder(sequence, start, i - start);
		//判断左子树是不是二叉搜索树
		if (i<start + len - 1)
			bool right = JudgePrevOrder(sequence, start, start + len - i - 1);

		return left && right;
	}
};