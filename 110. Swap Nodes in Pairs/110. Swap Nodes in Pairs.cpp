/**
		Given a linked list, swap every two adjacent nodes and return its head.
		For example,
		Given 1->2->3->4, you should return the list as 2->1->4->3.
		Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
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
    ListNode *swapPairs(ListNode *head) {
		ListNode *node = head;
		ListNode *pre = NULL;
		head = NULL;
		while(node) {
			if(node->next) {
				ListNode *n1 = node;
				ListNode *n2 = node->next;
				node = n2->next;
				n2->next = n1;
				n1->next = NULL;
				if(!pre)
					head = n2;
				else
					pre->next = n2;
				pre = n1;
			} else {
				if(!pre)
					head = node;
				else
					pre->next = node;
				break;
			}
		}
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
    ListNode *swapPairs(ListNode *head) {
		ListNode *node = head;
		ListNode *pre = NULL;
		while(node && node->next) {
			ListNode *p = node->next->next;
			
			ListNode *p1 = node;
			ListNode *p2 = node->next;
			
			p2->next = p1;
			p1->next = p;

			if(head == p1) {
				head = p2;
			} else {
				pre->next = p2;
			}
			pre = p1;
			node = p;
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
class Solution {
public:
    ListNode *swapPairs(ListNode *head);
};


ListNode *Solution::swapPairs(ListNode *head)
{
	ListNode *p = head;
	ListNode *ppre = NULL;
	ListNode *pnext = NULL;
	
	while(p)
	{
		ListNode *ptail = p->next;
		if(!ptail)
			break;
		
		pnext = ptail->next;
		ptail->next = p;
		if(ppre)
			ppre->next = ptail;
		else
			head = ptail;
		
		p->next = pnext;
		ppre = p;
		p  = pnext;
	}
	
	return head;
}

