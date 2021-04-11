/**
		Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

		For example:
		Given the below binary tree and sum = 22,
					  5
					 / \
					4   8
				   /   / \
				  11  13  4
				 /  \    / \
				7    2  5   1
		return
		[
		   [5,4,11,2],
		   [5,8,4,5]
		]
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
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
    	vector<vector<int> > result;
		if(!root)
			return result;
			
		vector<pair<TreeNode *, int> > stkNode;
		stkNode.push_back(pair<TreeNode *, int>(root, sum));
		while(stkNode.size()) {
			pair<TreeNode *, int> node = stkNode[stkNode.size()-1];
			if(node.first->left) 
				stkNode.push_back(pair<TreeNode *, int>(node.first->left, node.second - node.first->val));
			else if(node.first->right) 
				stkNode.push_back(pair<TreeNode *, int>(node.first->right, node.second - node.first->val));
			else {
				if(node.second == node.first->val) {
					vector<int> item;
					for(int i=0; i<stkNode.size(); ++i)
						item.push_back(stkNode[i].first->val);
					result.push_back(item);
				}
				
				stkNode.pop_back();
				while(stkNode.size()) {
					pair<TreeNode *, int> parent = stkNode[stkNode.size()-1];
					if(!parent.first->right || node.first == parent.first->right) {
						node = parent;
						stkNode.pop_back();
					} else {
						stkNode.push_back(pair<TreeNode *, int>(parent.first->right, parent.second - parent.first->val));
						break;
					}
				}
			}
		}
		return result;
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
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
		vector<vector<int> > result;
		if(!root)
			return result;
			
		stack<pair<TreeNode *, int> > stkNodes;
		vector<int> cont;
		stkNodes.push(pair<TreeNode *, int>(root, 0));
		cont.push_back(root->val);
		
		while(!stkNodes.empty()){
			pair<TreeNode *, int> node = stkNodes.top();
			if(node.first->left){
				stkNodes.push(pair<TreeNode *, int>(node.first->left, node.second+node.first->val));
				cont.push_back(node.first->left->val);
			}else if(node.first->right){
				stkNodes.push(pair<TreeNode *, int>(node.first->right, node.second+node.first->val));
				cont.push_back(node.first->right->val);
			}else{
				if(node.second+node.first->val == sum)
					result.push_back(cont);
				while(!stkNodes.empty()){
					pair<TreeNode *, int> nodeparent = stkNodes.top();
					if(node.first == nodeparent.first->right || !nodeparent.first->right){
						stkNodes.pop();
						cont.resize(cont.size()-1);
						node = nodeparent;
					}else{
						stkNodes.push(pair<TreeNode *, int>(nodeparent.first->right, nodeparent.second+nodeparent.first->val));
						cont.push_back(nodeparent.first->right->val);
						break;
					}
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
    vector<vector<int> > pathSum(TreeNode *root, int sum);
private:
    void pathSumSub(TreeNode *root, int sum, vector<vector<int> >&result, vector<int> subresult);

};

vector<vector<int> > Solution::pathSum(TreeNode *root, int sum)
{
	vector<vector<int> > result;
	
	if(!root)
		return result;
		
	vector<int> subresult;
	pathSumSub(root, sum, result, subresult);
}

void Solution::pathSumSub(TreeNode *root, int sum, vector<vector<int> >&result, vector<int> subresult)
{
	if(!root->left && !root->right)
	{
		if(sum == root->val)
		{
			subresult.push_back(root->val);
			result.push_back(subresult);
		}
		return;
	}
	
	if(root->left)
	{
		vector<int> subresult1 =subresult;
		subresult1.push_back(root->val);
		pathSumSub(root->left, sum - root->val, result, subresult1);
	}
	if(root->right)
	{
		vector<int> subresult1 =subresult;
		subresult1.push_back(root->val);
		pathSumSub(root->right, sum - root->val, result, subresult1);
	}
}
