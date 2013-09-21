/**
		Given a binary tree, find its minimum depth.
		The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
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
    int minDepth(TreeNode *root) {
		if(!root)
			return 0;
			
		queue<pair<TreeNode *, int> > queNodes;
		queNodes.push(pair<TreeNode *, int>(root, 1));
		while(!queNodes.empty()) {
			pair<TreeNode *, int> node = queNodes.front();
			queNodes.pop();
			if(!node.first->left && !node.first->right)
				return node.second;
			if(node.first->left)
				queNodes.push(pair<TreeNode *, int>(node.first->left, node.second+1));
			if(node.first->right)
				queNodes.push(pair<TreeNode *, int>(node.first->right, node.second+1));
		}
		return 0;
    }
};






























 
 
 
/// Pass 2
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
    int minDepth(TreeNode *root) {
		if(!root)
			return 0;
			
		queue<pair<TreeNode *, int> > queNodes;
		queNodes.push(pair<TreeNode *, int>(root, 1));
		while(!queNodes.empty()){
			pair<TreeNode *, int> node = queNodes.front();
			queNodes.pop();
			if(node.first->left)
				queNodes.push(pair<TreeNode *, int>(node.first->left, node.second+1));
			if(node.first->right)
				queNodes.push(pair<TreeNode *, int>(node.first->right, node.second+1));
			if(!node.first->left && !node.first->right)
				return node.second;
		}
		return 0;
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
    int minDepth(TreeNode *root);
};

int Solution::minDepth(TreeNode *root)
{
	if(!root)
		return 0;
		
	if(!root->left && !root->right)
		return 1;
		
	bool bHasMin = false;
	int nMin;
	
	if(root->left)
	{
		int nDepLeft = minDepth(root->left);
		bHasMin = true;
		nMin = nDepLeft;
	}
	
	if(root->right)
	{
		int nDepRight = minDepth(root->right);
		if(!bHasMin)
			nMin = nDepRight;
		else
			nMin = min(nMin, nDepRight);
	}
	return nMin + 1;
}



