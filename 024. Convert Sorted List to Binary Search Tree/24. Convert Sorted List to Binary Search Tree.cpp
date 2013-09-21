/**
		Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
*/
// pass 3
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
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
    TreeNode *sortedListToBST(ListNode *head) {
		if(!head)
			return NULL;
		else if(!head->next) {
			TreeNode *root = new TreeNode(head->val);
			delete head;
			return root;
		}
		ListNode *pPre = NULL;
		ListNode *pMid = head;
		ListNode *node = head;
		while(node && node->next) {
			node = node->next->next; // go farward by 2
			pPre = pMid;
			pMid = pMid->next;
		}
		// if(node) {
			// pPre = pMid;
			// pMid = pMid->next;
		// }
		
		TreeNode *root = new TreeNode(pMid->val);
		
		if(pPre) {
			pPre->next = NULL;
			root->left = sortedListToBST(head);
		}
		
		root->right = sortedListToBST(pMid->next);
		pMid->next = NULL;
		delete pMid;
		return root;
    }
};




















































/////// pass 2
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
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
    TreeNode *sortedListToBST(ListNode *head) {
		int count = 0;
		ListNode *node = head;
		while(node){
			++count;
			node = node->next;
		}
		
		return sortedListToBST(head, count);
    }
	
    TreeNode *sortedListToBST(ListNode *head, int n) {
		if(!n)
			return NULL;
		
		int mid = 0;
		mid = n/2;
		
		if(!mid){
			TreeNode *root = new TreeNode(head->val);
			root->left = NULL;
			root->right = NULL;
			return root;
		}
		// 0...mid-1 mid mid+1 .. n-1
		ListNode *node = head;
		for(int i=0; i<mid-1; ++i){
			node = node->next;
		}
		
		ListNode *nodeMid = node->next;
		TreeNode *root = new TreeNode(nodeMid->val);
		node->next = NULL;
		root->left = sortedListToBST(head, mid);
		node->next = nodeMid;
		root->right = sortedListToBST(nodeMid->next, n-mid-1);
		return root;
	}
};

























/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
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
class Solution
{
public:
    TreeNode *sortedListToBST(ListNode *head);
};

TreeNode *Solution::sortedListToBST(ListNode *head)
{
	if(!head)
		return NULL;
		
	ListNode *pList = head;
	int nCount = 0;
	while(pList)
	{
		pList = pList->next;
		++nCount;
	}
	
	int nMidCount = 0;
	if(nCount %2 != 0)
		nMidCount = nCount/2 + 1;
	else 
		nMidCount = nCount/2;
		
	ListNode *pNodeMid = NULL;
	ListNode *pNodeMidPrev = NULL;
	for(int i=0; i<nMidCount; ++i)
	{
		pNodeMidPrev = pNodeMid;
		if(!pNodeMid)
			pNodeMid = head;
		else 
			pNodeMid = pNodeMid->next;
	}
	
	// 
	TreeNode *pLeftTree=NULL, *pRightTree=NULL, *pNode=NULL;
	if(pNodeMidPrev)
	{
		pNodeMidPrev->next = NULL;
		pLeftTree = sortedListToBST(head);
		pNodeMidPrev->next = pNodeMid;
	}
	

	if(!pNodeMid)
	{
		pNode = new TreeNode(head->val);
		return pNode;
	}
	
	pNode = new TreeNode(pNodeMid->val);
	pNode->left = pLeftTree;
	pRightTree = sortedListToBST(pNodeMid->next);
	pNode->right = pRightTree;
	
	return pNode;
}




