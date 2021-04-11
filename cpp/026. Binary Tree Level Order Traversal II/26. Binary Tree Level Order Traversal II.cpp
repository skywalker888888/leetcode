/**
		Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

		For example:
		Given binary tree {3,9,20,#,#,15,7},
			3
		   / \
		  9  20
			/  \
		   15   7
		return its bottom-up level order traversal as:
		[
		  [15,7]
		  [9,20],
		  [3],
		]
		confused what "{1,#,2,3}" means? 
		
		See also: 31. Binary Tree Level Order Traversal
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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
    	vector<vector<int> > result;
		if(!root)
			return result;
		
		vector<queue<TreeNode *> > Qs(2);
		stack<vector<int> > intRes;
		vector<int> item;
		
		Qs[0].push(root);
		int flag = 0;
		while(!Qs[flag].empty()) {
			TreeNode *node = Qs[flag].front();
			Qs[flag].pop();
			item.push_back(node->val);
			if(node->left)
				Qs[!flag].push(node->left);
			if(node->right)
				Qs[!flag].push(node->right);
				
			if(Qs[flag].empty()) {
				intRes.push(item);
				item.clear();
				flag = !flag;
			}
		}
		
		while(!intRes.empty()) {
			result.push_back(intRes.top());
			intRes.pop();
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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
    	vector<vector<int> > result;
		if(!root)
			return result;
			
		queue<pair<TreeNode *, int> > queNodes;
		if(root)
			queNodes.push(pair<TreeNode *, int>(root, 0));
		while(!queNodes.empty()){
			pair<TreeNode *, int> node = queNodes.front();
			queNodes.pop();
			if(node.second+1 > result.size())
				result.resize(node.second+1);
			result[node.second].push_back(node.first->val);
			
			if(node.first->left)
				queNodes.push(pair<TreeNode *, int>(node.first->left, node.second+1));
			if(node.first->right)
				queNodes.push(pair<TreeNode *, int>(node.first->right, node.second+1));
		}
		reverse(result.begin(), result.end());
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
    vector<vector<int> > levelOrderBottom(TreeNode *root);
};

vector<vector<int> > Solution::levelOrderBottom(TreeNode *root)
{
	vector<vector<int> > result;
	if(!root)
		return result;
	
	queue<TreeNode *> queueParent, queueChildren;
	queue<TreeNode *> *pQueueParent, *pQueueChildren;
	queueParent.push(root);
	
	pQueueParent = &queueParent;
	pQueueChildren = &queueChildren;
	
	stack<vector<int> > tmpStack;
	while(!pQueueParent->empty())
	{
		vector<int> oneLine;
		// 
		while(!pQueueParent->empty())
		{
			TreeNode *Node = pQueueParent->front();
			pQueueParent->pop();
			
			if(Node->left)
				pQueueChildren->push(Node->left);
			if(Node->right)
				pQueueChildren->push(Node->right);
			
			oneLine.push_back(Node->val);
		}
		
		swap(pQueueParent,  pQueueChildren);
		
		tmpStack.push(oneLine);
	}
	
	while(!tmpStack.empty())
	{
		result.push_back(tmpStack.top());
		tmpStack.pop();
	}
}
