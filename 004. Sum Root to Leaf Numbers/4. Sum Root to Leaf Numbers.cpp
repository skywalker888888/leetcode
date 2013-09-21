/**
	http://leetcode.com/onlinejudge
	4. Sum Root to Leaf Numbers
		Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
		An example is the root-to-leaf path 1->2->3 which represents the number 123.
		Find the total sum of all root-to-leaf numbers.
		For example,
			1
		   / \
		  2   3
		The root-to-leaf path 1->2 represents the number 12.
		The root-to-leaf path 1->3 represents the number 13.
		Return the sum = 12 + 13 = 25.
		
		Analysis:
			DFS can find all the leaves.
			
		Solution:
		
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
// non-recursion
class Solution {
public:
    int sumNumbers(TreeNode *root) {
       int result = 0;
	   if(!root)
			return result;
		int number = 0;
		stack<TreeNode *> stkNodes;
		stkNodes.push(root);
		number = 10 * number + root->val;
		while(!stkNodes.empty()) {
			TreeNode *node = stkNodes.top();
			if(node->left) {
				number = 10 * number + node->left->val;
				stkNodes.push(node->left);
			} else if(node->right) {
				number = 10 * number + node->right->val;
				stkNodes.push(node->right);
			} else {
				result += number;
				stkNodes.pop();
				number = (number - node->val)/10;
				while(!stkNodes.empty()) {
					TreeNode *pre = stkNodes.top();
					if(node==pre->right || !pre->right) {
						node = pre;
						stkNodes.pop();
						number = (number - node->val)/10;
					} else {
						stkNodes.push(pre->right);
						number = 10 * number + pre->right->val;
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
// recursion version
Time: O(n)
Space: O(n)
class Solution {
public:
    int sumNumbers(TreeNode *root) {
		int result = 0;
		int numbers = 0;
		sumNumbers(root, result, numbers);
		return result;
    }
	
	void sumNumbers(TreeNode *root, int &result, int &numbers) {
		if(!root)
			return;
		if(!root->left && !root->right) {
			numbers = 10 * numbers + root->val;
			result += numbers;
			numbers = (numbers - root->val) / 10;
			return;
		} else {
			numbers = 10 * numbers + root->val;
			if(root->left)
				sumNumbers(root->left, result, numbers);
			if(root->right)
				sumNumbers(root->right, result, numbers);
			numbers = (numbers - root->val) / 10;
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
    int sumNumbers(TreeNode *root);
	
private:
	int parse(TreeNode *root, int sum);
};
 
int Solution::sumNumbers(TreeNode *root)
{
	int sum = 0;
	sum = parse(root, 0);
	return sum;
}
 
int Solution::parse(TreeNode *root, int sum)
{
	int result = 0;
	if(!root)
		return sum;
	result += parse(root->left, sum*10+root->val);
		
	if(!root->left && !root->right)
		result = sum*10 + root->val;
	else if(root->left && root->right)
		result = parse(root->left, sum*10+root->val) + parse(root->right, sum*10+root->val);
	else if(root->left) 
		result = parse(root->left, sum*10+root->val);
	else 
		result = parse(root->right, sum*10+root->val);
		
	return result;
}


// Non - recursion version
class Solution {
public:
    int sumNumbers(TreeNode *root);
};
 
int Solution::sumNumbers(TreeNode *root)
{
	int result = 0;
	
	stack<pair<TreeNode *, int> > stkNodes;
	if(root)
	{
		stkNodes.push(pair<TreeNode *, int>(root, root->val));
	}
	while(!stkNodes.empty())
	{
		TreeNode *pNode = stkNodes.top().first;
		int val = stkNodes.top().second;
		if(pNode->left)
			stkNodes.push(pair<TreeNode *, int>(pNode->left, val*10 + pNode->left->val));
		else if(pNode->right)
			stkNodes.push(pair<TreeNode *, int>(pNode->right, val*10 + pNode->right->val));
		else
		{
			result += val;
			
			// trace back
			stkNodes.pop();
			while(!stkNodes.empty())
			{
				TreeNode *pParentNode = stkNodes.top().first;
				int parentval = stkNodes.top().second;
				if(pNode==pParentNode->right || !pParentNode->right)
				{
					pNode = pParentNode;
					stkNodes.pop();
				}
				else
				{
					stkNodes.push(pair<TreeNode *, int>(pParentNode->right, parentval*10 + pParentNode->right->val));
					break;
				}
			}
		}
	}
	
	return result;
}



 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
struct TreeNode
{

	int val;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(int x)
		: val(x), left(NULL), right(NULL)
	{
	}
}; 

class Solution
{
public:
    int sumNumbers(TreeNode *root);
	TreeNode	*generateTree(string data);
};

/**
	Recursive solution.
 */
int Solution::sumNumbers(TreeNode *root)
{
    if(!root)
		return 0;
	
	TreeNode *left = root->left;
	TreeNode *right = root->right;
    
    if(!left && !right)
        return root->val;
	
	int nLeftSum = 0;
	if(left)
	{
		int nLeftValue = left->val;
		left->val += root->val * 10;
		nLeftSum = sumNumbers(left);
		left->val = nLeftValue;
	}

    int nRightSum = 0;
	if(right)
	{
		int nRightValue = right->val;
		right->val += root->val * 10;
		nRightSum = sumNumbers(right);
		right->val = nRightValue;
	}
	
	return nLeftSum + nRightSum;
}


int main(int argc, char **argv)
{
	Solution solu;
	
	
	return 0;
}
