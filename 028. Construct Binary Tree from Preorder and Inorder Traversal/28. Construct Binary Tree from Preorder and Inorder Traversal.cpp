/**
		Given preorder and inorder traversal of a tree, construct the binary tree.
		Note:
		You may assume that duplicates do not exist in the tree.	
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    	if(preorder.size()!=inorder.size() || !inorder.size())
			return NULL;
		
		stack<tuple<TreeNode *, bool, int, int, int, int> > stkNodes;
		
		int k = 0;
		while(k<inorder.size() && inorder[k] != preorder[0])
			++k;
		if(k >= inorder.size())
			return NULL;
		TreeNode *root = new TreeNode(preorder[0]);
		stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(root, true, 1, k, 0, k-1));
		stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(root, false, k+1, preorder.size()-1, k+1, inorder.size()-1));
		while(!stkNodes.empty()) {
			tuple<TreeNode *, bool, int, int, int, int> node = stkNodes.top();
			stkNodes.pop();
			TreeNode * pChildRoot = std::get<0>(node);
			bool bIsLeftChild = std::get<1>(node);
			int i = std::get<2>(node);
			int j = std::get<3>(node);
			int m = std::get<4>(node);
			int n = std::get<5>(node);
			
			if(i > j)
				(bIsLeftChild?pChildRoot->left:pChildRoot->right) = NULL;
			else {
				k = m;
				while(k<=n && inorder[k]!=preorder[i])
					++k;
				TreeNode *r = new TreeNode(preorder[i]);
				(bIsLeftChild?pChildRoot->left:pChildRoot->right) = r;
				
				stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(r, true, i+1, i+1+(k-1-m), m, k-1));
				stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(r, false, i+1+(k-1-m)+1, j, k+1, n));
			}
		}
		
		return root;
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
		if(preorder.size()==0 || preorder.size()!=inorder.size())
			return NULL;
		
		TreeNode *root = NULL;
		stack<tuple<TreeNode *, bool, int, int, int, int> > stkNodes;
		stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(NULL, true, 0, preorder.size()-1, 0, inorder.size()-1));
		while(!stkNodes.empty()){
			tuple<TreeNode *, bool, int, int, int, int> node = stkNodes.top();
			stkNodes.pop();
			
			TreeNode *pChildRoot = std::get<0>(node);
			bool bLeftChild = std::get<1>(node);
			int p_l = std::get<2>(node);
			int p_r = std::get<3>(node);
			int i_l = std::get<4>(node);
			int i_r = std::get<5>(node);
			
			int val = preorder[p_l];
			if(p_l > p_r)
				if(bLeftChild)
					pChildRoot->left = NULL;
				else 
					pChildRoot->right = NULL;
			else{
				int val = preorder[p_l];
				TreeNode *pNode = new TreeNode(val);
				if(!pChildRoot)
					root = pNode;
				else
					if(bLeftChild)
						pChildRoot->left = pNode;
					else 
						pChildRoot->right = pNode;
				int pos_inorder = -1;
				for(int i=i_l; i<=i_r; ++i)
					if(inorder[i] == val){
						pos_inorder = i;
						break;
					}
				stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(pNode, true, p_l+1, p_l+(pos_inorder-i_l), i_l, pos_inorder-1));
				stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(pNode, false, p_l+(pos_inorder-i_l)+1, p_r, pos_inorder+1, i_r));
			}
		}
        
		return root;
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder);
private:
    TreeNode *buildTree(int i, int j, vector<int> &preorder, int m, int n, vector<int> &inorder);
};


TreeNode *Solution::buildTree(vector<int> &preorder, vector<int> &inorder)
{
	int n = preorder.size();
	if(!n)
		return NULL;
	
	return buildTree(0, n-1, preorder, 0, n-1, inorder);
	
}


TreeNode *Solution::buildTree(int i, int j, vector<int> &preorder, int m, int n, vector<int> &inorder)
{
	if(j<i)
		return NULL;
	if(i == j)
		return new TreeNode(preorder[i]);
		
	int nVal = preorder[i];
	
	int nIndex = i - 1;
	for(int k=m; k<=n; ++k)
		if(inorder[k] == nVal)
		{
			nIndex = k;
			break;
		}
		
	int nLenLeft = nIndex-m;
	int nLenRight = n - nIndex;
	TreeNode *root = new TreeNode(nVal);
	TreeNode *pLeft = buildTree(i+1, i+nLenLeft, preorder, m, nIndex-1, inorder);
	TreeNode *pRight = buildTree(i+nLenLeft+1, j, preorder, nIndex+1, n, inorder);
	
	root->left = pLeft;
	root->right = pRight;
	
	return root;
}
