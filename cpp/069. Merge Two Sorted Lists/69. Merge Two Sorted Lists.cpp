/**
		Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		ListNode *result=NULL, *pre=NULL;
		while(l1 && l2) {
			ListNode *&node = (l1->val<=l2->val)?l1:l2;
			(pre?:pre->next:result) = node;
			pre = node;
			node = node->next;
			pre->next = NULL;
		}
		((pre)?pre->next:result) = (l1)?l1:l2;
		return result;
	}
};


class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *result = NULL;
		ListNode *pre = NULL;
		while(l1 && l2) {
			if(l1->val <= l2->val) {
				if(!pre) {
					result = l1;
					pre = l1;
				} else {
					pre->next = l1;
					pre = l1;
				}
				l1 = l1->next;
			} else {
				if(!pre) {
					result = l2;
					pre = l2;
				} else {
					pre->next = l2;
					pre = l2;
				}
				l2 = l2->next;
			}
			pre->next = NULL;
		}
		
		ListNode *r = (l1)?l1:l2;
		if(!pre) {
			result = r;
		} else {
			pre->next = r;
		}
		
		return result;
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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		ListNode *result = NULL;
		ListNode *pre = NULL;
		while(l1 && l2) {
			ListNode *&node = l1->val <= l2->val ? l1: l2;
			ListNode *next = node->next;
			if(!result) {
				result = node;
				pre = node;
			} else {
				pre->next = node;
				pre = node;
			}
			pre->next = NULL;
			node = next;
		}
		
		ListNode *&remainNode = !l1?l2:l1;
		while(remainNode) {
			ListNode *next = remainNode->next;
			if(!result) {
				result = remainNode;
				pre = result;
			} else {
				pre->next = remainNode;
				pre = remainNode;
			}
			
			pre->next = NULL;
			remainNode = next;
		}
		
		return result;
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
class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2);
};


ListNode *Solution::mergeTwoLists(ListNode *l1, ListNode *l2)
{
	ListNode *result = NULL;
	ListNode *next = NULL;
	
	while(l1 || l2)
	{
		ListNode *node = NULL;
		if(l1 && l2)
		{
			if(l1->val <= l2->val)
			{
				node= l1;
				l1 = l1->next;
			}
			else
			{
				node= l2;
				l2 = l2->next;
			}
		}
		else if(l1)
		{
			node = l1;
			l1 = l1->next;
		}
		else
		{
			node= l2;
			l2 = l2->next;
		}
		
		if(!result)
		{
			result= node;
			next = result;
			next->next = NULL;
		}
		else
		{
			next->next = node;
			next = node;
			next->next = NULL;
		}
	}
	
	return result;
}

