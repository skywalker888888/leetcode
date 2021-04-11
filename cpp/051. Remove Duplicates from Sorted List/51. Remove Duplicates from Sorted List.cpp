/**
		Given a sorted linked list, delete all duplicates such that each element appear only once.
		For example,
		Given 1->1->2, return 1->2.
		Given 1->1->2->3->3, return 1->2->3.
		
		See also: 50. Remove Duplicates from Sorted List II
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
		ListNode *pre = head;
		ListNode *node = head;
		while(node) {
			ListNode *next = node->next;
			while(next && next->val==node->val) {
				pre->next = next->next;
				next->next = NULL;
				delete next;
				next = pre->next;
			}
			node = next;
			pre = next;
		}
		return head;
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
		while(node){
			ListNode *next = node->next;
			node->next = NULL;
			if(!pre){
				head = node;
				pre = head;
			} else{
				pre->next = node;
				pre = node;
			}
			
			while(next && next->val == node->val){
				ListNode *tmp = next;
				next = next->next;
				delete tmp;
			}
			
			node = next;
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
	ListNode *pNode = head;
	ListNode *pPre = NULL;
	while(pNode)
	{
		if(pPre && pPre->val == pNode->val)
		{
			pPre->next = pNode->next;
			delete pNode;
			pNode = pPre->next;
		}
		else
		{
			pPre = pNode;
			pNode = pNode->next;
		}
	}
	return head;
}
