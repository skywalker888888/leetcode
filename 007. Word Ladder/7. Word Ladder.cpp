/**
	Given two words (start and end), and a dictionary, find the length of shortest transformation sequence from start to end, such that:

	Only one letter can be changed at a time
	Each intermediate word must exist in the dictionary
	For example,

	Given:
	start = "hit"
	end = "cog"
	dict = ["hot","dot","dog","lot","log"]
	As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
	return its length 5.

	Note:
	Return 0 if there is no such transformation sequence.
	All words have the same length.
	All words contain only lowercase alphabetic characters.
*/
// pass 3
class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
    	queue<pair<string, int> > queWords;
		queWords.push(pair<string, int>(start, 1));
		while(!queWords.empty()) {
			pair<string, int> word = queWords.front();
            queWords.pop();
			if(word.first == end)
				return word.second;
			else {
				string w = word.first;
				for(int i=0; i<w.size(); ++i) {
					char ch = w[i];
					
					for(char c='a'; c<='z'; ++c) {
						w[i] = c;
						if(dict.find(w)!=dict.end() || w==end) {
							dict.erase(w);
							queWords.push(pair<string, int>(w, word.second+1));
						}
					}
					w[i] = ch;
				}
			}
		}
		return 0;
    }
};




































// pass 2
class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
		vector<queue<pair<string, int> > > queues(2);
		queues[0].push(pair<string, int>(start, 1));
		int flag = 1;
		while(!queues[!flag].empty()) {
			pair<string, int> tp = queues[!flag].front();
			if(tp.first == end)
				return tp.second;
			queues[!flag].pop();
			for(int i=0; i<tp.first.size(); ++i) {
				char ch = tp.first[i];
				for(char j='a'; j<='z'; ++j) {
					tp.first[i] = j;
					if(ch!=j && dict.find(tp.first) != dict.end()) {
						queues[flag].push(pair<string, int>(tp.first, tp.second+1));
						dict.erase(tp.first);
					}
				}
				tp.first[i] = ch;
			}
			if(queues[!flag].empty())
				flag = !flag;
		}
		return 0;
	}
};

	
class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
		queue<pair<string, int> > queNodes;
		queNodes.push(pair<string, int>(start, 1));

		unordered_set<string> searchedStrings;
		searchedStrings.insert(start);
		
		while(!queNodes.empty()) {
			pair<string, int> tp = queNodes.front();
			if(tp.first == end)
				return tp.second;
			queNodes.pop();
			for(int i=0; i<tp.first.size(); ++i) {
				char ch = tp.first[i];
				for(char j='a'; j<='z'; ++j) {
					tp.first[i] = j;
					if(ch!=j && dict.find(tp.first) != dict.end() && searchedStrings.find(tp.first)==searchedStrings.end()) {
						queNodes.push(pair<string, int>(tp.first, tp.second+1));
						searchedStrings.insert(tp.first);
					}
				}
				tp.first[i] = ch;
			}
		}
		return 0;
	}
};


























class Solution {
public:
	int ladderLength(string start, string end, unordered_set<string> &dict) {
		int len = 1;
		queue<string> bfsqueue1;
		bfsqueue1.push(start);
		bool bFound = false;
		
		while(!bfsqueue1.empty() && !bFound) {
			queue<string> bfsqueue2;
			while(!bfsqueue1.empty() && !bFound) {
				string val = bfsqueue1.front();
				bfsqueue1.pop();
				
				for(int j=0; j<val.size()&&!bFound; ++j) {
					char ch = val[j];
					for(char ch2='a'; ch2<='z'; ++ch2) {
						val[j] = ch2;
						if(dict.find(val) != dict.end()) {
							dict.erase(val);
							bfsqueue2.push(val);
							if(val == end) {
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
			return 0;
		
		return len;
	}
};

