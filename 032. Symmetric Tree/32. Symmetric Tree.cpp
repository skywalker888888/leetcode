
/**
		Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

		For example, this binary tree is symmetric:

			1
		   / \
		  2   2
		 / \ / \
		3  4 4  3
		But the following is not:
			1
		   / \
		  2   2
		   \   \
		   3    3
		Note:
		Bonus points if you could solve it both recursively and iteratively.
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
    bool isSymmetric(TreeNode *root) {
		if(!root)
			return true;
		stack<pair<TreeNode *, TreeNode *> > stkNodes;
		stkNodes.push(pair<TreeNode *, TreeNode *>(root->left, root->right));
		while(!stkNodes.empty()) {
			TreeNode *n1 = stkNodes.top().first;
			TreeNode *n2 = stkNodes.top().second;
			stkNodes.pop();
			if(n1 && n2) {
				if(n1->val != n2->val)
					return false;
				stkNodes.push(pair<TreeNode *, TreeNode *>(n1->left, n2->right));
				stkNodes.push(pair<TreeNode *, TreeNode *>(n2->left, n1->right));
			} else if(n1 || n2) {
				return false;
			}
		}
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
    bool isSymmetric(TreeNode *root) {
    	if(!root)
			return true;
		return isSymmetric(root->left, root->right);
    }
    bool isSymmetric(TreeNode *r1, TreeNode *r2) {
		if(!r1 && !r2) {
			return true;
		}
		else if(r1 && r2) {
			if(r1->val != r2->val)
				return false;
			return isSymmetric(r1->left, r2->right) && isSymmetric(r1->right, r2->left);
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
    bool isSymmetric(TreeNode *root) {
		if(!root)
			return true;
		return 	isSymmetric(root->left, root->right);
    }
    bool isSymmetric(TreeNode *r1, TreeNode *r2) {
		if(!r1 && !r2)
			return true;
		else if(!r1 || !r2)
			return false;
		else if(r1->val != r2->val)
			return false;
		else
			return 	isSymmetric(r1->left, r2->right) && isSymmetric(r2->left, r1->right);
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
    bool isSymmetric(TreeNode *root) {
		if(!root)
			return true;
		queue<TreeNode *> queNode1;
		queue<TreeNode *> queNode2;
		queNode1.push(root);
		queNode2.push(root);
		
		while(!queNode1.empty() && !queNode2.empty()){
			TreeNode *pNode1 = queNode1.front();
			TreeNode *pNode2 = queNode2.front();
			queNode1.pop();
			queNode2.pop();
			
			if(pNode1->val != pNode2->val)
				return false;
			
			if(pNode1->left && pNode2->right){
				queNode1.push(pNode1->left);
				queNode2.push(pNode2->right);
			}else if(pNode1->left || pNode2->right)
				return false;
			
			if(pNode1->right && pNode2->left){
				queNode1.push(pNode1->right);
				queNode2.push(pNode2->left);
			}else if(pNode1->right || pNode2->left)
				return false;
		}
		
		if(!queNode1.empty() || !queNode2.empty())
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
class Solution
{
public:
    bool isSymmetric(TreeNode *root);
	
private:
	bool isSymmetric(TreeNode *root1, TreeNode *root2);
	bool isSymmetric2(TreeNode *root1, TreeNode *root2);
};


bool Solution::isSymmetric(TreeNode *root)
{
	if(!root)
		return true;
	
	if(!root->left && !root->right)
		return true;
	
	if(root->left && root->right)
	{
		//return isSymmetric(root->left, root->right);
		return isSymmetric2(root->left, root->right);
	}
	
	return false;
}

bool Solution::isSymmetric(TreeNode *root1, TreeNode *root2)
{
	if(!root1 && !root2)
		return true;
	
	if(root1 && root2)
	{
		if(root1->val != root2->val)
			return false;
		return isSymmetric(root1->left, root2->right) && isSymmetric(root1->right, root2->left);
	}
	
	return false;
}

bool Solution::isSymmetric2(TreeNode *root1, TreeNode *root2)
{
	stack<TreeNode *> stkTree1;
	stack<TreeNode *> stkTree2;
	
	stkTree1.push(root1);
	stkTree2.push(root2);
	while(!stkTree1.empty())
	{
		if(stkTree2.empty())
			return false;
			
		TreeNode *pNode1 = stkTree1.top();
		TreeNode *pNode2 = stkTree2.top();
		
		if(pNode1->val != pNode2->val)
			return false;

		if(!pNode1->left&&pNode2->right || pNode1->left&&!pNode2->right)
			return false;
		if(!pNode2->left&&pNode1->right || pNode2->left&&!pNode1->right)
			return false;
			
		if(pNode1->left && pNode2->right)
		{
			stkTree1.push(pNode1->left);
			stkTree2.push(pNode2->right);
		}
		else if(pNode1->right && pNode2->left)
		{
			stkTree1.push(pNode1->right);
			stkTree2.push(pNode2->left);
		}
		else if(!pNode1->left && !pNode1->right && !pNode2->left && !pNode2->right) // both are leaves
		{
			while(true)
			{
				stkTree1.pop();
				stkTree2.pop();
				
				if(stkTree1.empty() && stkTree2.empty())
					return true;
				else if(stkTree1.empty() || stkTree2.empty())
					return false;

				TreeNode *pNode11 = stkTree1.top();
				TreeNode *pNode22 = stkTree2.top();
			
				if(pNode11->right == pNode1 && pNode22->left == pNode2)
				{
					pNode1 = pNode11;
					pNode2 = pNode22;
				}
				else if(!pNode11->right && !pNode22->left)
				{
					pNode1 = pNode11;
					pNode2 = pNode22;
				}
				else if(pNode11->right && pNode22->left)
				{
					stkTree1.push(pNode11->right);
					stkTree2.push(pNode22->left);
					break;
				}
				else
					return false;
			}
		}
		else
		{
			return false;
		}
	}
	
	if(!stkTree2.empty())
		return false;
	
	return true;
}



int main(int argc, char **argv)
{

	TreeNode *n1 = new TreeNode(1);
	TreeNode *n2 = new TreeNode(2);
	TreeNode *n3 = new TreeNode(2);
	TreeNode *n4 = new TreeNode(3);
	TreeNode *n5 = new TreeNode(3);
	
	n1->left = n2;
	n1->right = n3;
	
	n2->left = n4;
	n3->right = n5;
	
	Solution sol;
	bool b = sol.isSymmetric(n1);
	
	cout << "the vale is: " << b << "\n";
}



