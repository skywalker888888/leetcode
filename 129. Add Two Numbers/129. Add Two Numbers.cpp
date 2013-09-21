/**
		You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

		Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
		Output: 7 -> 0 -> 8
*/
// pass 3
class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		if(!l1 || !l2)
			return l1?l1:l2;
		
		ListNode *result = NULL;
		ListNode *pre = NULL;
		int carry = 0;
		while(l1 && l2) {
			if(!result) {
				result = l1;
			} else {
				pre->next = l1;
			}
			pre = l1;
			l1 = l1->next;
			pre->next = NULL;
			pre->val += l2->val + carry;
			carry = pre->val/10;
			pre->val %= 10;

			ListNode *tmp = l2;
			l2 = l2->next;
			delete tmp;
		}
		
		pre->next = l1?l1:l2;
		if(pre->next) {
			pre = pre->next;
			while(pre) {
				pre->val += carry;
				carry = pre->val/10;
				pre->val %= 10;
				if(carry && !pre->next) {
					pre->next = new ListNode(carry);
					carry = 0;
				}
				pre = pre->next;
			}
		} else if(carry) {
			pre->next = new ListNode(carry);
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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    	int carry = 0;
		ListNode *result = NULL;
		ListNode *pre = NULL;
		while(l1 || l2) {
			int val = carry;
			ListNode *node = NULL;
			if(l1) {
				node = l1;
				l1 = l1->next;
				val += node->val;
			}
			if(l2) {
				val += l2->val;
				if(!node) {
					node = l2;
					l2 = l2->next;
				} else {
					ListNode *tmp = l2->next;
					delete l2;
					l2 = tmp;
				}
			}
			
			node->val = val%10;
			carry = val/10;
			if(!pre) {
				result = node;
				pre = node;
			} else {
				pre->next = node;
				pre = node;
			}
			pre->next = NULL;
		}
		while(carry) {
			pre->next = new ListNode(carry%10);
			carry /= 10;
			pre = pre->next;
			pre->next = NULL;
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
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
	{

		ListNode *result = NULL;
		ListNode *pre = NULL;
		int ncarry = 0;
		while(l1 && l2)
		{
			int num1 = l1->val;
			int num2 = l2->val;
			int sum = num1 + num2 + ncarry;
			ncarry = sum/10;
			sum %= 10;
			
			if(!pre)
			{
				result = l1;
				l1 = l1->next;
				result->next = NULL;
				pre = result;
			}
			else
			{
				pre->next = l1;
				l1 = l1->next;
				pre = pre->next;
				pre->next = NULL;
			}
			pre->val = sum;
			
			l2 = l2->next;
		}
		
		ListNode *pleftover = NULL;
		if(l1)
			pleftover = l1;
		else 
			pleftover = l2;
		while(pleftover)
		{
			int sum = pleftover->val + ncarry;
			ncarry = sum/10;
			sum %= 10;
			if(!pre)
			{
				result = pleftover;
				pleftover = pleftover->next;
				result->next = NULL;
				pre = result;
			}
			else
			{
				pre->next = pleftover;
				pleftover = pleftover->next;
				pre = pre->next;
				pre->next = NULL;
			}
			pre->val = sum;
		}
		
		if(ncarry)
		{
			if(!pre)
				result = new ListNode(ncarry);
			else 
				pre->next = new ListNode(ncarry);
		}
		
		return result;
	}
};




