/**
		Given a list, rotate the list to the right by k places, where k is non-negative.

		For example:
		Given 1->2->3->4->5->NULL and k = 2,
		return 4->5->1->2->3->NULL.
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
    ListNode *rotateRight(ListNode *head, int k) {

		ListNode *tail = NULL;
		int count = 0;
		ListNode *node = head;
		while(node) {
			++count;
			tail = node;
			node = node->next;
		}
		if(count <= 1)
			return head;

		k %= count;
		if(k <= 0 || !head)
			return head;
		
		ListNode *pre = NULL;
		int rem = count - k;
		
		node = head;
		while(rem) {
			pre = node;
			node = node->next;
			--rem;
		}
		
		tail->next = head;
		pre->next = NULL;
		head = node;
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
    ListNode *rotateRight(ListNode *head, int k) {
		ListNode *tail = NULL;
		ListNode *node = head;
		int count = 0;
		while(node) {
			++count;
			tail = node;
			node = node->next;
		}
		
		if(!count || !k%count)
			return head;
			
		k %= count;
		int precount = count - k;
		node = head;
		tail->next = head;
		head = NULL;
		
		while(--precount)
			node = node->next;
		
		head = node->next;
		node->next = NULL;
		
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
	ListNode *rotateRight(ListNode *head, int k)
	{
		// count
		int nCount = 0;
		ListNode *pNode = head;
		ListNode *pLast = NULL;
		while(pNode) {
			++nCount;
			pLast = pNode;
			pNode = pNode->next;
		}
		
		if(!nCount || !(k % nCount))
			return head;
		
		// make sure k is 1, 2, ..., nCount-1
		k = k % nCount;
		int m = nCount - k;
		
		
		pNode = head;
		while(--m)
			pNode = pNode->next;
		
		// ......(pNode) ()...(pLast)
		pLast->next = head;
		pLast = pNode->next;
		pNode->next = NULL;
		head = pLast;
		return head;
	}
};


