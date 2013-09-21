/**
		Reverse a linked list from position m to n. Do it in-place and in one-pass.

		For example:
		Given 1->2->3->4->5->NULL, m = 2 and n = 4,

		return 1->4->3->2->5->NULL.

		Note:
		Given m, n satisfy the following condition:
		1 <= m <= n <= length of list.
		
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
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
		ListNode *node = head;
		ListNode *pre = NULL;
		if(m == n)
			return head;
			
		for(int i=1; node && i<m; ++i) {
			pre = node;
			node = node->next;
		}
		if(!node)
			return head; // invalid problem
		
		ListNode *node1 = node;
		ListNode *node2 = NULL;
		
		ListNode *pre2 = NULL;
		
		for(int i=m; i<=n; ++i) {
			ListNode *next = node->next;
			node->next = pre2;
			pre2 = node;
			node = next;
			if(node && i==n)
				node2 = node;
		}
		if(pre)
			pre->next = pre2;
		else
			head = pre2;
		node1->next = node2;
		return head;
    }
};












































// pass 2
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
		ListNode *pre = NULL;
		ListNode *node = NULL;
		
		node = head;
		for(int i=1; i<m && node; ++i){
			pre = node;
			node = node->next;
		}
		
		if(!node)
			return head; // invalid
		
		ListNode *first = NULL;
		ListNode *last = NULL;
		for(int i=m; i<=n; ++i){
			if(!node)
				break;
			if(!first)
				first = node;
			ListNode *next = node->next;
			node->next = last;
			last = node;
			node = next;
		}
		
		if(first)
			first->next = node;
		if(m == 1)
			head = last;
		else
			pre->next = last;
			
		return head;
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
class Solution
{
public:
    ListNode *reverseBetween(ListNode *head, int m, int n);
};

ListNode *Solution::reverseBetween(ListNode *head, int m, int n)
{
	if(!head)
		return head;
		
	if(m == n)
		return head;
		
	ListNode *pPre = NULL;
	ListNode *pM = NULL;
	ListNode *pN = NULL;
	ListNode *pPost = NULL;
	
	// find pM
	ListNode *pNode = head;
	for(int i=1; i<m; ++i)
	{
		pPre = pNode;
		pNode = pNode->next;
		if(!pNode->next && i<m-1)
			return head; // invalid
	}
	pM = pNode;
	
	// find pN
	pNode = head;
	for(int i=1; i<n; ++i)
	{
		pNode = pNode->next;
		if(!pNode->next && i<m-1)
			return head; // invalid
	}
	pN = pNode;
	pPost = pN->next;
	
	// reverse [pM...pN]
	// NOTE: use stack here will be better
	pNode = pM;
	ListNode *p1 = pNode;
	ListNode *p2 = pNode->next;
	while(p2)
	{
		ListNode *p3 = p2->next;
		p2->next = p1;
		if(p2 == pN)
			break;
		p1 = p2;
		p2 = p3;
		if(!p3)
			break;
		p3 = p3->next;
	}
	
	// add to list
	if(pPre)
		pPre->next = pN;
	else
		head = pN;
	
	pM->next = pPost;
	
	return head;
}


