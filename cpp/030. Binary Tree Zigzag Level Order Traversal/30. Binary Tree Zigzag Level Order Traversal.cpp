/**
		Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
		For example:
		Given binary tree {3,9,20,#,#,15,7},
			3
		   / \
		  9  20
			/  \
		   15   7
		return its zigzag level order traversal as:
		[
		  [3],
		  [20,9],
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
		vector<vector<int> > result;
		if(!root)
			return result;
	
		vector<deque<TreeNode *> > DQs(2);
		DQs[0].push_back(root);
		int flag = 1;
		
		vector<int> item;
		while(DQs[!flag].size()) {
			TreeNode *node = NULL;
			if(flag) {
				node = DQs[!flag].front();
				DQs[!flag].pop_front();
				if(node->left)
					DQs[flag].push_back(node->left);
				if(node->right)
					DQs[flag].push_back(node->right);
			} else {
				node = DQs[!flag].back();
				DQs[!flag].pop_back();
				if(node->right)
					DQs[flag].push_front(node->right);
				if(node->left)
					DQs[flag].push_front(node->left);
			}
			item.push_back(node->val);
			
			if(!DQs[!flag].size()) {
				result.push_back(item);
				item.clear();
				flag = !flag;
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
		vector<vector<int> > result;
		if(!root)
			return result;
			
		int layer = 1;
		stack<TreeNode *> stkNodes0;
		stack<TreeNode *> stkNodes1;
		
		if(root){
			stkNodes0.push(root);
			result.resize(1);
		}
		bool hasNextLayerData = false;
		while((layer==1&&!stkNodes0.empty()) || (layer==0&&!stkNodes1.empty())){
			TreeNode *pNode = NULL;
			if(layer){
				// generate reverse order
				pNode = stkNodes0.top();
				result[result.size()-1].push_back(pNode->val);
				stkNodes0.pop();
				if(pNode->left){
					hasNextLayerData = true;
					stkNodes1.push(pNode->left);
				}
				if(pNode->right){
					hasNextLayerData = true;
					stkNodes1.push(pNode->right);
				}
				if(stkNodes0.empty()){
					if(hasNextLayerData)
						result.resize(result.size()+1);
					layer = !layer;
					hasNextLayerData = false;
				}
			}else{
				pNode = stkNodes1.top();
				result[result.size()-1].push_back(pNode->val);
				stkNodes1.pop();
				if(pNode->right){
					hasNextLayerData = true;
					stkNodes0.push(pNode->right);
				}
				if(pNode->left){
					hasNextLayerData = true;
					stkNodes0.push(pNode->left);
				}
				if(stkNodes1.empty()){
					if(hasNextLayerData)
						result.resize(result.size()+1);
					layer = !layer;
					hasNextLayerData = false;
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root);
};

vector<vector<int> > Solution::zigzagLevelOrder(TreeNode *root)
{
	vector<vector<int> > result;
	
	if(!root)
		return result;
	
	queue<TreeNode *> queuePassOdd;
	queue<TreeNode *> queuePassEven;
	
	bool uPassOdd = true;
	queuePassOdd.push(root);
	
	while(true)
	{
		vector<int> line;
		if(uPassOdd)
		{
			if(queuePassOdd.empty())
				break;
			queue<int> queueResult;
			while(!queuePassOdd.empty())
			{
				TreeNode *pNode = queuePassOdd.front();
				queuePassOdd.pop();
				
				queueResult.push(pNode->val);
				
				if(pNode->left)
					queuePassEven.push(pNode->left);
				if(pNode->right)
					queuePassEven.push(pNode->right);
			}
			
			while(!queueResult.empty())
			{
				int nVal = queueResult.front();
				queueResult.pop();
				line.push_back(nVal);
			}
			
			result.push_back(line);
			uPassOdd = false;
		}
		else 
		{
			if(queuePassEven.empty())
				break;
			stack<int> stackResult;
			while(!queuePassEven.empty())
			{
				TreeNode *pNode = queuePassEven.front();
				queuePassEven.pop();
				stackResult.push(pNode->val);
				if(pNode->left)
					queuePassOdd.push(pNode->left);
				if(pNode->right)
					queuePassOdd.push(pNode->right);
			}

			while(!stackResult.empty())
			{
				int nVal = stackResult.top();
				stackResult.pop();
				line.push_back(nVal);
			}
			
			result.push_back(line);
			uPassOdd = true;
		}
	}
	
	return result;
}
