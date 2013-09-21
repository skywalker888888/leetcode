/**
		Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

		You should preserve the original relative order of the nodes in each of the two partitions.

		For example,
		Given 1->4->3->2->5->2 and x = 3,
		return 1->2->2->4->3->5.
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
    ListNode *partition(ListNode *head, int x) {
		ListNode *pre=NULL, *tail=NULL;
		ListNode *node = head;
		head = NULL;
		while(node) {
			ListNode *n = node->next;
			node->next = NULL;
			if(node->val < x) {
				if(!pre) {
					node->next = head;
					pre = node;
					head = node;
				} else {
					node->next = pre->next;
					pre->next = node;
					pre = node;
				}
			} else {
				if(!tail) {
					tail = node;
					if(pre) {
						pre->next = node;
					} else {
						head = node;
					}
				} else {
					tail->next = node;
					tail = node;
				}
			}
			node = n;
		}
		return head;
	}
};

class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
		ListNode *pre = NULL;
		ListNode *tail = NULL;
		ListNode *node = head;
		head = NULL;
		while(node) {
			ListNode *n = node->next;
			node->next = NULL;
			if(!pre && !tail) {
				if(node->val < x) {
					pre = node;
					head = node;
				} else {
					tail = node;
					head = node;
				}
			} else if(!pre) {
				if(node->val < x) {
					pre = node;
					pre->next = head;
					head = node;
				} else {
					tail->next = node;
					tail = node;
				}
			} else if(!tail) {
				if(node->val < x) {
					node->next = pre->next;
					pre->next = node;
					pre = node;
				} else {
					pre->next = node;
					tail = node;
				}
			} else {
				if(node->val < x) {
					node->next = pre->next;
					pre->next = node;
					pre = node;
				} else {
					tail->next = node;
					tail = node;
				}
			}
			node = n;
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
    ListNode *partition(ListNode *head, int x) {
		ListNode *i = NULL;
		ListNode *j = NULL;
		ListNode *node = head;
		head = NULL;
		while(node){
			ListNode *next = node->next;
			node->next = NULL;
			if(!head){
				head = node;
				if(head->val < x)
					i = head;
				else
					j = head;
			}else if(node->val < x) {
				//
				if(!i) {
					node->next = head;
					head = node;
					i = node;
				}else {
					node->next = i->next;
					i->next = node;
					i = node;
				}
			}else {
				if(!j){
					i->next = node;
					node->next = NULL;
					j = node;
				}else{
					node->next = NULL;
					j->next = node;
					j = node;
				}
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
	ListNode *partition(ListNode *head, int x)
	{
		if(!head)
			return head;
			
		ListNode *pNode = head;
		head = NULL;
		ListNode *pPre = NULL;
		while(pNode) {
			if(pNode->val >= x) {
				pPre = pNode;
				pNode = pNode->next;
			} else {
				if(pPre) {
					pPre->next = pNode->next;
					pNode->next = head;
					head = pNode;
					pNode = pPre->next;
				} else 
					pNode = pNode->next;
			}
		}
		
		return head;
	}
};



