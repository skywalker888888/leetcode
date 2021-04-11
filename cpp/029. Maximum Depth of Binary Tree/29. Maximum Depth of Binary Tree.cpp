/**
		Given a binary tree, find its maximum depth.
		The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
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
    int maxDepth(TreeNode *root) {
    	if(!root)
			return 0;
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

class Solution {
public:
    int maxDepth(TreeNode *root) {
    	if(!root)
			return 0;
		int result = 0;
		stack<pair<TreeNode *, int> > stkNodes;
		stkNodes.push(pair<TreeNode *, int>(root, 1));
		while(!stkNodes.empty()) {
			pair<TreeNode *, int> node = stkNodes.top();
			stkNodes.pop();
			if(!node.first->left && !node.first->right)
				result = max(result, node.second);
			else {
				if(node.first->left)
					stkNodes.push(pair<TreeNode *, int>(node.first->left, node.second+1));
				if(node.first->right)
					stkNodes.push(pair<TreeNode *, int>(node.first->right, node.second+1));
			}
		}
		
		return result;
    }
};


































 

///////// pass 2
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
    int maxDepth(TreeNode *root) {
		int nMaxDepth = 0;
		queue<pair<TreeNode *, int> > queNodes;
		if(root)
			queNodes.push(pair<TreeNode *, int>(root, 1));
		while(!queNodes.empty()){
			pair<TreeNode *,int> node = queNodes.front();
			queNodes.pop();
			TreeNode *pNode = node.first;
			nMaxDepth = max(nMaxDepth, node.second);
			
			if(pNode->left)
				queNodes.push(pair<TreeNode *, int>(pNode->left, node.second+1));
			if(pNode->right)
				queNodes.push(pair<TreeNode *, int>(pNode->right, node.second+1));
		}
		return nMaxDepth;
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
    int maxDepth(TreeNode *root);
};


int Solution::maxDepth(TreeNode *root)
{
	if(!root)
		return 0;
	
	if(!root->left && !root->right)
		return 1;
		
	int nLeftHeight = maxDepth(root->left);
	int nRightHeight = maxDepth(root->right);
	
	return max(nLeftHeight, nRightHeight) + 1;
}
