/**
		Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
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
    TreeNode *sortedArrayToBST(vector<int> &num) {
    	if(num.size() == 0)
			return NULL;
		return sortedArrayToBST(num, 0, num.size()-1);
    }
    TreeNode *sortedArrayToBST(vector<int> &num, int s, int e) {
		if(s > e)
			return NULL;
		else if(s == e)
			return new TreeNode(num[s]);
		
		int m = (s + e)/2;
		TreeNode *root = new TreeNode(num[m]);
		root->left = sortedArrayToBST(num, s, m-1);
		root->right = sortedArrayToBST(num, m+1, e);
		return root;
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
    TreeNode *sortedArrayToBST(vector<int> &num) {
		if(!num.size())
			return NULL;
			
		return sortedArrayToBST(num, 0, num.size()-1);
    }

    TreeNode *sortedArrayToBST(vector<int> &num, int s, int e) {
		if( s > e)
			return NULL;
		
		int mid = (s + e)/2;
		
		// s...mid-1 mid mid+1 ...e
		TreeNode *root = new TreeNode(num[mid]);
		root->left = sortedArrayToBST(num, s, mid-1);
		root->right = sortedArrayToBST(num, mid+1, e);
		return root;
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
class Solution
{
public:
    TreeNode *sortedArrayToBST(vector<int> &num);
private:
    TreeNode *sortedArrayToBST(int i, int j, vector<int> &num);
};

TreeNode *Solution::sortedArrayToBST(vector<int> &num)
{
	int n = num.size();
	if(!n)
		return NULL;
	return sortedArrayToBST(0, n-1, num);
}


TreeNode *Solution::sortedArrayToBST(int i, int j, vector<int> &num)
{
	if(i > j)
		return NULL;
	
	if(i == j)
	{
		TreeNode *pNode = new TreeNode(num[i]);
		return pNode;
	}
	
	if(i == j-1)
	{
		TreeNode *pNode = new TreeNode(num[j]);
		pNode->left  = new TreeNode(num[i]);
		return pNode;
	}
	
	int n = j - i + 1;
	int mid = (i + j) / 2;
	
	// 
	TreeNode *pNode = new TreeNode(num[mid]);
	pNode->left = sortedArrayToBST(i, mid-1, num);
	pNode->right = sortedArrayToBST(mid+1, j, num);
	return pNode;
}
