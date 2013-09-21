/**
		Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
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
struct NodeStruct {
	int index;
	ListNode *data;
	NodeStruct(int i, ListNode *d):index(i), data(d) {}
};
class Comparor{
public:
	bool operator()(NodeStruct &n1, NodeStruct &n2) {
		return n1.data->val > n2.data->val;
	}
};
class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
		ListNode *head = NULL;
		ListNode *pre = NULL;
		
		priority_queue<NodeStruct, vector<NodeStruct>, Comparor> minHeap;
		for(int i=0; i<lists.size(); ++i)
			if(lists[i]) {
				minHeap.push(NodeStruct(i, lists[i]));
				lists[i] = lists[i]->next;
			}
		while(!minHeap.empty()) {
			NodeStruct node = minHeap.top();
			minHeap.pop();
			if(!head)
				head = node.data;
			else 
				pre->next = node.data;
			pre = node.data;
			int i = node.index;
			if(lists[i]) {
				minHeap.push(NodeStruct(i, lists[i]));
				lists[i] = lists[i]->next;
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
 // Time: O(n lg k) 
 // Space: O(k)
class Solution {
public:
	struct NodeType {
		int index;
		ListNode *node;
		NodeType(int i, ListNode *p) :index(i), node(p) {}
	};
	class NodeCompare {
	public:
#if 0
		bool operator()(NodeType *n1, NodeType *n2) {
			if(!n1 || !n2 || !n1->node || n2->node)
				return false;
			return n1->node->val >= n2->node->val;
		}
#else
		bool operator()(NodeType &n1, NodeType &n2) {
			if(!n1.node || !n2.node)
				return false;
			return n1.node->val >= n2.node->val;
		}
#endif
	};
	
    ListNode *mergeKLists(vector<ListNode *> &lists) {
		ListNode *head = NULL;
		ListNode *pre = NULL;
		int k = lists.size();
		if(!k)
			return head;
		priority_queue<NodeType, vector<NodeType>, NodeCompare> minheap;
		for(int i=0; i<k; ++i) {
			ListNode *p = lists[i];
			if(p) {
				lists[i] = p->next;
				p->next = NULL;
				minheap.push(NodeType(i, p));
			}
		}
		while(!minheap.empty()) {
			NodeType val = minheap.top();
			ListNode *p = val.node;
			int index = val.index;
			
			minheap.pop();
			if(p) {
				if(!head)
					head = p;
				else
					pre->next = p;
				pre = p;
			}
			if(index>=0 && index<k && lists[index]) {
				ListNode *p = lists[index];
				lists[index] = p->next;
				p->next = NULL;
				minheap.push(NodeType(index, p));
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
	class NodeCompare {
	public:
		bool operator()(ListNode *n1, ListNode *n2) {
			if(!n1 || !n2)
				return false;
			return n1->val >= n2->val;
		}
	};

	ListNode *mergeKLists(vector<ListNode *> &lists) {
		ListNode *head = NULL;
		ListNode *p = NULL;
		ListNode *pnext = NULL;
		if(!lists.size())
			return head;
			
		priority_queue<ListNode *, vector<ListNode *>, NodeCompare> minheap;
		while(true) {
			bool finished = true;
			for(int i=0; i<lists.size(); ++i) {
				ListNode *node = lists[i];
				if(lists[i]) {
					minheap.push(node);
					lists[i] = lists[i]->next;
					finished = false;
				}
			}
			
			if(finished)
				break;
			
			// 
			if(minheap.empty())
				break;
				
			ListNode *pnode = minheap.top();
			minheap.pop();
			pnode->next = NULL;
			if(!head) {
				head = pnode;
				pnext = head;
			} else {
				pnext->next = pnode;
				pnext = pnode;
			}
		}
		
		while(!minheap.empty()) {
			ListNode *pnode = minheap.top();
			minheap.pop();
			pnode->next = NULL;
			if(!head) {
				head = pnode;
				pnext = head;
			} else {
				pnext->next = pnode;
				pnext = pnode;
			}
		}
		
		return head;
	}
};


