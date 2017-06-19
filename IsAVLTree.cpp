class Solution {
public:
	int _Height(TreeNode* root)
	{
		if (root == NULL)
			return 0;
		int left = _Height(root->left);
		int right = _Height(root->right);
		return left>right ? left + 1 : right + 1;
	}

	bool IsBalanced_Solution(TreeNode* pRoot) {
		if (pRoot == NULL)
			return true;
		int left = _Height(pRoot->left);
		int right = _Height(pRoot->right);
		int bf = right - left;

		return abs(bf)<2 && IsBalanced_Solution(pRoot->left)
			&& IsBalanced_Solution(pRoot->right);
	}
};