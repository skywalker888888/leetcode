/**
		Given a linked list, remove the nth node from the end of list and return its head.
		For example,
			Given linked list: 1->2->3->4->5, and n = 2.
			After removing the second node from the end, the linked list becomes 1->2->3->5.
		Note:
		Given n will always be valid.
		Try to do this in one pass.
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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
    	ListNode *node = head;
		ListNode *pre = NULL;
		while(node) {
			ListNode *nxt = node;
			int count = 0;
			while(nxt) {
				++count;
				nxt = nxt->next;
			}
			if(count == n) {
				if(node == head) {
					ListNode *tmp = head->next;
					delete head;
					head = tmp;
				} else {
					ListNode *tmp = node->next;
					pre->next = tmp;
					delete node;
				}
				break;
			}
			pre = node;
			node = node->next;
		}
		return head;
    }
};






































// pass 2
// Time: O(m)
class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
		int m = 0;
		ListNode *node = head;
		for(; node; node=node->next, ++m) ;
		
		if(m < n)
			return head;
		
		node = head;
		ListNode *pre = NULL;
		for(int i=0; i<m-n; ++i) {
			pre = node;
			node = node->next;
		}
		if(!pre) {
			node = head;
			head = head->next;
			delete node;
			return head;
		}
		
		pre->next = node->next;
		delete node;
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
// Time: O(m * n)
// Space: O(1)
class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
		if(!head || !n)
			return head;
			
		ListNode *node = head;
		ListNode *pre = NULL;
		while(node) {
			ListNode *last = node;
			int i = 0;
			for(; i<n&&last; ++i) 
				last = last->next;
			if(i < n)
				return head;
			if(!last) {
				if(!pre) {
					head = node->next;
					delete node;
				} else {
					pre->next = node->next;
					delete node;
				}
				break;
			} else {
				pre = node;
				node = node->next;
			}
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
	ListNode *removeNthFromEnd(ListNode *head, int n) {
		if(!head || !n)
			return head;
			
		ListNode *p = head;
		ListNode *ppre = NULL;
		while(p) {
			ListNode *next = p;
			for(int i=0; i<n; ++i) {
				if(!next)
					return head;
				next = next->next;
			}
			
			if(!next) {
				// 
				if(!ppre)
					head= head->next;
				else
					ppre->next = p->next;
				delete p;
				break;
			}
			
			ppre = p;
			p = p->next;
		}
		
		return head;
	}
};




