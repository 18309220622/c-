

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        bool res=false;
        
        if(pRoot1 && pRoot2)
         {
			 //如果两树的根节点值相同再递归判断左右子树的节点值是否相同
            if(pRoot1->val == pRoot2->val)
                res=IsTree1HaveTree2(pRoot1,pRoot2);
        
            if(!res)
                res=HasSubtree(pRoot1->left, pRoot2);
        
            if(!res)
                res=HasSubtree(pRoot1->right, pRoot2);
        }    
        return res;
    }
private:
    bool IsTree1HaveTree2(TreeNode* pRoot1,TreeNode* pRoot2)
        {
        //递归返回条件，树2走完,且每个节点都是和树1的节点相同
        if(pRoot2==NULL)
            return true;
        
        if(pRoot1==NULL)
            return false;
        
        if(pRoot1->val != pRoot2->val)
            return false;
        
        return IsTree1HaveTree2(pRoot1->left,pRoot2->left) 
            && IsTree1HaveTree2(pRoot1->right,pRoot2->right);
    }
};