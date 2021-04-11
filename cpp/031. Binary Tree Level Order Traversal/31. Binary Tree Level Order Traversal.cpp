/**
		Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

		For example:
		Given binary tree {3,9,20,#,#,15,7},
			3
		   / \
		  9  20
			/  \
		   15   7
		return its level order traversal as:
		[
		  [3],
		  [9,20],
		  [15,7]
		]
				
		OJ's Binary Tree Serialization:
		The serialization of a binary tree follows a level order traversal, where '#' signifies a path terminator where no node exists below.

		Here's an example:
		   1
		  / \
		 2   3
			/
		   4
			\
			 5
		The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
		
		See also: 26. Binary Tree Level Order Traversal II
		
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
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > result;
		if(!root)
			return result;
		vector<queue<TreeNode *> > Qs(2);
		Qs[0].push(root);
		int flag = 0;
		vector<int> item;
		while(!Qs[flag].empty()) {
			TreeNode *node = Qs[flag].front();
			item.push_back(node->val);
			Qs[flag].pop();
			if(node->left)
				Qs[!flag].push(node->left);
			if(node->right)
				Qs[!flag].push(node->right);
			if(Qs[flag].empty()) {
				result.push_back(item);
				item.clear();
				flag = !flag;
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
    vector<vector<int> > levelOrder(TreeNode *root){
		vector<vector<int> > result;
		if(!root)
			return result;
		
		queue<TreeNode *> queNodes0, *pqueNodes0;
		queue<TreeNode *> queNodes1, *pqueNodes1;
		
		pqueNodes0 = &queNodes0;
		pqueNodes1 = &queNodes1;
		
		pqueNodes0->push(root);
		result.resize(1);
		
		while(!pqueNodes0->empty()){
			TreeNode *pNode = pqueNodes0->front();
			pqueNodes0->pop();
			result[result.size()-1].push_back(pNode->val);
			
			if(pNode->left)
				pqueNodes1->push(pNode->left);
			
			if(pNode->right)
				pqueNodes1->push(pNode->right);
			
			if(pqueNodes0->empty() && !pqueNodes1->empty()){
				swap(pqueNodes0, pqueNodes1);
				result.resize(result.size()+1);
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
    vector<vector<int> > levelOrder(TreeNode *root);
	
private:
	void calculate(queue<TreeNode *>& q1, queue<TreeNode *>&q2, vector<int> &line);
};

vector<vector<int> > Solution::levelOrder(TreeNode *root)
{
	vector<vector<int> > result;
	if(!root)
		return result;
	queue<TreeNode *> q1, q2;
	q1.push(root);
	bool bUseQ1 = true;
	while(true)
	{
		vector<int> line;
		if(bUseQ1)
			calculate(q1, q2, line);
		else
			calculate(q2, q1, line);
		
		bUseQ1 = !bUseQ1;
		if(line.empty())
			break;
			
		result.push_back(line);
	}
		
	return result;
	
}

void Solution::calculate(queue<TreeNode *>& q1, queue<TreeNode *>&q2, vector<int> &line)
{
	if(q1.empty())
		return;
	
	while(!q1.empty())
	{
		TreeNode *pNode = q1.front();
		q1.pop();
		line.push_back(pNode->val);
		if(pNode->left)
			q2.push(pNode->left);
		if(pNode->right)
			q2.push(pNode->right);
	}
}
