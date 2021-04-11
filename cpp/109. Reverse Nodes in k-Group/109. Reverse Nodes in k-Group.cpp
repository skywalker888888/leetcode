/**
		Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
		If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
		You may not alter the values in the nodes, only nodes itself may be changed.
		Only constant memory is allowed.
		For example,
		Given this linked list: 1->2->3->4->5
		For k = 2, you should return: 2->1->4->3->5
		For k = 3, you should return: 3->2->1->4->5
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
    ListNode *reverseKGroup(ListNode *head, int k) {
		if(k < 2)
			return head;
		
		ListNode *node = head;
		head = NULL;
		ListNode *tail = NULL;
		
		while(node) {
			// keep reversing
			ListNode *pre = NULL;
			ListNode *n1 = node;
			int count = 0;
			while(node && count<k) {
				ListNode *tmp = node->next;
				node->next = pre;
				pre = node;
				//pre->next = NULL;
				node = tmp;
				++count;
			}
			if(count == k) {
				if(!tail) {
					head = pre;
				} else {
					tail->next = pre;
				}
				tail = n1;
			}else {
				// reverse back
				ListNode *p1 = NULL;
				while(pre) {
					ListNode *tmp = pre->next;
					pre->next = p1;
					p1 = pre;
					pre = tmp;
				}
				if(!head)
					head = p1;
				else
					tail->next = p1;
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
    ListNode *reverseKGroup(ListNode *head, int k) {
		if(k <= 1)
			return head;
		ListNode *node = head;

		ListNode *newhead = NULL;
		ListNode *pre = NULL;
		
		while(node) {
			ListNode *first = node;
			ListNode *last = NULL;
			int i=0;
			for(; i<k && node; ++i) {
				last = node;
				node = node->next;
			}
			if(i < k)
				break;
			// reverse [first..last]
			ListNode *p1 = first;
			ListNode *p2 = p1->next;
			while(p1 != last) {
				ListNode *p3 = p2->next;
				p2->next = p1;
				p1 = p2;
				p2 = p3;
			}
			if(!newhead) {
				newhead = last;
				head = newhead;
				pre = first;
			} else {
				pre->next = last;
				pre = first;
			}
			pre->next = node;
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
	ListNode *reverseKGroup(ListNode *head, int k)
	{
		if(k < 2)
			return head;
		
		ListNode *pprev = NULL;
		ListNode *pnext = NULL;
		
		ListNode *p = head;
		while(p) {
			ListNode *ptail = p;
			for(int i=0; i<k-1; ++i) {
				if(!ptail) {
					ptail = NULL;
					break;
				}
				ptail = ptail->next;
			}
			
			if(!ptail)
				return head;
			pnext = ptail->next;
			if(ptail == p->next)
				ptail->next = p;
			else {
				ListNode *p1 = p;
				ListNode *p2 = p1->next;
				while(p2 != pnext) {
					ListNode *p3 = p2->next;
					p2->next = p1;
					p1 = p2;
					p2 = p3;
				}
			}
			p->next = pnext;
			if(pprev)
				pprev->next = ptail;
			else
				head = ptail;
			pprev = p;
			p = pnext;
		}
		
		return head;
	}
};



