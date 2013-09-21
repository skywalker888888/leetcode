/**
		Given a binary tree, determine if it is height-balanced.
		For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
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
    bool isBalanced(TreeNode *root) {
    	if(!root)
			return true;
			
		stack<pair<TreeNode *, int> > stkNodes;
		stkNodes.push(pair<TreeNode *, int>(root, 1));
		while(!stkNodes.empty()) {
			pair<TreeNode *, int> node = stkNodes.top();
			TreeNode *p = node.first;
			int height = node.second;
			if(p->left)
				stkNodes.push(pair<TreeNode *, int>(p->left, 1));
			else if(p->right)
				stkNodes.push(pair<TreeNode *, int>(p->right, 1));
			else {
				height = 1;
				stkNodes.pop();
				while(!stkNodes.empty()) {
					pair<TreeNode *, int> &parent = stkNodes.top();
					TreeNode *pParent = parent.first;
					if(!pParent->right) {
						if(height > 1)
							return false;
						parent.second = height + 1;
						node = parent;
						p = node.first;
						height = node.second;
						stkNodes.pop();
					} else if(p == pParent->right) {
						if(abs(height - parent.second + 1) > 1)
							return false;
						parent.second = max(parent.second, height+1);
						node = parent;
						p = node.first;
						height = node.second;
						stkNodes.pop();
					} else {
						parent.second = height + 1;
						stkNodes.push(pair<TreeNode *, int>(parent.first->right, 1));
						break;
					}
				}
			}
		}
		
		return true;
    }
};




































// recursion
// Time: O(n)
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
    bool isBalanced(TreeNode *root) {
		if(!root)
			return true;
		int height = 0;
		return isBalanced(root, height);
    }
    bool isBalanced(TreeNode *root, int &height) {
		if(!root) {
			height = 0;
			return true;
		}
		else if(!root->left && !root->right) {
			height = 1;
			return true;
		} else {
			int h_left, h_right;
			bool b_left = isBalanced(root->left, h_left);
			bool b_right = isBalanced(root->right, h_right);
			if(!b_left || !b_right)
				return false;
			if(abs(h_left-h_right) > 1)
				return false;
			height = max(h_left, h_right) + 1;
			return true;
		}
		return true;
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
    bool isBalanced(TreeNode *root) {
        if(!root)
			return true;
		int minHeight = 1;
		int maxHeight = 1;
		
		stack<pair<TreeNode *, int> > stkNodes;
		stkNodes.push(pair<TreeNode *, int>(root, 0));
		while(!stkNodes.empty()){
			pair<TreeNode *, int> &node = stkNodes.top();
			if(node.first->left)
				stkNodes.push(pair<TreeNode *, int>(node.first->left, 0));
			else{
				if(node.first->right)
					stkNodes.push(pair<TreeNode *, int>(node.first->right, 0));
				else{
					pair<TreeNode *, int> child_node = stkNodes.top();
					child_node.second = 1;
					stkNodes.pop();
					while(!stkNodes.empty()){
						pair<TreeNode *, int>& parent_node = stkNodes.top();
						if(child_node.first == parent_node.first->left){
							parent_node.second = child_node.second + 1;
							if(parent_node.first->right){
								stkNodes.push(pair<TreeNode *, int>(parent_node.first->right, 0));
								break;
							}else{
								if(parent_node.second > 2)
									return false;
								child_node = parent_node;
								stkNodes.pop();
							}
						}else{
							if(!parent_node.first->left){
								if(child_node.second > 1)
									return false;
									
								parent_node.second = child_node.second + 1;
							}else{
								int dist = abs(child_node.second - (parent_node.second-1));
								if(dist > 1)
									return false;
								parent_node.second = max(parent_node.second, child_node.second+1);
							}
							child_node = parent_node;
							stkNodes.pop();
						}
					}
				}
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
    bool isBalanced(TreeNode *root);
	
private:
	int		calculateHeight(TreeNode *root);
};

bool Solution::isBalanced(TreeNode *root)
{
	if(!root)
		return true;
		
	if(!isBalanced(root->left) || !isBalanced(root->right))
		return false;
		
	int hLeft = calculateHeight(root->left);
	int hRight = calculateHeight(root->right);
	if(abs(hLeft-hRight) > 1)
		return false;
	return true;
}

int Solution::calculateHeight(TreeNode *root)
{
	if(!root)
		return 0;
	
	int hLeft = calculateHeight(root->left);
	int hRight = calculateHeight(root->right);
	
	return max(hLeft, hRight) + 1;
}
