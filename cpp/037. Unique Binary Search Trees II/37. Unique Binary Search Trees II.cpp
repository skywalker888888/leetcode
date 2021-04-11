/**
		Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.
		For example,
		Given n = 3, your program should return all 5 unique BST's shown below.

		   1         3     3      2      1
			\       /     /      / \      \
			 3     2     1      1   3      2
			/     /       \                 \
		   2     1         2                 3
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
    vector<TreeNode *> generateTrees(int n) {
		return generateTrees(1, n);
    }
    vector<TreeNode *> generateTrees(int i, int j) {
		vector<TreeNode *> result;
		if(i > j) {
			result.push_back(NULL);
			return result;
		}
		
		for(int k=i; k<=j; ++k) {
			vector<TreeNode *> r1 = generateTrees(i, k-1);
			vector<TreeNode *> r2 = generateTrees(k+1, j);
			for(int m=0; m<r1.size(); ++m)
				for(int n=0; n<r2.size(); ++n) {
					TreeNode *root = new TreeNode(k);
					root->left = r1[m];
					root->right = r2[n];
					result.push_back(root);
				}
		}
		return result;
	}
};











































// pass 2
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
	// Non recursion version
    vector<TreeNode *> generateTrees(int n) {
	
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
class Solution {
public:
    vector<TreeNode *> generateTrees(int n) {
        return generateTrees(1, n);
    }
    vector<TreeNode *> generateTrees(int i, int j) {
    	vector<TreeNode *> result;
		if(i > j){
			result.push_back(NULL);
			return result;
		}
		
		for(int k=i; k<=j; ++k){
			vector<TreeNode *> res1 = generateTrees(i, k-1);
			vector<TreeNode *> res2 = generateTrees(k+1, j);
			if(res1.size() && res2.size()){
				for(int m=0; m<res1.size(); ++m)
					for(int n=0; n<res2.size(); ++n){
						TreeNode *root = new TreeNode(k);
						root->left = res1[m];
						root->right = res2[n];
						result.push_back(root);
					}
			}
		}
		
		return result;
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
    vector<TreeNode *> generateTrees(int n);
    vector<TreeNode *> generateTrees(int i, int j);
};

vector<TreeNode *> Solution::generateTrees(int n)
{
	return generateTrees(1, n);
}
vector<TreeNode *> Solution::generateTrees(int i, int j)
{
	vector<TreeNode *> result;
	if(i>j)
	{
		result.push_back(NULL);
		return result;
	}
	for(int k=i; k<=j; ++k)
	{
		vector<TreeNode *> lgroup = generateTrees(i, k-1);
		vector<TreeNode *> rgroup = generateTrees(k+1, j);
		for(int l=0; l<lgroup.size(); ++l)
		{
			TreeNode *pNodeL = lgroup[l];
			for(int r=0; r<rgroup.size(); ++r)
			{
				TreeNode *pNodeR = rgroup[r];
				TreeNode *pNode = new TreeNode(k);
				pNode->left = pNodeL;
				pNode->right = pNodeR;
				result.push_back(pNode);
			}
		}
	}
	return result;
}

