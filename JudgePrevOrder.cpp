#include<iostream>
using namespace std;

class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		//������� ������--�����--������
		if (sequence.empty())
			return false;
		int len = sequence.size();
		return JudgePrevOrder(sequence, 0, len);
	}
	bool JudgePrevOrder(vector<int>& sequence, int start, int len)
	{
		int root = sequence[len + start - 1];  //���ҵ����ڵ�
		//���ݶ��������������ʵ�֪���������Ľڵ�ֵ��С�ڸ��ڵ�ģ��������Ľڵ�ֵ�����ڸ��ڵ��

		//���ҵ������������Ľڵ����������
		int i = start;
		for (; i<len + start - 1; ++i)   //���ڵ��ѳ���
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
		//�ж��������ǲ��Ƕ���������
		if (i>0)
			bool left = JudgePrevOrder(sequence, start, i - start);
		//�ж��������ǲ��Ƕ���������
		if (i<start + len - 1)
			bool right = JudgePrevOrder(sequence, start, start + len - i - 1);

		return left && right;
	}
};