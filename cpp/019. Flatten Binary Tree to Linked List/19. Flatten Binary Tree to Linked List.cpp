/**
		Given a binary tree, flatten it to a linked list in-place.

		For example,
		Given

				 1
				/ \
			   2   5
			  / \   \
			 3   4   6
		The flattened tree should look like:
		   1
			\
			 2
			  \
			   3
				\
				 4
				  \
				   5
					\
					 6	
		Analysis:
			Hints:
			If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.			
*/
// pass 3
// non-recursive version
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
    void flatten(TreeNode *root) {
		if(!root)
			return;
		stack<TreeNode *> stkNode;
		
		TreeNode *pre = NULL;
		stkNode.push(root);
		while(!stkNode.empty()) {
			TreeNode *node = stkNode.top();
			stkNode.pop();
			if(node->right)
				stkNode.push(node->right);
			if(node->left)
				stkNode.push(node->left);
			node->left = node->right = NULL;
			if(!pre)
				pre = node;
			else {
				pre->right = node;
				pre->left = NULL;
				pre = node;
			}
			pre->left = pre->right = NULL;
		}
    }
};

// recursion version
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
    void flatten(TreeNode *root) {
		TreeNode *head;
		TreeNode *tail;
		
		flatten(root, head, tail);
		return head;
    }
    void flatten(TreeNode *root, TreeNode *&head, TreeNode * &tail) {
		head = tail = NULL;
		if(!root) 
			return;
		
		TreeNode *h_left, *t_left;
		flatten(root->left, h_left, t_left);
		
		TreeNode *h_right, *t_right;
		flatten(root->right, h_right, t_right);
		
		head = root;
		tail = root;
		TreeNode *pre = root;
		pre->left = pre->right = NULL;
		
		if(h_left) {
			pre->right = h_left;
			pre = t_left;
		}
		if(h_right) {
			pre->right = h_right;
			pre = t_right;
		}
		tail = pre;
	}
};



























 
// Pass 2
class Solution
{
public:
    void flatten(TreeNode *root)
	{
		if(!root)
			return;
			
		stack<TreeNode *> stkNodes;
		stkNodes.push(root);
		root = NULL;
		TreeNode *pPre = NULL;
		while(!stkNodes.empty()){
			TreeNode *pNode = stkNodes.top();
			stkNodes.pop();
			if(pNode->right)
				stkNodes.push(pNode->right);
			if(pNode->left)
				stkNodes.push(pNode->left);
			if(!root)
				root = pNode;
			else
				pPre->right = pNode;

			pNode->left = NULL;
			pNode->right = NULL;
			pPre = pNode;
		}
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
	void flatten(TreeNode *root)
	{
		flattenTree(root);
	}

	pair<TreeNode*, TreeNode*> flattenTree(TreeNode *root)
	{
		pair<TreeNode*, TreeNode*> result = make_pair<TreeNode*, TreeNode*>(NULL, NULL);
		if(!root)
			return result;
		pair<TreeNode *, TreeNode*> ftnLeft = flattenTree(root->left);
		pair<TreeNode *, TreeNode*> ftnRight = flattenTree(root->right);
		root->left = root->right = NULL;
		
		TreeNode *pNode = root;
		if(ftnLeft.first)
		{
			pNode->left = NULL;
			pNode->right = ftnLeft.first;
			pNode = ftnLeft.second;
			pNode->left = NULL;
			pNode->right = NULL;
		}
		
		if(ftnRight.first)
		{
			pNode->left = NULL;
			pNode->right = ftnRight.first;
			pNode = ftnRight.second;
			pNode->left = NULL;
			pNode->right = NULL;
		}

		result.first = root;
		result.second = pNode;
		
		return result;
	}
};



