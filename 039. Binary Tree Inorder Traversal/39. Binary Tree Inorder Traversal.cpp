/**
		Given a binary tree, return the inorder traversal of its nodes' values.
		For example:
		Given binary tree {1,#,2,3},
		   1
			\
			 2
			/
		   3
		return [1,3,2].
		Note: Recursive solution is trivial, could you do it iteratively?
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
    vector<int> inorderTraversal(TreeNode *root) {
    	vector<int> result;
		inorderTraversal(root, result);
		return result;
	}
	
	void inorderTraversal(TreeNode *root, vector<int> &result) {
		if(!root)
			return;
		inorderTraversal(root->left, result);
		result.push_back(root->val);
		inorderTraversal(root->right, result);
	}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
		vector<int> result;
		if(!root)
			return result;
		stack<TreeNode *> stkNodes;
		stkNodes.push(root);
		while(!stkNodes.empty()) {
			TreeNode *node = stkNodes.top();
			if(node->left) {
				stkNodes.push(node->left);
			} else if(node->right) {
				result.push_back(node->val);
				stkNodes.push(node->right);
			} else {
				result.push_back(node->val);
				stkNodes.pop();
				while(!stkNodes.empty()) {
					TreeNode *parent = stkNodes.top();
					if(!parent->right) {
						result.push_back(parent->val);
						node = parent;
						stkNodes.pop();
					} else if(node == parent->right) {
						node = parent;
						stkNodes.pop();
					} else {
						result.push_back(parent->val);
						stkNodes.push(parent->right);
						break;
					}
				}
			}
		}
		
		return result;
    }
};





































// Pass2
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
    vector<int> inorderTraversal(TreeNode *root) {
		vector<int> result;
		if(!root)
			return result;
		stack<TreeNode *> stkNodes;
		stkNodes.push(root);
		while(!stkNodes.empty()){
			TreeNode *node = stkNodes.top();
			if(node->left)
				stkNodes.push(node->left);
			else if(node->right){
				result.push_back(node->val);
				stkNodes.push(node->right);
			}else{
				result.push_back(node->val);
				stkNodes.pop();
				while(!stkNodes.empty()){
					TreeNode *parent = stkNodes.top();
					if(node == parent->left){
						result.push_back(parent->val);
						if(parent->right){
							stkNodes.push(parent->right);
							break;
						}
					}
					node = parent;
					stkNodes.pop();
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
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
    	vector<int> result;
		if(!root)
			return result;
		inorderTraversal(root, result);
		return result;
    }
	
    void inorderTraversal(TreeNode *root, vector<int> &result) {
		if(!root)
			return;
		inorderTraversal(root->left, result);
		result.push_back(root->val);
		inorderTraversal(root->right, result);
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
    vector<int> inorderTraversal(TreeNode *root);
    vector<int> inorderTraversal2(TreeNode *root);
    void inorderTraversal(TreeNode *root, vector<int>&data);
};


/**
	use recursion.
 */
vector<int> Solution::inorderTraversal2(TreeNode *root)
{
	vector<int> result;
	inorderTraversal(root, result);
	return result;
}


void Solution::inorderTraversal(TreeNode *root, vector<int>&data)
{
	if(!root)
		return;
	inorderTraversal(root->left, data);
	data.push_back(root->val);
	inorderTraversal(root->right, data);
}



vector<int> Solution::inorderTraversal(TreeNode *root)
{
	vector<int> result;
	if(!root)
		return result;
	
	stack<TreeNode *> stkNodes;
	stkNodes.push(root);
	while(!stkNodes.empty())
	{
		TreeNode *pNode = stkNodes.top();
		if(pNode->left)
			stkNodes.push(pNode->left);
		else if(pNode->right)
		{
			result.push_back(pNode->val);
			stkNodes.push(pNode->right);
		}
		else if(!pNode->left && !pNode->right)
		{
			result.push_back(pNode->val);
			while(!stkNodes.empty())
			{
				stkNodes.pop();
				if(stkNodes.empty())
				{
					break;
				}
				
				TreeNode *pParent = stkNodes.top();
				if(pNode == pParent->left)
				{
					result.push_back(pParent->val);
					if(pParent->right)
					{
						stkNodes.push(pParent->right);
						break;
					}
						
				}
				pNode = pParent;
			}
		}
	}
}
