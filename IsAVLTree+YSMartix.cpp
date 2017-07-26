#include<iostream>
using namespace std;
struct BinaryTreeNode
{
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	BinaryTreeNode* _parent;
	int _key;
	int _bf;
	BinaryTreeNode(int key)
		:_key(key)
		, _bf(0)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};
class BinaryTree
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	bool Insert(const int& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;   //该值已经存在，不能重复插入
		}
		//找到cur为空位置进行插入
		cur = new Node(key);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//检查是否平衡，如果不平衡更新平衡因子
		parent = cur->_parent;
		while (parent)
		{
			if (parent->_left == cur)
				parent->_bf--;
			if (parent->_right == cur)
				parent->_bf++;
		
			if (parent->_bf == 0)
				break;            //说明插入节点后不影响平衡
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//说明树的高度变了，需要继续往上调整
				cur = parent;
				parent = cur->_parent;
			}
			else
			{
				//parent->_bf == 2 || parent->_bf == -2
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)   //需要左单旋
						_RotateL(parent);

					else        //需要右左单旋
						_RotateRL(parent);
					
				}
				else if (parent->_bf == -2)
				{
					if (cur->_bf == -1)   //需要右单旋
						_RotateR(parent);

					else        //需要左右单旋
						_RotateLR(parent);
				}
			}
		}
	}
	bool IsAVLTree()
	{
		return _IsBalance(_root);
	}
	bool IsAVLTreeOP()
	{
		size_t Height = 0;
		return _IsBalanceOP(_root,Height);
	}

	void MirrorBinaryTree()
	{
		_MirrorBinaryTree(_root);
	}
private:
	void _MirrorBinaryTree(Node* root)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL && root->_right == NULL)
			return;
		Node* tmp = root->_left;
		root->_left = root->_right;
		root->_right = tmp;

		if (root->_left)
			_MirrorBinaryTree(root->_left);
		if (root->_right)
			_MirrorBinaryTree(root->_right);
	}
	bool _IsBalanceOP(Node*& root, size_t& Height)   //通过参数的方式每次把高度带上，下次就不用再重新计算已有的高度
	{
		if (root == NULL)
			return true;
		size_t LeftHeight = 0;
		size_t RightHeight = 0;
		//只要左子树不平衡或右子树不平衡，该树就不平衡
		if (_IsBalanceOP(root->_left, LeftHeight) == false)
			return false;
		if (_IsBalanceOP(root->_right, RightHeight) == false)
			return false;
		int bf = RightHeight - LeftHeight;
		if (abs(bf) <= 1)
		{
			//带出高度
			Height = LeftHeight > RightHeight ? LeftHeight + 1 : RightHeight + 1;
			return true;
		}
	}
	size_t _Height(Node* root)
	{
		if (root == NULL)
			return 0;
		size_t leftHeight = _Height(root->_left) + 1;
		size_t rightHeight = _Height(root->_right) + 1;
		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}
	
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;
		size_t LeftHeight = _Height(root->_left);
		size_t RightHeight = _Height(root->_right);
		int bf = RightHeight - LeftHeight;
		if (root->_bf != bf)
		{
			cout << "Unbalance:" << root->_key << endl;
			return false;
		}
		return abs(bf)<2  && _IsBalance(root->_left) && _IsBalance(root->_right);
	}
	void _RotateL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		parent->_parent = subR;
		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (ppNode->_right == parent)
				ppNode->_right = subR;
			else
				ppNode->_left = subR;

			subR->_parent = ppNode;
		}
		subR->_bf = parent->_bf = 0;     //更新平衡因子
	}
	void _RotateR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;
		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}
		subL->_bf = parent->_bf = 0;
	}
	void _RotateRL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		_RotateR(parent->_right);
		_RotateL(parent);
		if (bf == 0)  //新增节点  
		{
			parent->_bf = subR->_bf = subRL->_bf = 0;
		}
		else if (bf == -1)  //b处插入  
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else           //c处插入  
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 1;
		}
	}
	void _RotateLR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		_RotateL(parent->_left);
		_RotateR(parent);
		if (bf == 0)  //新增节点  
		{
			parent->_bf = subL->_bf = subLR->_bf = 0;
		}
		else if (bf == -1)  //b处插入  
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else           //c处插入  
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 1;
		}
	}
private:
	Node* _root;
};

void test()
{
	BinaryTree bt;
	//int arr[]={16, 3, 7, 11, 9, 26, 18, 14, 15};
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (size_t i = 0; i < 10; ++i)
	{
		bt.Insert(arr[i]);
	}
	cout<<"balance or unbalance?"<<bt.IsAVLTree()<<endl;
	//cout << "balance or unbalance?"<<" " << bt.IsAVLTreeOP() << endl;

}
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}
#include<assert.h>
bool FindNumInMartix(int martix[][4],int rows,int cols,int key)
{
	assert(martix);
	assert(rows > 0 && cols > 0);
	//先确定好从那个位置开始查找，从右上角或左下角开始一次可以排除一行或一列，效率较高
	int row = 0;      //行
	int col = cols - 1;  //列
	while (row < rows && col >= 0)
	{
		if (martix[row][col] == key)
		{
			return true;
		}
		else if (martix[row][col]>key)
			--col;
		else     //martix[row][col] < key
			++row;
	}
	return false;
}
int main()
{
	int arr[][4] = {1, 2, 8, 9, 2, 4, 9, 12, 4,7,10,13, 6, 8,11,15 };
	int ret = FindNumInMartix(arr, 4, 4, 12);
	if (ret)
	{
		printf("查找成功！\n");
	}
	else
	{
		printf("查找失败！\n");
	}
	system("pause");
	return 0;
}