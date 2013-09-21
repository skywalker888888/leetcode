/**
		Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
		For example,
		Given 1->2->3->3->4->4->5, return 1->2->5.
		Given 1->1->1->2->3, return 2->3.
		
		See also: 51. Remove Duplicates from Sorted List
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
    ListNode *deleteDuplicates(ListNode *head) {
		ListNode *result = NULL;
		ListNode *pre = NULL;
		while(head) {
			ListNode *next = head->next;
			if(!next || next->val!=head->val) {
				if(!pre) {
					result = pre = head;
					head->next = NULL;
				} else {
					pre->next = head;
					pre = head;
					pre->next = NULL;
				}
			} else {
				while(next && next->val == head->val) {
					ListNode *n = next->next;
					next->next = NULL;
					delete next;
					next = n;
				}
				delete head;
			}
			head = next;
		}
		return result;
    }
};














































 
// Pass 2
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
    ListNode *deleteDuplicates(ListNode *head) {
		ListNode *node = head;
		ListNode *pre = NULL;
		head = NULL;
		while(node) {
			ListNode *next = node->next;
			if(next && next->val==node->val){
					while(next && next->val==node->val){
						ListNode *next2 = next->next;
						delete next;
						next = next2;
					}
					// delete node
					delete node;
					node = next;
					continue;
			}
			
			if(pre)
				pre->next = node;
			pre = node;
			node = node->next;
			pre->next = NULL;
			if(!head)
				head = pre;
		}
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
    ListNode *deleteDuplicates(ListNode *head);
};

ListNode *Solution::deleteDuplicates(ListNode *head)
{
	if(!head)
		return head;
		
	ListNode *pNode = head;
	ListNode *pPreNode = NULL;
	
	while(pNode)
	{
		bool bDelete = false;
		if(pNode->next && pNode->next->val==pNode->val)
			bDelete = true;
		if(bDelete)
		{
			ListNode *pPostNode = pNode->next;
			while(pPostNode && pPostNode->val==pNode->val)
			{
				ListNode *pNext = pPostNode->next;
				pNode->next = pNext;
				delete pPostNode;
				pPostNode = pNext;
			}
			
			// delete pNode itself
			if(pPreNode)
			{
				pPreNode->next = pNode->next;
				delete pNode;
				pNode = pPreNode->next;
			}
			else
			{
				if(head == pNode)
				{
					head = pNode->next;
					delete pNode;
					pNode = head;
				}
				else
				{
					head->next = pNode->next;
					delete pNode;
					pNode = head->next;
				}
			}
		}
		else 
		{
			pPreNode = pNode;
			pNode = pNode->next;
		}
	}
	
	return head;
}
