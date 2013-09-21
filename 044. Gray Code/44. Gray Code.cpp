/**
		The gray code is a binary numeral system where two successive values differ in only one bit.

		Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

		For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

		00 - 0
		01 - 1
		11 - 3
		10 - 2
		Note:
		For a given n, a gray code sequence is not uniquely defined.

		For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

		For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
*/
// pass 3
class Solution {
public:
    vector<int> grayCode(int n) {
		if(!n)
			return vector<int>(1, 0);
    	unordered_set<int> visited;
		unsigned long num = 0;
		vector<int> result;
		while(visited.find(num) == visited.end()) {
			visited.insert(num);
			result.push_back((int)num);
			unsigned long tag = 1;
			for(int i=0; i<n; ++i) {
				unsigned long value = num ^ (tag << i);
				if(visited.find(value) == visited.end()) {
					num = value;
					break;
				}
			}
		}
		return result;
    }
};

































// pass 2
class Solution {
public:
    vector<int> grayCode(int n) {
		vector<int> result;
		// DFS
		unsigned long ulLen = (unsigned long)1 << n;
		vector<bool> visited(ulLen, false);
		result.push_back(0);
		visited[0] = true;
		if(!n)
			return result;

		unsigned long num = 0;
		while(n){
			bool bHasNewValue = false;
			for(int i=0; i<n; ++i){
				unsigned long ulTag = (unsigned long)1 << i;
				unsigned long ulNum = num;
				
				ulNum ^= ulTag; // flip one bit
				if(ulNum<=ulLen && !visited[ulNum]){
					visited[ulNum] = true;
					result.push_back((int)ulNum);
					bHasNewValue = true;
					num = ulNum;
					break;
				}
			}
			if(!bHasNewValue)
				break;
		}
		
		return result;
    }
};






























struct _TreeNode
{
	unsigned int	m_nVal;
	vector<unsigned int> 	m_adjNodes;
	bool			m_bVisited;
	
	_TreeNode(int v): m_nVal(v), m_bVisited(false) {}
};

class Solution
{
public:
	Solution();
    vector<int> grayCode(int n);
    vector<int> grayCode2(int n);
	
private:
	bool	diffOnly1Bit(unsigned int m, unsigned int n);
	bool	diffOnly1Bit(unsigned int m, unsigned int n, vector<unsigned int>& bitMap);
	
	vector<unsigned int> 	m_Bit;
};


Solution::Solution()
{
	int nSize = sizeof(unsigned int);
	for(int i=0; i<nSize*8; ++i)
		m_Bit.push_back( ((unsigned int)1) << i);
}


vector<int> Solution::grayCode2(int n)
{
	unsigned int size = 1;
	for(int i=0; i<n; ++i)
		size *= 2;
		
	vector<_TreeNode> graph;
	for(int i=0; i<size; ++i)
		graph.push_back(_TreeNode((unsigned int) i));

	for(int i=0; i<graph.size(); ++i)
		for(int j=i+1; j<graph.size(); ++j)
			if(diffOnly1Bit(graph[i].m_nVal, graph[j].m_nVal))
			{
				vector<unsigned int> &iAdjs = graph[i].m_adjNodes;
				if(find(iAdjs.begin(), iAdjs.end(), graph[j].m_nVal) == iAdjs.end())
					iAdjs.push_back(graph[j].m_nVal);
					
				vector<unsigned int> &jAdjs = graph[j].m_adjNodes;
				if(find(jAdjs.begin(), jAdjs.end(), graph[i].m_nVal) == jAdjs.end())
					jAdjs.push_back(graph[i].m_nVal);
			}
			
	int nStartIndex = 0;
	for(int i=0; i<graph.size(); ++i)
		if(graph[i].m_adjNodes.size() % 2)
		{
			nStartIndex = i;
			break;
		}
	
	// DFS
	vector<int> result;
	result.push_back(nStartIndex);
	graph[nStartIndex].m_bVisited = true;
	bool bQuit = false;
	while(!bQuit)
	{
		bQuit = true;
		int nNodeId = result[result.size() - 1];
		for(int i=0; i<graph[nNodeId].m_adjNodes.size(); ++i)
		{
			unsigned int nIndex = graph[nNodeId].m_adjNodes[i];
			if(!graph[nIndex].m_bVisited)
			{
				graph[nIndex].m_bVisited = true;
				result.push_back(nIndex);
				bQuit = false;
				break;
			}
		}
	}
	
	return result;
}

bool Solution::diffOnly1Bit(unsigned int m, unsigned int n)
{
	return diffOnly1Bit(m, n, m_Bit);
}

bool Solution::diffOnly1Bit(unsigned int m, unsigned int n, vector<unsigned int>& bitMap)
{
	unsigned int num = m ^ n;
	int nDiff = 0;
	for(int i=0; i<bitMap.size(); ++i)
		if(bitMap[i] & num)
			++nDiff;
	return nDiff==1;
}



vector<int> Solution::grayCode(int n)
{
	vector<int> result;
	
	vector<unsigned int> 	bitMap;
	unsigned int size = 1;
	for(int i=0; i<n; ++i)
	{
		size *= 2;
		bitMap.push_back( ((unsigned int)1) << i );
	}
		
	bool bQuit = false;
	result.push_back(0);
	set<unsigned int> visitedNodes;
	visitedNodes.insert(0);
	while(!bQuit)
	{
		bQuit = true;
		unsigned int nValue = result[result.size() -1 ];
		for(unsigned int i=0; i<size; ++i)
			if(visitedNodes.find(i)==visitedNodes.end() && diffOnly1Bit(nValue, i, bitMap))
			{
				bQuit = false;
				result.push_back(i);
				visitedNodes.insert(i);
				break;
			}
	}
	
	return result;
}


