/**
	17. Populating Next Right Pointers in Each Node
		Given a binary tree

			struct TreeLinkNode {
			  TreeLinkNode *left;
			  TreeLinkNode *right;
			  TreeLinkNode *next;
			}
		Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

		Initially, all next pointers are set to NULL.

		Note:

		You may only use constant extra space.
		You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
		For example,
		Given the following perfect binary tree,
				 1
			   /  \
			  2    3
			 / \  / \
			4  5  6  7
		After calling your function, the tree should look like:
				 1 -> NULL
			   /  \
			  2 -> 3 -> NULL
			 / \  / \
			4->5->6->7 -> NULL
			
		Analysis:
			Use BFS search.
 */
// pass 3
// Bse next as the queue for BFS
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
		if(!root)
			return;
		TreeLinkNode *queue = root;
		root->next = NULL;
		while(queue) {
			TreeLinkNode *tmpQueue = NULL;
			TreeLinkNode *tmpQueueHead = NULL;
			while(queue) {
				TreeLinkNode *tmp = queue->next;
				if(queue->left || queue->right) {
					if(!tmpQueue) {
						tmpQueue = (queue->left)?queue->left:queue->right;
						tmpQueueHead = tmpQueue;
					}
					tmpQueue->next = NULL;
					if(queue->left && tmpQueue!=queue->left) {
						tmpQueue->next = queue->left;
						tmpQueue = queue->left;
						tmpQueue->next = NULL;
					}
					if(queue->right && tmpQueue!=queue->right) {
						tmpQueue->next = queue->right;
						tmpQueue = queue->right;
						tmpQueue->next = NULL;
					}
				}
				queue = tmp;
			}
				
			queue = tmpQueueHead;
		}
    }
};



























// pass 2
class Solution {
public:
    void connect(TreeLinkNode *root) {
		if(!root)
			return;
			
		TreeLinkNode* hdr = root;
		int depth = 0;
		hdr->next = NULL;
		
		connect(root, hdr, depth);
		while(hdr) {
			TreeLinkNode* node = hdr;
			hdr = hdr->next;
			node->next = NULL;
		}
    }
	
	void connect(TreeLinkNode *root, TreeLinkNode* hdr, int depth) {
		if(!root)
			return;
		
		TreeLinkNode* pre=NULL, *node=hdr;
		if(depth > 0) {
			int i = 0;
			while(node && i<depth) {
				pre = node;
				node = node->next;
				++i;
			}
			
			if(!node) {
				pre->next = root;
				root->next = NULL;
			} else {
				pre->next = root;
				root->next = node->next;
				node->next = root;
			}
		}
		connect(root->left, hdr, depth+1);
		connect(root->right, hdr, depth+1);
	}
};

 
 
 
 
 
 
 
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

class Solution
{
public:
	void connect(TreeLinkNode *root)
	{
		m_nHeight = 0;
		m_vNodes.clear();
		DFS(root);
	}

	void DFS(TreeLinkNode *pNode)
	{
		if(!pNode)
			return;
			
		++m_nHeight;
		if(m_vNodes.size() < m_nHeight)
		{
			m_vNodes.push_back(pNode);
			pNode->next = NULL;
		}
		else
		{
			TreeLinkNode *pPreVNode = m_vNodes[m_nHeight-1];
			pPreVNode->next = pNode;
			m_vNodes[m_nHeight-1] = pNode;
		}
		pNode->next = NULL;
		
		DFS(pNode->left);
		DFS(pNode->right);
		
		--m_nHeight;
	}
	
private:
	int						m_nHeight;
	vector<TreeLinkNode *>	m_vNodes;
};

