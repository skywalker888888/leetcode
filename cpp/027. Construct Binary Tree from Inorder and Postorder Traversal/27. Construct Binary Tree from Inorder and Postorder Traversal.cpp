/**
		Given inorder and postorder traversal of a tree, construct the binary tree.
		Note:
		You may assume that duplicates do not exist in the tree.
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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    	if(inorder.size()!=postorder.size() || !inorder.size())
			return NULL;
			
		TreeNode *root = NULL;
		stack<tuple<TreeNode *, bool, int, int, int, int> > stkNodes;
		stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(NULL, true, 0, inorder.size()-1, 0, postorder.size()-1));
		while(!stkNodes.empty()) {
			tuple<TreeNode *, bool, int, int, int, int> node = stkNodes.top();
			TreeNode *pChildRoot = std::get<0>(node);
			bool	bIsLeftChild = std::get<1>(node);
			int		i = std::get<2>(node);
			int		j = std::get<3>(node);
			int		m = std::get<4>(node);
			int		n = std::get<5>(node);
			
			stkNodes.pop();
			if( i>j ) {
				if(pChildRoot)
					(bIsLeftChild?pChildRoot->left:pChildRoot->right) = NULL;
			} else {
				int k = i;
				while(k<=j && inorder[k]!=postorder[n])
					++k;
				TreeNode *pRoot = new TreeNode(postorder[n]);
				if(!root)
					root = pRoot;
				if(pChildRoot)
					(bIsLeftChild?pChildRoot->left:pChildRoot->right) = pRoot;
					
				stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(pRoot, true, i, k-1, m, m+(k-i-1)));
				stkNodes.push(tuple<TreeNode *, bool, int, int, int, int>(pRoot, false, k+1, j, m+(k-i-1)+1, n-1));
			}
			
		}
		return root;
    }
};







































// recursion
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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
		if(inorder.size()!=postorder.size() || !postorder.size())
			return NULL;
		
		return buildTree(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
    }
    TreeNode *buildTree(vector<int> &inorder, int i, int j, vector<int> &postorder, int m, int n) {
		if(m>n || i>j)
			return NULL;
		TreeNode *root = new TreeNode(postorder[n]);
		int k = i;
		while(k<=j && inorder[k]!=postorder[n])
			++k;
		
		root->left = buildTree(inorder, i, k-1, postorder, m, m+(k-i-1));
		root->right = buildTree(inorder, k+1, j, postorder, m+(k-i-1)+1, n-1);
		return root;
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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder){
		if(!inorder.size() || inorder.size()!=postorder.size())
			return NULL;
		
		TreeNode *root = NULL;
		stack<tuple<TreeNode *, bool, int, int, int, int> > stkTree;
		stkTree.push(tuple<TreeNode *, bool, int, int, int,int>(NULL, true, 0, inorder.size()-1, 0, postorder.size()-1));
		while(!stkTree.empty()){
			tuple<TreeNode *, bool, int, int, int, int> node = stkTree.top();
			stkTree.pop();
			TreeNode *pChildRoot = std::get<0>(node);
			bool bLeftChild = std::get<1>(node);
			int i_l = std::get<2>(node);
			int i_r = std::get<3>(node);
			int p_l = std::get<4>(node);
			int p_r = std::get<5>(node);
			
			if(i_l>i_r){
				if(!pChildRoot)
					root = NULL;
				else if(bLeftChild)
					pChildRoot->left = NULL;
				else 
					pChildRoot->right = NULL;
			}else{
				int val = postorder[p_r];
				TreeNode *pNode = new TreeNode(val);
				if(!pChildRoot)
					root = pNode;
				else if(bLeftChild)
					pChildRoot->left = pNode;
				else
					pChildRoot->right = pNode;
				
				//
				int pos_inorder = -1;
				for(int i=i_l; i<=i_r; ++i)
					if(inorder[i] == val){
						pos_inorder = i;
						break;
					}
				if(pos_inorder < 0){
					// ERROR
					return NULL;
				}
				
				stkTree.push(tuple<TreeNode *, bool, int, int, int, int>(pNode, false, pos_inorder+1, i_r, p_l+(pos_inorder-i_l), p_r-1));
				stkTree.push(tuple<TreeNode *, bool, int, int, int, int>(pNode, true, i_l, pos_inorder-1, p_l, p_l+(pos_inorder-i_l)-1));
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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder);
	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
	{
		if(!inorder.size())
			return NULL;
		int n = inorder.size();
		
		return buildTree(0, n-1, inorder, 0, n-1, postorder);
	}

	TreeNode *buildTree(int a, int b, vector<int> &inorder, int i, int j, vector<int> &postorder) {
		if(b < a)
			return NULL;
		
		if(a==b) {
			TreeNode *pNode = new TreeNode(inorder[a]);
			return pNode;
		}
		
		int nMidNode = postorder[j];
		int nMidPosition = a - 1;
		for(int k=a; k<=b; ++k)
			if(nMidNode == inorder[k]) {
				nMidPosition = k;
				break;
			}
			
		TreeNode *pNode = new TreeNode(nMidNode);
		int nLenLeft = nMidPosition - a;
		int nLenRight = b - nMidPosition;
		
		TreeNode *pLeft = buildTree(a, nMidPosition-1, inorder, i, j-nLenRight-1, postorder);
		TreeNode *pRight = buildTree(nMidPosition+1, b, inorder, j-nLenRight, j-1, postorder);
		
		pNode->left = pLeft;
		pNode->right = pRight;
		
		return pNode;
	}
};



