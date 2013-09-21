/**
		Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

		For example:
		Given the below binary tree and sum = 22,
					  5
					 / \
					4   8
				   /   / \
				  11  13  4
				 /  \      \
				7    2      1
		return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
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
    bool hasPathSum(TreeNode *root, int sum) {
    	if(!root)
			return false;
			
		stack<pair<TreeNode *, int> > stkNodes;
		stkNodes.push(pair<TreeNode *, int>(root, sum));
		while(!stkNodes.empty()) {
			pair<TreeNode *,int > node = stkNodes.top();
			if(node.first->left) 
				stkNodes.push(pair<TreeNode *, int>(node.first->left, node.second - node.first->val));
			else if(node.first->right) 
				stkNodes.push(pair<TreeNode *, int>(node.first->right, node.second - node.first->val));
			else {
				if(node.second == node.first->val)
					return true;
				stkNodes.pop();
				while(!stkNodes.empty()) {
					pair<TreeNode *,int > parent = stkNodes.top();
					if(!parent.first->right || node.first==parent.first->right) {
						node = parent;
						stkNodes.pop();
					} else {
						stkNodes.push(pair<TreeNode *, int>(parent.first->right, parent.second - parent.first->val));
						break;
					}
				}
			}
		}
		return false;
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
    bool hasPathSum(TreeNode *root, int sum){
    	bool result = false;
		if(!root)
			return false;
		stack<pair<TreeNode *, int> > stkNodes;
		stkNodes.push(pair<TreeNode *, int>(root, 0));
		while(!stkNodes.empty()){
			pair<TreeNode *, int> node = stkNodes.top();
			if(node.first->left)
				stkNodes.push(pair<TreeNode *, int>(node.first->left, node.second+node.first->val));
			else if(node.first->right)
				stkNodes.push(pair<TreeNode *, int>(node.first->right, node.second+node.first->val));
			else{
				stkNodes.pop();
				if(node.second + node.first->val == sum)
					return true;
				else if(stkNodes.empty())
					break;
				else{
					pair<TreeNode *, int> nodeparent = stkNodes.top();
					while((node.first==nodeparent.first->right || !nodeparent.first->right)){
						node = nodeparent;
						stkNodes.pop();
						if(stkNodes.empty())
							break;
						nodeparent = stkNodes.top();
					}
					if(!stkNodes.empty())
						stkNodes.push(pair<TreeNode *, int>(nodeparent.first->right, nodeparent.second+nodeparent.first->val));
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
    bool hasPathSum(TreeNode *root, int sum);
private:
    bool hasPathSumSub(TreeNode *root, int sum);
};

bool Solution::hasPathSum(TreeNode *root, int sum)
{
	if(!root)
		return false;
		
	return hasPathSumSub(root, sum);
}

bool Solution::hasPathSumSub(TreeNode *root, int sum)
{
	if(!root->left && !root->right)
	{
		if(sum == root->val)
			return true;
		else
			return false;
	}

	if(root->left)
	{
		bool bSucceed = hasPathSumSub(root->left, sum - root->val);
		if(bSucceed)
			return bSucceed;
	}

	if(root->right)
	{
		bool bSucceed = hasPathSumSub(root->right, sum - root->val);
		if(bSucceed)
			return bSucceed;
	}
	
	return false;
}
