/**
		Populating Next Right Pointers in Each Node
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
		
		///////////////////////////////////////////////////////////////////////////////////////
		
		Follow up for problem "Populating Next Right Pointers in Each Node".

		What if the given tree could be any binary tree? Would your previous solution still work?

		Note:

		You may only use constant extra space.
		For example,
		Given the following binary tree,
				 1
			   /  \
			  2    3
			 / \    \
			4   5    7
		After calling your function, the tree should look like:
				 1 -> NULL
			   /  \
			  2 -> 3 -> NULL
			 / \    \
			4-> 5 -> 7 -> NULL
			
	Analysis:
		We will use the right most nodes' next pointer. 
		We remember the right edge and will adjust the next pointers when necessary.
*/
///////////////// pass 3
// Use next as the queue for BFS
class Solution {
public:
    void connect(TreeLinkNode *root) {
		TreeLinkNode *que, *nextque = NULL;
		que = root;
		
		TreeLinkNode *nextquetail = NULL;
		while(que)
		{
			enqueunode(que->left, nextque, nextquetail);
			enqueunode(que->right, nextque, nextquetail);
			que = que->next;
			if(!que)
			{
				que = nextque;
				nextque = NULL;
				nextquetail = NULL;
			}
		}
	}
	void enqueunode(TreeLinkNode *node, TreeLinkNode *&nextque, TreeLinkNode *&nextquetail)
	{
		if(!node)
			return;
		if(!nextquetail)
		{
			nextque = node;
			nextquetail = node;
			nextquetail->next = NULL;
		}
		else
		{
			nextquetail->next = node;
			nextquetail = nextquetail->next;
			nextquetail->next = NULL;
		}
	}
};

/////////////// pass 2
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
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
		if(!root)
			return;
			
		TreeLinkNode* hdr = root;
		int depth = 0;
		hdr->next = NULL;
		
		connect(root, hdr, depth);
		while(hdr)
		{
			TreeLinkNode* node = hdr;
			hdr = hdr->next;
			node->next = NULL;
		}
    }
	
	void connect(TreeLinkNode *root, TreeLinkNode* hdr, int depth)
	{
		if(!root)
			return;
		
		TreeLinkNode* pre=NULL, *node=hdr;
		if(depth > 0)
		{
			int i = 0;
			while(node && i<depth)
			{
				pre = node;
				node = node->next;
				++i;
			}
			
			if(!node)
			{
				pre->next = root;
				root->next = NULL;
			}
			else
			{
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
	void			connect(TreeLinkNode *root);
private:
	void			DFS(TreeLinkNode *pNode);
private:
	int				m_nHeight;
	TreeLinkNode	*m_pRightEdge;
	int				m_nEdgeLen;
};

void Solution::connect(TreeLinkNode *root)
{
	m_nHeight = 0;
	m_pRightEdge = NULL;
	m_nEdgeLen = 0;
	DFS(root);
	
	TreeLinkNode *pEdge = m_pRightEdge;
	while(pEdge)
	{
		TreeLinkNode *pNext = pEdge->next;
		pEdge->next = NULL;
		pEdge = pNext;
	}
}

void Solution::DFS(TreeLinkNode *pNode)
{
	if(!pNode)
		return;
		
	++m_nHeight;
	if(m_nHeight == 1)
	{
		m_pRightEdge = pNode;
		m_pRightEdge->next = NULL;
		++m_nEdgeLen;
	}
	else if(m_nEdgeLen < m_nHeight)
	{
		// add the one to the end
		TreeLinkNode *pEdge = m_pRightEdge;
		while(pEdge->next)
		{
			pEdge = pEdge->next;
		}
		pEdge->next = pNode;
		pEdge = pNode;
		pEdge->next = NULL;
		++m_nEdgeLen;
	}
	else // 
	{
		TreeLinkNode *pEdge = m_pRightEdge;
		for(int i=0; i<m_nHeight-2; ++i)
			pEdge = pEdge->next;
			
		pNode->next = pEdge->next->next;
		pEdge->next->next = pNode;
		pEdge->next = pNode;
	}
	
	DFS(pNode->left);
	DFS(pNode->right);
	
	--m_nHeight;
}
