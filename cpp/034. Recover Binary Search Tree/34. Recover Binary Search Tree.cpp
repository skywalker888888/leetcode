/**
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
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
	TreeNode *getMinimum(TreeNode *root) {
		while(root && root->left)
			root = root->left;
		return root;
	}
	TreeNode *getMaximum(TreeNode *root) {
		while(root && root->right)
			root = root->right;
		return root;
	}
	
	void testAndSet(TreeNode *front, TreeNode *tail, TreeNode *&first, TreeNode *&middle, TreeNode *&second){
		if(second || !front || !tail)
			return;
			
		if(front->val > tail->val)
			if(!first){
				first = front;
				middle = tail;
			}else if(!second)
				second = tail;
	}
	
    void recoverTree(TreeNode *root) {
		if(!root)
			return;
		TreeNode *first=NULL, *middle=NULL, *last=NULL;
		stack<TreeNode *> stkNodes;
		stkNodes.push(root);
		while(!stkNodes.empty()) {
			TreeNode *node = stkNodes.top();
			if(node->left) {
				stkNodes.push(node->left);
			} else if(node->right) {
				TreeNode *minNode = getMinimum(node->right);
				testAndSet(node, minNode, first, middle, last);
				stkNodes.push(node->right);
			} else {
				stkNodes.pop();
				while(!stkNodes.empty()) {
					TreeNode *parent = stkNodes.top();
					if(node == parent->left) {
						TreeNode *pMaxNode = getMaximum(node);
						testAndSet(pMaxNode, parent, first, middle, last);
						
						if(parent->right) {
							TreeNode *pNext = getMinimum(parent->right);
							testAndSet(parent, pNext, first, middle, last);
							stkNodes.push(parent->right);
							break;
						}
					}
					node = parent;
					stkNodes.pop();
					
				}
			}
		}
		if(last) {
			swap(first->val, last->val);
		} else if(first) {
			swap(first->val, middle->val);
		}
    }
};

































/// pass2
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
	void	testAndSet(TreeNode *front, TreeNode *tail, TreeNode *&first, TreeNode *&middle, TreeNode *&second){
		if(second || !front || !tail)
			return;
			
		if(front->val > tail->val)
			if(!first){
				first = front;
				middle = tail;
			}else if(!second)
				second = tail;
	}
	
	TreeNode *TreeMinimum(TreeNode *u){
		while(u && u->left)
			u = u->left;
		return u;
	}
	
	TreeNode *TreeMaximum(TreeNode *u){
		while(u && u->right)
			u = u->right;
		return u;
	}
	
	
    void recoverTree(TreeNode *root){
		if(!root)
			return;
		TreeNode *first=NULL, *middle=NULL, *second=NULL;

		stack<TreeNode *> stkNodes;
		stkNodes.push(root);
		while(!stkNodes.empty()){
			TreeNode *pNode = stkNodes.top();
			if(pNode->left){
				stkNodes.push(pNode->left);
			}
			else if(pNode->right){
				TreeNode *pNext = TreeMinimum(pNode->right);
				testAndSet(pNode, pNext, first, middle, second);
				stkNodes.push(pNode->right);
			}else{
				stkNodes.pop();
				while(!stkNodes.empty()){
					TreeNode *pParent = stkNodes.top();
					if(pNode == pParent->left){
						TreeNode *pMax = TreeMaximum(pNode);
						testAndSet(pMax, pParent, first, middle, second);
							
						if(pParent->right){
							TreeNode *pNext = TreeMinimum(pParent->right);
							testAndSet(pParent, pNext, first, middle, second);
							stkNodes.push(pParent->right);
							break;
						}
					}
					pNode = pParent;
					stkNodes.pop();
				}
			}
		}
		
		if(second){
			swap(first->val, second->val);
		}else if(first){
			swap(first->val, middle->val);
		}
    }
};












































/**
		Two elements of a binary search tree (BST) are swapped by mistake.
		Recover the tree without changing its structure.
		Note:
		A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

Two nodes of a BST are swapped, correct the BST
September 14, 2012
Two of the nodes of a Binary Search Tree (BST) are swapped. Fix (or correct) the BST.

Input Tree:
         10
        /  \
       5    8
      / \
     2   20

In the above tree, nodes 20 and 8 must be swapped to fix the tree.  
Following is the output tree
         10
        /  \
       5    20
      / \
     2   8
Solution1: The inorder traversal of a BST produces a sorted array. So a simple method is to store inorder traversal of the input tree in an auxiliary array. Sort the auxiliary array. Finally, insert the auxiilary array elements back to the BST, keeping the structure of the BST same. Time complexity of this method is O(nLogn) and auxiliary space needed is O(n).

Solution2: We can solve this in O(n) time and with a single traversal of the given BST. Since inorder traversal of BST is always a sorted array, the problem can be reduced to a problem where two elements of a sorted array are swapped. There are two cases that we need to handle:
1. The swapped nodes are not adjacent in the inorder traversal of the BST.
 For example, Nodes 5 and 25 are swapped in {3 5 7 8 10 15 20 25}. 
 The inorder traversal of the given tree is 3 25 7 8 10 15 20 5 
If we observe carefully, during inorder traversal, we find node 7 is smaller than the previous visited node 25. Here save the context of node 25 (previous node). Again, we find that node 5 is smaller than the previous node 20. This time, we save the context of node 5 ( current node ). Finally swap the two node¡¯s values.

2. The swapped nodes are adjacent in the inorder traversal of BST.
  For example, Nodes 7 and 8 are swapped in {3 5 7 8 10 15 20 25}. 
  The inorder traversal of the given tree is 3 5 8 7 10 15 20 25 
Unlike case #1, here only one point exists where a node value is smaller than previous node value. e.g. node 7 is smaller than node 8.

How to Solve? We will maintain three pointers, first, middle and last. When we find the first point where current node value is smaller than previous node value, we update the first with the previous node & middle with the current node. When we find the second point where current node value is smaller than previous node value, we update the last with the current node. In case #2, we will never find the second point. So, last pointer will not be updated. After processing, if the last node value is null, then two swapped nodes of BST are adjacent.

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

/**
Solution1: The inorder traversal of a BST produces a sorted array. So a simple method is to store inorder traversal of the input tree in an auxiliary array. Sort the auxiliary array. Finally, insert the auxiilary array elements back to the BST, keeping the structure of the BST same. Time complexity of this method is O(nLogn) and auxiliary space needed is O(n).
 */
class Solution1
{
public:
    void	recoverTree(TreeNode *root);
private:
	void	generateVector(TreeNode *pNode, vector<int>& data);
	void	sortTheVector(vector<int>& data);
	void	fillBackDataToTree(TreeNode *pNode, int& nIndex, vector<int>& data);
};

// find the two node
void Solution1::recoverTree(TreeNode *root)
{
	vector<int> data;
	generateVector(root, data);
	sortTheVector(data);
	int nIndex = 0;
	fillBackDataToTree(root, nIndex, data);
}

/**
	Use inode pass to fill data
 */
void Solution1::generateVector(TreeNode *pNode, vector<int>& data)
{
	if(!pNode)
		return;
	generateVector(pNode->left, data);
	data.push_back(pNode->val);
	generateVector(pNode->right, data);
}

void Solution1::sortTheVector(vector<int>& data)
{
	sort(data.begin(), data.end());
}

void Solution1::fillBackDataToTree(TreeNode *pNode, int& nIndex, vector<int>& data)
{
	if(!pNode)
		return;
	fillBackDataToTree(pNode->left, nIndex, data);
	pNode->val = data[nIndex];
	++nIndex;
	fillBackDataToTree(pNode->right, nIndex, data);
}

/*
Solution2: We can solve this in O(n) time and with a single traversal of the given BST. Since inorder traversal of BST is always a sorted array, the problem can be reduced to a problem where two elements of a sorted array are swapped. There are two cases that we need to handle:
1. The swapped nodes are not adjacent in the inorder traversal of the BST.
 For example, Nodes 5 and 25 are swapped in {3 5 7 8 10 15 20 25}. 
 The inorder traversal of the given tree is 3 25 7 8 10 15 20 5 
If we observe carefully, during inorder traversal, we find node 7 is smaller than the previous visited node 25. Here save the context of node 25 (previous node). Again, we find that node 5 is smaller than the previous node 20. This time, we save the context of node 5 ( current node ). Finally swap the two node¡¯s values.

2. The swapped nodes are adjacent in the inorder traversal of BST.
  For example, Nodes 7 and 8 are swapped in {3 5 7 8 10 15 20 25}. 
  The inorder traversal of the given tree is 3 5 8 7 10 15 20 25 
Unlike case #1, here only one point exists where a node value is smaller than previous node value. e.g. node 7 is smaller than node 8.

How to Solve? We will maintain three pointers, first, middle and last. When we find the first point where current node value is smaller than previous node value, we update the first with the previous node & middle with the current node. When we find the second point where current node value is smaller than previous node value, we update the last with the current node. In case #2, we will never find the second point. So, last pointer will not be updated. After processing, if the last node value is null, then two swapped nodes of BST are adjacent.

 */
class Solution2
{
public:
	Solution2() : m_pNode1(NULL),m_pNode2(NULL),m_pNode3(NULL){} 
    void	recoverTree(TreeNode *root);
private:
	void	find(TreeNode *pNode, TreeNode *&pPrev);
private:
	TreeNode *m_pNode1;
	TreeNode *m_pNode2;
	TreeNode *m_pNode3;
};



void Solution2::recoverTree(TreeNode *root)
{
	TreeNode *pPrev = NULL;
	
	find(root, pPrev);
	if(!m_pNode3)
		swap(m_pNode1->val, m_pNode2->val);
	else
		swap(m_pNode1->val, m_pNode3->val);
}


/**
	Find the three nodes m_pNode1, m_pNode2 and m_pNode3
	Also ruturn the first/last node of the tree pNode
 */
void Solution2::find(TreeNode *pNode, TreeNode *&pPrev)
{
	if(!pNode)
		return;
	
	find(pNode->left, pPrev);
	if(pPrev && pPrev->val>pNode->val)
	{
		if(!m_pNode1)
		{
			m_pNode1 = pPrev;
			m_pNode2 = pNode;
		}
		else
			m_pNode3 = pNode;
	}
	pPrev = pNode;
	find(pNode->right, pPrev);
}


class Solution
{
public:
    void	recoverTree(TreeNode *root);
};

void Solution::recoverTree(TreeNode *root)
{
	Solution2 sol;
	sol.recoverTree(root);
}
