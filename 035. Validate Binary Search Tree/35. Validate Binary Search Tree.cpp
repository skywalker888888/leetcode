#include <iostream>


/**
		Given a binary tree, determine if it is a valid binary search tree (BST).
		Assume a BST is defined as follows:
			The left subtree of a node contains only nodes with keys less than the node's key.
			The right subtree of a node contains only nodes with keys greater than the node's key.
			Both the left and right subtrees must also be binary search trees.
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
    bool isValidBST(TreeNode *root) {
		if(!root)
			return true;
		int minVal, maxVal;
		return isValidBST(root, minVal, maxVal);
    }
	
    bool isValidBST(TreeNode *root, int &minVal, int &maxVal) {
		if(!root->left && !root->right) {
			minVal = maxVal = root->val;
			return true;
		}
		
		minVal = maxVal = root->val;
		if(root->left) {
			int v1, v2;
			bool bLeft = isValidBST(root->left, v1, v2);
			
			if(!bLeft || v2>=root->val)
				return false;
			minVal = v1;
		}
		
		if(root->right) {
			int v1, v2;
			bool bRight = isValidBST(root->right, v1, v2);
			
			if(!bRight || v1<=root->val)
				return false;
			maxVal = v2;
		}
		
		return true;
    }
};

































class Solution {
public:
    bool isValidBST(TreeNode *root) {
    	if(!root)
			return true;
			
		int nMin, nMax;
		return isBST(root, nMin, nMax);
    }
    
	bool isBST(TreeNode *root, int &minValue, int &maxValue) {
		if(!root)
			return true;
		if(!root->right && !root->left) {
			minValue = maxValue = root->val;
			return true;
		}
		
		bool hasValue = false;
		if(root->left) {
			int leftMinValue;
			int leftMaxValue;
			if(!isBST(root->left, leftMinValue, leftMaxValue))
				return false;
			
			hasValue = true;
			if(leftMaxValue >= root->val)
				return false;
			minValue = leftMinValue;
			maxValue = root->val;
		}
		if(!hasValue)
			minValue = maxValue = root->val;
			
		if(root->right) {
			int rightMinValue;
			int rightMaxValue;
			if(!isBST(root->right, rightMinValue, rightMaxValue))
				return false;
			if(rightMinValue <= root->val)
				return false;
			maxValue = rightMaxValue;
		}
		
		return true;
	}
};







// Pass 2
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
    bool isValidBST(TreeNode *root) {
		int nMin, nMax;
		return isValidBSTAux(root, nMin, nMax);
    }
    
	bool isValidBSTAux(TreeNode *root, int &nMin, int &nMax) {
		if(!root)
			return true;
		nMin = root->val;
		nMax = root->val;
		
		if(root->left){
			if(root->left->val >= root->val)
				return false;
			int nMinL, nMaxL;
			bool isValid = isValidBSTAux(root->left, nMinL, nMaxL);
			if(!isValid)
				return false;
			
			if(nMaxL >= root->val)
				return false;
				
			nMin = min(nMin, nMinL);
			nMax = max(nMax, nMaxL);
		}
		
		if(root->right){
			if(root->right->val <= root->val)
				return false;
			int nMinR, nMaxR;
			bool isValid = isValidBSTAux(root->right, nMinR, nMaxR);
			if(!isValid)
				return false;
			if(nMinR <= root->val)
				return false;
			nMin = min(nMin, nMinR);
			nMax = max(nMax, nMaxR);
		}
		
		return true;
	}
};


























struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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
class Solution
{
public:
    bool isValidBST(TreeNode *root);
	
private:
    bool 	isValidBSTSub(TreeNode *root);
	bool	m_bValidPre;
	int		m_nPre;
};

bool Solution::isValidBST(TreeNode *root)
{
	m_bValidPre = false;
	return isValidBSTSub(root);
}


bool Solution::isValidBSTSub(TreeNode *root)
{
	if(!root)
		return true;

	bool bTrue = isValidBSTSub(root->left);
	if(!bTrue)
		return false;
		
	if(m_bValidPre && m_nPre>=root->val)
		return false;
	
	m_nPre = root->val;
	m_bValidPre = true;
	
	return isValidBSTSub(root->right);
}


int main(int argc, char **argv)
{
	TreeNode *pRoot = new TreeNode(0);
	pRoot->left = new TreeNode(-1);
	
	Solution sol;
	
	bool b = sol.isValidBST(pRoot);
	
	std::cout << "b=" << b << "\n";
}