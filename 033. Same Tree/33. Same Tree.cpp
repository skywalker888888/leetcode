/**
		Given two binary trees, write a function to check if they are equal or not.
		Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
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
    bool isSameTree(TreeNode *p, TreeNode *q) {
    	stack<pair<TreeNode *, TreeNode *> > stkNodes;
		stkNodes.push(pair<TreeNode *, TreeNode *>(p, q));
		while(!stkNodes.empty()) {
			TreeNode *n1 = stkNodes.top().first;
			TreeNode *n2 = stkNodes.top().second;
			stkNodes.pop();
			if(n1 && n2) {
				if(n1->val != n2->val)
					return false;
				stkNodes.push(pair<TreeNode *, TreeNode *>(n1->left, n2->left));
				stkNodes.push(pair<TreeNode *, TreeNode *>(n1->right, n2->right));
			} else if(n1 || n2){
				return false;
			}
		}
		return true;
	}
};
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
		if(p && q) {
			if(p->val != q->val)
				return false;
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		} else if(p || q)
			return false;
		return true;
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
    bool isSameTree(TreeNode *p, TreeNode *q) {
		if(!p && !q)
			return true;
		else if(!p || !q)
			return false;
		
		queue<TreeNode *> queNodeP, queNodeQ;
		queNodeP.push(p);
		queNodeQ.push(q);
		
		while(!queNodeP.empty() && !queNodeQ.empty()){
			TreeNode *p1 = queNodeP.front();
			TreeNode *p2 = queNodeQ.front();
			queNodeP.pop();
			queNodeQ.pop();
			
			if(p1->val != p2->val)
				return false;
			
			if(p1->left && p2->left){
				queNodeP.push(p1->left);
				queNodeQ.push(p2->left);
			}else if(p1->left || p2->left)
				return false;
			
			if(p1->right && p2->right){
				queNodeP.push(p1->right);
				queNodeQ.push(p2->right);
			}else if(p1->right || p1->right)
				return false;
		}
		
		if(!queNodeP.empty() || !queNodeQ.empty())
			return false;
		return true;
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
    bool isSameTree(TreeNode *p, TreeNode *q) {
		if(!p && !q)
			return true;
		else if(!p || !q)
			return false;
		
		if(p->val != q->val)
			return false;
		
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
    bool isSameTree(TreeNode *p, TreeNode *q);
};

bool Solution::isSameTree(TreeNode *p, TreeNode *q)
{
	if(!p && !q)
		return true;
		
	if(p && q)
	{
		if(p->val != q->val)
			return false;
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
	
	return false;
}
