/**
		Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:

		Only one letter can be changed at a time
		Each intermediate word must exist in the dictionary

		For example,
		Given:
		start = "hit"
		end = "cog"
		dict = ["hot","dot","dog","lot","log"]
		Return
		  [
			["hit","hot","dot","dog","cog"],
			["hit","hot","lot","log","cog"]
		  ]
		Note:
		All words have the same length.
		All words contain only lowercase alphabetic characters.
*/
// pass 3








































// #include <unordered_set>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

#define unordered_set	set
#define unordered_map	map

/**
		Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:

		Only one letter can be changed at a time
		Each intermediate word must exist in the dictionary

		For example,
		Given:
		start = "hit"
		end = "cog"
		dict = ["hot","dot","dog","lot","log"]
		Return
		  [
			["hit","hot","dot","dog","cog"],
			["hit","hot","lot","log","cog"]
		  ]
		Note:
		All words have the same length.
		All words contain only lowercase alphabetic characters.
		
		Analysis:
			1. Brute force method: can BFS the tree, until get the result at some layer
			
			2.
				First, create adjecent graph
				Then, do BFS
				
			
			
		Solution:
			See:
				http://discuss.leetcode.com/questions/1051/word-ladder-ii
				https://github.com/Kicksend/mailcheck/wiki/String-Distance-Algorithms
				http://www.csse.monash.edu.au/~lloyd/tildeAlgDS/Dynamic/Edit/
*/


























// pass 1
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Solution
{
	vector<string>				m_nodes;
	vector<vector<int> >		m_adj;
    void buildGraph(unordered_set<string> &dict) {
		unordered_map<string, int>	mapnodes;
		for(auto itr=dict.begin(); itr!=dict.end(); itr++) {
			mapnodes[*itr] = m_nodes.size();
			m_nodes.push_back(*itr);
		}

		m_adj.resize(m_nodes.size());
		
		for(int i=0; i<m_nodes.size(); ++i) {
			string str = m_nodes[i];
			for(int j=0; j<str.size(); ++j) {
				for(char ch='a'; ch<='z'; ++ch)
					if(ch != m_nodes[i][j]) {
						str[j] = ch;
						if(mapnodes.count(str))
							m_adj[i].push_back(mapnodes[str]);
					}
				str[j] = m_nodes[i][j];
			}
		}
	}
	void generateResult(int v1, int v2, vector<vector<int> > &pre, vector<int> &path, vector<vector<string> > &result) {
		path.push_back(v2);
		if(v1==v2 && path.size()>1) {
			result.push_back(vector<string>());
			for(vector<int>::reverse_iterator ritr = path.rbegin(); ritr!=path.rend(); ++ritr)
				result.back().push_back(m_nodes[*ritr]);
			
		}
		else
			for(int i=0; i<pre[v2].size(); ++i)
				generateResult(v1, pre[v2][i], pre, path, result);
		path.pop_back();
	}
	
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
		dict.insert(start);
		dict.insert(end);

		m_nodes.clear();
		m_adj.clear();
		
		buildGraph(dict);
		queue<int> quenodes;

		vector<vector<int> > pre(m_nodes.size());
		vector<int> distance(m_nodes.size());

		int startindex=0; // = m_mapnodes[start];
		int endindex=0; // = m_mapnodes[end];
		while(m_nodes[startindex]!=start) ++startindex;
		while(m_nodes[endindex]!=end) ++endindex;
		
		// quenodes.push(startindex);
		// distance[startindex] = 0;
		for(int i=0; i<m_adj[startindex].size(); ++i) {
			int v = m_adj[startindex][i];
			quenodes.push(v);
			pre[v].push_back(startindex);
			distance[v] = 1;
		}
		while(!quenodes.empty()) {
			int v = quenodes.front();
			quenodes.pop();
			if(v == endindex)
				break;
			int d = distance[v] + 1;
			for(int i=0; i<m_adj[v].size(); ++i) {
				int adjv = m_adj[v][i];
				if(!pre[adjv].size()) {
					distance[adjv] = d;
					pre[adjv].push_back(v);
					quenodes.push(adjv);
				}
				else if(distance[adjv] == d)
					pre[adjv].push_back(v);
			}
		}
		
		vector<vector<string> > result;
		vector<int> path;
		generateResult(startindex, endindex, pre, path, result);
		
		return result;	
	}
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Solution
{
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict);
private:
    inline void buildGraph(string start, string end, unordered_set<string> &dict);
	inline void bfsGraph(string start, string end);
	inline void generateResult(int start, int end, vector<int> &path, vector<vector<string> > &result);
	
	unordered_map<string, int>	m_mapnodes;
	vector<string>				m_nodes;
	vector<vector<int> >		m_pre;
	vector<int>					m_distance;
	vector<vector<int> >		m_adj;
	int							m_startindex;
	int							m_endindex;
};

void Solution::buildGraph(string start, string end, unordered_set<string> &dict)
{
	dict.insert(start);
	dict.insert(end);
	
	for(unordered_set<string>::iterator itr = dict.begin(); itr!=dict.end(); ++itr)
	{
		m_mapnodes[*itr] = m_nodes.size();
		m_nodes.push_back(*itr);
	}

	m_pre.resize(m_nodes.size());
	m_distance.resize(m_nodes.size());
	m_adj.resize(m_nodes.size());
	
	for(int i=0; i<m_nodes.size(); ++i)
	{
		string str = m_nodes[i];
		for(int j=0; j<str.size(); ++j)
		{
			for(char ch='a'; ch<='z'; ++ch)
				if(ch != m_nodes[i][j])
				{
					str[j] = ch;
					if(m_mapnodes.count(str))
						m_adj[i].push_back(m_mapnodes[str]);
				}
			str[j] = m_nodes[i][j];
		}
	}
}

void Solution::bfsGraph(string start, string end)
{
	int startindex = m_mapnodes[start];
	int endindex = m_mapnodes[end];
	
	queue<int> quenodes;
	quenodes.push(startindex);
	m_distance[startindex] = 0;
	
	while(!quenodes.empty())
	{
		int v = quenodes.front();
		quenodes.pop();
		if(v == endindex)
			break;
		int d = m_distance[v] + 1;
		for(int i=0; i<m_adj[v].size(); ++i)
		{
			int adjv = m_adj[v][i];
			if(!m_pre[adjv].size())
			{
				m_distance[adjv] = d;
				m_pre[adjv].push_back(v);
				quenodes.push(adjv);
			}
			else if(m_distance[adjv] == d)
				m_pre[adjv].push_back(v);
		}
	}
}

void Solution::generateResult(int start, int end, vector<int> &path, vector<vector<string> > &result)
{
	path.push_back(end);
	if(start==end && path.size()>1)
	{
		result.push_back(vector<string>());
		for(vector<int>::reverse_iterator ritr = path.rbegin(); ritr!=path.rend(); ++ritr)
			result.back().push_back(m_nodes[*ritr]);
		
	}
	else
		for(int i=0; i<m_pre[end].size(); ++i)
			generateResult(start, m_pre[end][i], path, result);
	path.pop_back();
}

vector<vector<string> > Solution::findLadders(string start, string end, unordered_set<string> &dict)
{
	buildGraph(start, end, dict);
	bfsGraph(start, end);

	vector<vector<string> > result;
	vector<int> path;
	generateResult(m_mapnodes[start], m_mapnodes[end], path, result);
	
	return result;
}



class Solution {
    vector<string> vdict;
    vector<vector<int> > adj;

    void build(unordered_set<string> &dict){
        int i, j;
        vdict.clear();
        unordered_map<string, int> ids;
        for(auto it=dict.begin(); it != dict.end(); it++){
            ids[*it] = vdict.size();
            vdict.push_back(*it);

        }
        adj.clear();
        adj.resize(vdict.size());
        for(int i = 0; i < vdict.size(); i++){
            string w = vdict[i];
            for(int j = 0; j < vdict[i].size(); j++){
                for(char c = 'a'; c <= 'z'; c++)
                    if(c != vdict[i][j]){
                        w[j] = c;
                        if(ids.count(w)){
                            adj[i].push_back(ids[w]);
                        }
                        w[j] = vdict[i][j];
                    }
            }
        }
    }

    void gen(int v1, int v2, vector<vector<int> >& prev, vector<int>& path, vector<vector<string> >&ans){
        path.push_back(v2);
        if(v2 == v1 and path.size() > 1){
            ans.push_back(vector<string>());
            for(auto rit = path.rbegin(); rit != path.rend(); rit++){
                ans.back().push_back(vdict[*rit]);
            }
        }else{
            int i;
            for(i = 0; i < prev[v2].size(); i++){
                gen(v1, prev[v2][i], prev, path, ans);
            }
        }
        path.pop_back();
    }
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        dict.insert(start);
        dict.insert(end);
        build(dict);
        queue<int> que;
        vector<vector<int> > prev(vdict.size());
        vector<int> distance(vdict.size());

        int v, v1, v2;
        for(v1 = 0; vdict[v1] != start; v1++);
        for(v2 = 0; vdict[v2] != end; v2++);
        for(int i = 0; i < adj[v1].size(); i++){
            v = adj[v1][i];
            que.push(v);
            prev[v].push_back(v1);
            distance[v] = 1;
        }
        while(not que.empty()){
            int v1 = que.front(); que.pop();
            if(v1 == v2) break;
            int d = distance[v1] + 1;
            for(int i = 0; i < adj[v1].size(); i++){
                v = adj[v1][i];
                if(prev[v].size() == 0){
                    prev[v].clear();
                    prev[v].push_back(v1);
                    distance[v] = d;
                    que.push(v);
                }else if(distance[v] == d){
                    prev[v].push_back(v1);
                }
            }
        }

        vector<vector<string> > ans;

        vector<int> path;
        gen(v1, v2, prev, path, ans);

        return ans;
    }
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







struct _NODE
{
	string val;
	vector<int> adj;
	vector<int> pre;
	int			distance;
	
	_NODE(string v) : val(v), distance(-1) {}
};

class Solution
{
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict);
private:
	void generateResult(int index, int endindex, vector<_NODE> &graph, vector<int> &path, vector<vector<string> > &result);
};

vector<vector<string> > Solution::findLadders(string start, string end, unordered_set<string> &dict)
{
	vector<vector<string> > result;
	
	vector<_NODE> graph;
	
	// Generate the graph and return the start/end index
	dict.insert(start);
	dict.insert(end);
	unordered_map<string, int> nodemap;
	
	for(unordered_set<string>::iterator itr=dict.begin(); itr!=dict.end(); ++itr)
	{
		nodemap[*itr] = graph.size();
		graph.push_back(_NODE(*itr));
	}
	
	for(int index=0; index<graph.size(); ++index)
	{
		string str = graph[index].val;
		for(int i=0; i<str.size(); ++i)
		{
			char ch0 = str[i];
			for(char ch='a'; ch<='z'; ++ch)
			{
				// skip the same string
				if(ch == ch0)
					continue;
					
				str[i] = ch;
				int num = nodemap.count(str);
				if(num)
					graph[index].adj.push_back(nodemap[str]);
			}
			str[i] = ch0;
		}
	}
	int startindex = nodemap[start];
	int endindex = nodemap[end];
	
	queue<int> quenodes;
	quenodes.push(startindex);
	graph[startindex].distance = 0;
	while(!quenodes.empty())
	{
		int nodenum = quenodes.front();
		quenodes.pop();

		// when we find end index, all the nodes which has end as pre are visited already(becaue of BFS), we do not need to do anything more
		if(nodenum == endindex)
			break;
		
		for(int i=0; i<graph[nodenum].adj.size(); ++i)
		{
			int adjnode = graph[nodenum].adj[i];
			if(graph[adjnode].pre.size() == 0)
			{
				graph[adjnode].pre.push_back(nodenum); // 
				graph[adjnode].distance = graph[nodenum].distance + 1;
				quenodes.push(adjnode);
			}
			else if(graph[adjnode].distance == graph[nodenum].distance+1)
			{
				// NOTE: when graph[adjnode].pre is not NULL, the node adjnode was visited before from another path.
				// If the distance is the same here, we take it, or we skip it because it will not generate minimum path.
				graph[adjnode].pre.push_back(nodenum); // 
			}
		}
	}
	
	// From end search back to start
	vector<int> path;
	generateResult(startindex, endindex, graph, path, result);
	
	return result;
}


// 
void Solution::generateResult(int index, int endindex, vector<_NODE> &graph, vector<int>& path, vector<vector<string> > &result)
{	
	path.push_back(endindex);
	if(index == endindex)
	{
		vector<string> item;
		for(vector<int>::reverse_iterator ritr = path.rbegin(); ritr!=path.rend(); ++ritr)
			item.push_back(graph[*ritr].val);
		result.push_back(item);
	}
	else if(graph[index].distance < graph[endindex].distance)
	{
		for(int i=0; i<graph[endindex].pre.size(); ++i)
		{
			int next = graph[index].pre[i];
			generateResult(index, next, graph, path, result);
		}
	}
	path.pop_back();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct _NODE
{
	string val;
	vector<int> adj;
	vector<int> pre;
	int			distance;
	
	_NODE(string v) : val(v), distance(-1) {}
};

class Solution
{
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict);
private:
    pair<int, int> buildGraph(string start, string end, unordered_set<string> &dict, vector<_NODE> &graph);
	void bfsGraph(pair<int, int> ends, vector<_NODE> &graph);
	void generateResult(int index, int endindex, vector<_NODE> &graph, vector<int> &path, vector<vector<string> > &result);
};

vector<vector<string> > Solution::findLadders(string start, string end, unordered_set<string> &dict)
{
	vector<vector<string> > result;
	
	vector<_NODE> graph;
	
	// Generate the graph and return the start/end index
	pair<int, int> startendindex = buildGraph(start, end, dict, graph);
	if(startendindex.first<0 || startendindex.second<0)
		return result;
		
	bfsGraph(startendindex, graph);
	
	// From end search back to start
	vector<int> path;
	generateResult(startendindex.first, startendindex.second, graph, path, result);
	
	return result;
}

// build graph, start will be the first element, end will be the last one
// Time: O(n * L * 26)
// Space: O(n * L)
// return: the index for end string
pair<int, int> Solution::buildGraph(string start, string end, unordered_set<string> &dict, vector<_NODE> &graph)
{
	dict.insert(start);
	dict.insert(end);
	unordered_map<string, int> nodemap;
	
	for(unordered_set<string>::iterator itr=dict.begin(); itr!=dict.end(); ++itr)
	{
		nodemap[*itr] = graph.size();
		graph.push_back(_NODE(*itr));
	}
	
	for(int index=0; index<graph.size(); ++index)
	{
		string str = graph[index].val;
		for(int i=0; i<str.size(); ++i)
		{
			char ch0 = str[i];
			for(char ch='a'; ch<='z'; ++ch)
			{
				// skip the same string
				if(ch == ch0)
					continue;
					
				str[i] = ch;
				
				// skip the strings not in dict
				if(dict.find(str) == dict.end())
					continue;
					
				int num = nodemap.count(str);
				if(num)
					graph[index].adj.push_back(nodemap[str]);
			}
			str[i] = ch0;
		}
	}
	
	return pair<int, int>(nodemap[start], nodemap[end]);
}

// BFS to find the pre nodes for every node. Time: O(n * L)
// Space O(n)
void Solution::bfsGraph(pair<int, int> ends, vector<_NODE> &graph)
{
	int startindex = ends.first;
	int endindex = ends.second;
	
	queue<int> quenodes;
	quenodes.push(startindex);
	graph[startindex].distance = 0;
	while(!quenodes.empty())
	{
		int nodenum = quenodes.front();
		quenodes.pop();

		// when we find end index, all the nodes which has end as pre are visited already(becaue of BFS), we do not need to do anything more
		if(nodenum == endindex)
			break;
		
		for(int i=0; i<graph[nodenum].adj.size(); ++i)
		{
			int adjnode = graph[nodenum].adj[i];
			if(graph[adjnode].pre.size() == 0)
			{
				graph[adjnode].pre.push_back(nodenum); // 
				graph[adjnode].distance = graph[nodenum].distance + 1;
				quenodes.push(adjnode);
			}
			else if(graph[adjnode].distance == graph[nodenum].distance+1)
			{
				// NOTE: when graph[adjnode].pre is not NULL, the node adjnode was visited before from another path.
				// If the distance is the same here, we take it, or we skip it because it will not generate minimum path.
				graph[adjnode].pre.push_back(nodenum); // 
			}
		}
	}
}

// 
void Solution::generateResult(int index, int endindex, vector<_NODE> &graph, vector<int>& path, vector<vector<string> > &result)
{	
	path.push_back(endindex);
	// 0 is start index
	if(index == endindex)
	{
		vector<string> item;
		for(vector<int>::reverse_iterator ritr = path.rbegin(); ritr!=path.rend(); ++ritr)
			item.push_back(graph[*ritr].val);
		result.push_back(item);
	}
	else if(graph[index].distance < graph[endindex].distance)
	{
		for(int i=0; i<graph[endindex].pre.size(); ++i)
		{
			int next = graph[index].pre[i];
			generateResult(index, next, graph, path, result);
		}
	}
	path.pop_back();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

split the problem in three steps:

build the adjacency list
do a BFS to get a vector<vecto<int>> prev array. For example, prev[1] = [2, 3, 0] means we can go from (2 to 1) or (3 to 1) or (0 to 1).
construct the paths using prev.
A simple implement of the first step is O(n^2) and cannot pass the large test. So I use an O(nL26) method, where L is the length of each word. The idea is to try changing each letter in a word from 'a' to 'z', if that results to a valid word, we add the changed word to a adjacency list of the origin word.

Preforming a BFS is O(n) since we already has the adjacency list.

class Solution {
    vector<string> vdict;
    vector<vector<int> > adj;

    void build(unordered_set<string> &dict){
        int i, j;
        vdict.clear();
        unordered_map<string, int> ids;
        for(auto it=dict.begin(); it != dict.end(); it++){
            ids[*it] = vdict.size();
            vdict.push_back(*it);

        }
        adj.clear();
        adj.resize(vdict.size());
        for(int i = 0; i < vdict.size(); i++){
            string w = vdict[i];
            for(int j = 0; j < vdict[i].size(); j++){
                for(char c = 'a'; c <= 'z'; c++)
                    if(c != vdict[i][j]){
                        w[j] = c;
                        if(ids.count(w)){
                            adj[i].push_back(ids[w]);
                        }
                        w[j] = vdict[i][j];
                    }
            }
        }
    }

    void gen(int v1, int v2, vector<vector<int> >& prev, vector<int>& path, vector<vector<string> >&ans){
        path.push_back(v2);
        if(v2 == v1 and path.size() > 1){
            ans.push_back(vector<string>());
            for(auto rit = path.rbegin(); rit != path.rend(); rit++){
                ans.back().push_back(vdict[*rit]);
            }
        }else{
            int i;
            for(i = 0; i < prev[v2].size(); i++){
                gen(v1, prev[v2][i], prev, path, ans);
            }
        }
        path.pop_back();
    }
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        dict.insert(start);
        dict.insert(end);
        build(dict);
        queue<int> que;
        vector<vector<int> > prev(vdict.size());
        vector<int> distance(vdict.size());

        int v, v1, v2;
        for(v1 = 0; vdict[v1] != start; v1++);
        for(v2 = 0; vdict[v2] != end; v2++);
        for(int i = 0; i < adj[v1].size(); i++){
            v = adj[v1][i];
            que.push(v);
            prev[v].push_back(v1);
            distance[v] = 1;
        }
        while(not que.empty()){
            int v1 = que.front(); que.pop();
            if(v1 == v2) break;
            int d = distance[v1] + 1;
            for(int i = 0; i < adj[v1].size(); i++){
                v = adj[v1][i];
                if(prev[v].size() == 0){
                    prev[v].clear();
                    prev[v].push_back(v1);
                    distance[v] = d;
                    que.push(v);
                }else if(distance[v] == d){
                    prev[v].push_back(v1);
                }
            }
        }

        vector<vector<string> > ans;

        vector<int> path;
        gen(v1, v2, prev, path, ans);

        return ans;
    }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// BFS to calculate the length; DFS to find all the results
struct _TreeGraph
{
	string val;
	int	index;
	bool visited;
	vector<int> adjnodes;
	
	_TreeGraph(string v, int i): val(v), index(i), visited(false) {}
};
class Solution
{
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict);
	
private:
	void dfs(vector<string> item, int nmaxdepth, int depth, string end, vector<_TreeGraph>& graph, int indxe, vector<vector<string> > &result);
	void buildGraph(string start, string end, unordered_set<string> &dict, vector<_TreeGraph>& graph);
};
vector<vector<string> > Solution::findLadders(string start, string end, unordered_set<string> &dict)
{
	vector<vector<string> > result;
	unordered_set<string> dict2 =dict;
	
	int len = 1;
	queue<string> bfsqueue1;
	bfsqueue1.push(start);
	bool bFound = false;
	while(!bfsqueue1.empty() && !bFound)
	{
		unordered_set<string> dict3 =dict2;
		queue<string> bfsqueue2;
		while(!bfsqueue1.empty() && !bFound)
		{
			string val = bfsqueue1.front();
			bfsqueue1.pop();
			
			for(int j=0; j<val.size()&&!bFound; ++j)
			{
				char ch = val[j];
				for(char ch2='a'; ch2<='z'; ++ch2)
				{
					val[j] = ch2;
					if(dict3.find(val) != dict3.end())
					{
						dict2.erase(val);
						bfsqueue2.push(val);
						if(val == end)
						{
							bFound = true;
							break;
						}
					}
				}
				val[j] = ch;
			}
		}
		bfsqueue1 = bfsqueue2;
		if(!bfsqueue1.empty())
			++len;
	}
	
	if(!bFound)
		return result;
	
	vector<_TreeGraph> graph;
	buildGraph(start, end, dict, graph);
	// DFS
	//void dfs(vector<string> item, int nmaxdepth, int depth, string end, vector<_TreeGraph>& graph, int indxe, vector<vector<string> > &result);
	vector<string> item(1, start);
	dfs(item, len, 1, end, graph, 0, result);
	return result;
}

void Solution::buildGraph(string start, string end, unordered_set<string> &dict, vector<_TreeGraph>& graph)
{
	int index = 0;
	int n = dict.size();

	graph.push_back(_TreeGraph(start, index));
	++index;
	
	unordered_set<string>::iterator itr = dict.begin();
	while(itr != dict.end())
	{
		if(*itr!=start && *itr!=end)
		{
			graph.push_back(_TreeGraph(*itr, index));
			++index;
		}
		++itr;
	}
	graph.push_back(_TreeGraph(end, index));
	++index;
	
	// 
	for(int i=0; i<graph.size(); ++i)
		for(int j=i+1; j<graph.size(); ++j)
		{
			string &str1 = graph[i].val;
			string &str2 = graph[j].val;
			int ndist = 0;
			for(int k=0; k<str1.size(); ++k)
			{
				if(str1[k] != str2[k])
					++ndist;
			}
			
			if(ndist == 1)
			{
				graph[i].adjnodes.push_back(j);
				graph[j].adjnodes.push_back(i);
			}
		}
}

//	void dfs(vector<string> item, int nmaxdepth, int depth, string end, vector<_TreeGraph>& graph, int index, vector<vector<string> > &result);
void Solution::dfs(vector<string> item, int nmaxdepth, int depth, string end, vector<_TreeGraph>& graph, int index, vector<vector<string> > &result)
{
	if(depth >= nmaxdepth)
		return;
	
	vector<int> &adjnodes = graph[index].adjnodes;
	
	for(int j=0; j<adjnodes.size(); ++j)
	{
		int ind = graph[index].adjnodes[j];
		string &val = graph[ind].val;
		
		graph[ind].visited = true;
		
		vector<string> item2 = item;
		item2.push_back(val);
		if(depth+1 == nmaxdepth)
		{
			if(val == end)
				result.push_back(item2);
		}
		else
			dfs(item2, nmaxdepth, depth+1, end, graph, ind, result);
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BFS to calculate the length; DFS to find all the results
class Solution
{
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict);
	
private:
	void dfs(vector<string> item, int nmaxdepth, int depth, string end, unordered_set<string> &dict, vector<vector<string> > &result);
};
vector<vector<string> > Solution::findLadders(string start, string end, unordered_set<string> &dict)
{
	vector<vector<string> > result;
	unordered_set<string> dict2 =dict;
	
	int len = 1;
	queue<string> bfsqueue1;
	bfsqueue1.push(start);
	bool bFound = false;
	while(!bfsqueue1.empty() && !bFound)
	{
		unordered_set<string> dict3 =dict2;
		queue<string> bfsqueue2;
		while(!bfsqueue1.empty() && !bFound)
		{
			string val = bfsqueue1.front();
			bfsqueue1.pop();
			
			for(int j=0; j<val.size()&&!bFound; ++j)
			{
				char ch = val[j];
				for(char ch2='a'; ch2<='z'; ++ch2)
				{
					val[j] = ch2;
					if(dict3.find(val) != dict3.end())
					{
						dict2.erase(val);
						bfsqueue2.push(val);
						if(val == end)
						{
							bFound = true;
							break;
						}
					}
				}
				val[j] = ch;
			}
		}
		bfsqueue1 = bfsqueue2;
		if(!bfsqueue1.empty())
			++len;
	}
	
	if(!bFound)
		return result;
	
	// DFS
	//void dfs(vector<string> item, int nmaxdepth, int depth, string end, unordered_set<string> &dict, vector<vector<string> > &result);
	vector<string> item(1, start);
	dfs(item, len, 1, end, dict, result);
	return result;
}

void Solution::dfs(vector<string> item, int nmaxdepth, int depth, string end, unordered_set<string> &dict, vector<vector<string> > &result)
{
	string val = item[item.size()-1];
	if(depth >= nmaxdepth)
	{
		if(val == end)
			result.push_back(item);
		return;
	}
	for(int j=0; j<val.size(); ++j)
	{
		char ch = val[j];
		for(char ch2='a'; ch2<='z'; ++ch2)
		{
			val[j] = ch2;
			if(dict.find(val) != dict.end())
			{
				vector<string> item2 = item;
				item2.push_back(val);
				if(depth+1 == nmaxdepth)
				{
					if(val == end)
						result.push_back(item2);
				}
				else
					dfs(item2, nmaxdepth, depth+1, end, dict, result);
			}
		}
		val[j] = ch;
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Solution {
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict);
	int	distance(const string& str1, const string &str2);
};

int	Solution::distance(const string& str1, const string &str2)
{
	if(str1.size() != str2.size())
		return 1000;
	
	int len = 0;
	for(int i=0; i<str1.size(); ++i)
		if(str1[i] != str2[i])
			++len;
			
	return len;
}

 
vector<vector<string> > Solution::findLadders(string start, string end, unordered_set<string> &dict)
{
	vector<vector<string> > result;
	vector<string> dictstrings(dict.begin(), dict.end());

	bool bFound =false;
	unordered_set<string> used;
	result.push_back(vector<string>(1, start));
	used.insert(start);
	while(!bFound)
	{
		// Do BFS
		vector<vector<string> > tmpresult;
		unordered_set<string> tmpUsed = used;
		bool bAddedNew = false;
		for(int i=0; i<result.size(); ++i)
		{
			vector<string> node = result[i];
			string val = node[node.size()-1];
#if 1
			for(int j=0; j<val.size(); ++j)
			{
				char ch = val[j];
				for(char ch2='a'; ch2<='z'; ++ch2)
				{
					val[j] = ch2;
					if(dict.find(val)!=dict.end() && used.find(val)==used.end())
					{
						vector<string> node2 = node;
						node2.push_back(val);
						tmpresult.push_back(node2);
						tmpUsed.insert(val);
						bAddedNew = true;
						if(val == end)
							bFound = true;
					}
				}
				val[j] = ch;
			}
#else
				for(int k=0; k<dictstrings.size(); ++k)
					if(used.find(dictstrings[k])==used.end() && distance(val, dictstrings[k]==1))
					{
						string val2 = dictstrings[k];
						vector<string> node2 = node;
						node2.push_back(val2);
						tmpresult.push_back(node2);
						tmpUsed.insert(val2);
						bAddedNew = true;
						if(val2 == end)
							bFound = true;
					}
#endif
		}
		
		used = tmpUsed;
		
		if(bFound)
		{
			// remove all useless lines
			vector<vector<string> >::iterator itr = tmpresult.begin();
			while(itr != tmpresult.end())
			{
				vector<string> &node = *itr;
				if(node[node.size()-1] != end)
					itr = tmpresult.erase(itr);
				else
					++itr;
			}
		}
		else if(!bAddedNew)
		{
			tmpresult.clear();
			result = tmpresult;
			break;
		}
		
		result = tmpresult;
	}
	
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BFS only
class Solution {
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict);
};
vector<vector<string> > Solution::findLadders(string start, string end, unordered_set<string> &dict)
{
	vector<vector<string> > result;
	vector<string> dictstrings(dict.begin(), dict.end());

	bool bFound =false;
	result.push_back(vector<string>(1, start));
	used.insert(start);
	while(!bFound)
	{
		// Do BFS
		vector<vector<string> > tmpresult;
		bool bAddedNew = false;
		unordered_set<string> used;
		for(int i=0; i<result.size(); ++i)
		{
			vector<string> node = result[i];
			string val = node[node.size()-1];
			for(int j=0; j<val.size(); ++j)
			{
				char ch = val[j];
				for(char ch2='a'; ch2<='z'; ++ch2)
				{
					val[j] = ch2;
					if(dict.find(val)!=dict.end())
					{
						vector<string> node2 = node;
						node2.push_back(val);
						tmpresult.push_back(node2);
						used.insert(val);
						bAddedNew = true;
						if(val == end)
							bFound = true;
					}
				}
				val[j] = ch;
			}
		}
		
		// 
		while(!used.empty())
		{
			dict.erase(*used.begin());
			used.erase(used.begin());
		}
		
		if(bFound)
		{
			// remove all useless lines
			vector<vector<string> >::iterator itr = tmpresult.begin();
			while(itr != tmpresult.end())
			{
				vector<string> &node = *itr;
				if(node[node.size()-1] != end)
					itr = tmpresult.erase(itr);
				else
					++itr;
			}
		}
		else if(!bAddedNew)
		{
			tmpresult.clear();
			result = tmpresult;
			break;
		}
		
		result = tmpresult;
	}
	
	return result;
}
 

 
///////////////////////////////////////////////////////////////////////////////////////////////////////

struct GraphNode
{
	string		m_str; // the string of segment[i..j]
	bool		m_bVisited;
	GraphNode	*m_pBFSParent;
	int			m_nHeight;
	
	vector<GraphNode *>	m_AdjecentNodes;
	GraphNode(string str)
		:m_str(str), m_bVisited(false), m_pBFSParent(NULL)
	{
	}
	~GraphNode()
	{
	}
};


class Solution
{
public:
	 vector<vector<string> >	findLadders(string start, string end, unordered_set<string> &dict);
	 void						printResult(vector<vector<string> >& result);
	 
 private:
	void			generateGraph(string start, string end, unordered_set<string> &dict, vector<GraphNode *> &graph);
	void			BFSTree(string start, string end, vector<GraphNode *> &tree, vector<vector<string> > &result);
	deque<string>	generateStringList(GraphNode *pNode);
	bool			canConnect(GraphNode *n1, GraphNode*n2);
	GraphNode *		findNode(vector<GraphNode *> &graph, string str);
};

// dist(start[i..j], end[i..j]) = min{dist(start[i..k-1]+end[k+1..j] + start[k]==end[k]?0:1 for k=i+1,..,j-1 and start[i..k-1]end[k]start[k+1..j]is in directionary)}
void Solution::generateGraph(string start, string end, unordered_set<string> &dict, vector<GraphNode *> &graph)
{

	GraphNode *pStartNode = new GraphNode(start);
	GraphNode *pEndNode = new GraphNode(end);

	graph.push_back(pStartNode);
	unordered_set<string>::const_iterator itrBegin = dict.begin();
	unordered_set<string>::const_iterator itrEnd = dict.end();
	while(itrBegin != itrEnd)
	{
		string str = *itrBegin;
		if(str!=start && str!=end)
		{
			GraphNode *pNode = new GraphNode(str);
			graph.push_back(pNode);
		}
		++itrBegin;
	}
	graph.push_back(pEndNode);
	
	// add directed edge
	vector<GraphNode *>::iterator itrGraphBegin1 = graph.begin();
	vector<GraphNode *>::iterator itrGraphEnd1 = graph.end();
	while(itrGraphBegin1 != itrGraphEnd1)
	{
		GraphNode *pNode = *itrGraphBegin1;
		vector<GraphNode *>::iterator itrGraphBegin2;
		++itrGraphBegin1;
		for(itrGraphBegin2=graph.begin(); itrGraphBegin2!=graph.end(); ++itrGraphBegin2)
		{
			GraphNode *pNode2 = *itrGraphBegin2;
			if(pNode!=pNode2 && canConnect(pNode, pNode2) )
				pNode->m_AdjecentNodes.push_back(pNode2);
		}
	}
}

bool Solution::canConnect(GraphNode *n1, GraphNode*n2)
{
	string str1 = n1->m_str;
	string str2 = n2->m_str;
	int nCount = 0;
	for(int i=0; i<str1.size(); i++)
		if(str1[i] != str2[i])
			++nCount;
			
	return nCount==1;
}

GraphNode *Solution::findNode(vector<GraphNode *> &graph, string str)
{
	for(int i=0; i<graph.size(); i++)
		if(graph[i]->m_str == str)
			return graph[i];
	return NULL;
}

vector<vector<string> > Solution::findLadders(string start, string end, unordered_set<string> &dict)
{
	vector<GraphNode *> tree;
	generateGraph(start, end, dict, tree);
	
	// BFS the tree
	vector<vector<string> > result;
	BFSTree(start, end, tree, result);
	
	return result;
}


void Solution::BFSTree(string start, string end, vector<GraphNode *> &graph, vector<vector<string> > &result)
{
	GraphNode *pNodeStart = findNode(graph, start);
	GraphNode *pNodeEnd = findNode(graph, end);
	if(!pNodeStart || !pNodeEnd)
		return;
		
	if(pNodeStart == pNodeEnd)
	{
		vector<string> line;
		line.push_back(end);
		result.push_back(line);
		return;
	}
	
	queue<GraphNode *> queueNodes;
	
	int nMinHeight = graph.size() + 100;
	for(int i=0; i<graph.size(); i++)
		graph[i]->m_nHeight = nMinHeight; // all are INFINITE height

	pNodeStart->m_bVisited = true;
	pNodeStart->m_nHeight = 0;
	queueNodes.push(pNodeStart);
	
	while(!queueNodes.empty())
	{
		GraphNode *pNode = queueNodes.front();
		queueNodes.pop();
		
		for(int i=0; i<pNode->m_AdjecentNodes.size(); i++)
		{
			GraphNode *pAdjNode = pNode->m_AdjecentNodes[i];
			if(!pAdjNode->m_bVisited)
			{
				pAdjNode->m_pBFSParent = pNode;
				pAdjNode->m_nHeight = pNode->m_nHeight + 1;
				pAdjNode->m_bVisited = true;
				queueNodes.push(pAdjNode);
			}
		}
	}
	
	nMinHeight = pNodeEnd->m_nHeight;
	
	for(int i=0; i<graph.size(); i++)
	{
		GraphNode *pNode = graph[i];
		if(pNode->m_nHeight<nMinHeight && canConnect(pNode, pNodeEnd))
		{
			deque<string> res = generateStringList(pNode);
			res.push_back(end);
			vector<string> finalRes;
			finalRes.resize(res.size());
			copy(res.begin(), res.end(), finalRes.begin());
			result.push_back(finalRes);
		}
	}
}

deque<string> Solution::generateStringList(GraphNode *pNode)
{
	deque<string> res;
	while(pNode)
	{
		res.push_front(pNode->m_str);
		pNode = pNode->m_pBFSParent;
	}
	
	return res;
}


void Solution::printResult(vector<vector<string> >& result)
{
	for(int i=0; i<result.size(); i++)
	{
		for(int j=0; j<result[i].size(); j++)
			cout << "\"" << result[i][j] << "\"  ";
		cout << "\n";
	}
}

