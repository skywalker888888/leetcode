/**
		Given a binary tree, find the maximum path sum.
		The path may start and end at any node in the tree.
		For example:
		Given the below binary tree,
			   1
			  / \
			 2   3
		Return 6.
 */
// pass 3
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode *root) {
		int nMaxLen = 0;
		int nMaxHeight = 0;
		maxPathSum(root, nMaxLen, nMaxHeight);
		return nMaxLen;
    }
	
	void maxPathSum(TreeNode *root, int &nMaxLen, int &nMaxHeight) {
		if(!root) {
			nMaxLen = 0;
			nMaxHeight = 0;
			return;
		}

		nMaxLen = root->val;
		nMaxHeight = root->val;
		
		int nMaxLenLeft, nMaxHeightLeft;
		maxPathSum(root->left, nMaxLenLeft, nMaxHeightLeft);

		int nMaxLenRight, nMaxHeightRight;
		maxPathSum(root->right, nMaxLenRight, nMaxHeightRight);

		if(root->left) {
			nMaxLen = max(nMaxLen, nMaxLenLeft);
			nMaxLen = max(nMaxLen, nMaxHeightLeft+root->val);
			
			nMaxHeight = max(nMaxHeight, nMaxHeightLeft + root->val);
		}
		
		if(root->right) {
			nMaxLen = max(nMaxLen, nMaxLenRight);
			nMaxLen = max(nMaxLen, nMaxHeightRight+root->val);
		
			nMaxHeight = max(nMaxHeight, nMaxHeightRight + root->val);
		}
		
		if(root->left && root->right)
			nMaxLen = max(nMaxLen, nMaxHeightLeft+root->val+nMaxHeightRight);
	}
};





























/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 

// Pass 2 solution 
class Solution
{
public:
	int maxPathSum(TreeNode *root)
	{
		int len, height;
		maxPathSumAux(root, len, height);
		return len;
	}

	void maxPathSumAux(TreeNode *root, int &len, int &height)
	{
		if(!root)
			len = height = 0;
		else if(!root->right && !root->left)
		{
			len = height = root->val;
			return;
		}
		else if(root->right && root->left)
		{
			int lenl, heightl;
			maxPathSumAux(root->left, lenl, heightl);
			
			int lenr, heightr;
			maxPathSumAux(root->right, lenr, heightr);
			
			len = max(lenl, lenr);
			len = max(len, heightl);
			len = max(len, heightr);
			len = max(len, root->val);
			len = max(len, heightl + root->val);
			len = max(len, heightr + root->val);
			len = max(len, heightl + root->val + heightr);
			
			
			height = max(heightl+root->val, heightr+root->val);
			height = max(height, root->val);
		}
		else if(root->left)
		{
			int lenl, heightl;
			maxPathSumAux(root->left, lenl, heightl);
			len = lenl;
			len = max(len, heightl);
			len = max(len, root->val);
			len = max(len, heightl + root->val);
			
			height = root->val;
			height = max(height, heightl + root->val);
		}
		else
		{
			int lenr, heightr;
			maxPathSumAux(root->right, lenr, heightr);
			len = lenr;
			len = max(len, root->val);
			len = max(len, heightr);
			len = max(len, heightr + root->val);
			
			height = root->val;
			height = max(height, heightr + root->val);
		}
	}
};































// Pass 1 solution 
class Solution
{
public:
    int maxPathSum(TreeNode *root);
	
private:
	void	calculateMaxSums(TreeNode *root, int& sumToRoot, int& sumInChild);
	int		max(vector<int>& vals);
};


int Solution::maxPathSum(TreeNode *root)
{
	int sumToRoot, sumInChild;
	calculateMaxSums(root, sumToRoot, sumInChild);
	return sumInChild;
}


void Solution::calculateMaxSums(TreeNode *root, int& sumToRoot, int& sumInChild)
{
	TreeNode *left = root->left;
	TreeNode *right = root->right;

	vector<int> valsFromChildren;
	vector<int> valsInChildren;
	
	int sumToLRoot=0, sumInLChild=0;
	if(left)
	{
		calculateMaxSums(left, sumToLRoot, sumInLChild);
		valsFromChildren.push_back(sumToLRoot+root->val); // from left child
		valsInChildren.push_back(sumInLChild);
		valsInChildren.push_back(sumToLRoot+root->val);
	}

	int sumToRRoot=0, sumInRChild=0;
	if(right)
	{
		calculateMaxSums(right, sumToRRoot, sumInRChild);
		valsFromChildren.push_back(sumToRRoot+root->val);
		valsInChildren.push_back(sumInRChild);
		valsInChildren.push_back(sumToRRoot+root->val);
	}
	
	valsInChildren.push_back(sumToLRoot+root->val+sumToRRoot);

	valsFromChildren.push_back(root->val);
	valsInChildren.push_back(root->val);
	
	// calculate the max path from children to this root node
	sumToRoot = max(valsFromChildren);
	
	// calculate the max path in the whole tree, may include this root node
	sumInChild = max(valsInChildren);
}


int Solution::max(vector<int>& vals)
{
#if 0
	int nMax = 0;
	for(int i=0; i<vals.size(); i++)
	{
		if(!i)
			nMax = vals[i];
		else
			nMax = nMax>vals[i]?nMax:vals[i];
	}
	
	return nMax;
#else
	vector<int>::iterator itr = max_element(vals.begin(), vals.end());
	return *itr;
#endif
}


