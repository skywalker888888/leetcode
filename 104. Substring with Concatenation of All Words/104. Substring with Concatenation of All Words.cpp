/**
		You are given a string, S, and a list of words, L, that are all of the same length. Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.

		For example, given:
		S: "barfoothefoobarman"
		L: ["foo", "bar"]

		You should return the indices: [0,9].
		(order does not matter).
*/
// pass 3
class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        int n = L.size();
		if(!n)
			return vector<int>();
		int k = L[0].size();
		if(!k)
			return vector<int>();
		
		int m = S.size();
		
		if(m < n*k)
			return vector<int>();
			
		unordered_map<string, int> word_count;
		for(int i=0; i<n; ++i)
			++word_count[L[i]];
		
		vector<int> result;
		for(int i=0; i<=m-n*k; ++i) {
			unordered_map<string, int> word_count_tmp;
			int j=0;
			for(; j<n; ++j) {
				string str = S.substr(i+j*k, k);
				if(word_count.find(str) == word_count.end()) {
					break;
				}
				++word_count_tmp[str];
				if(word_count_tmp[str] > word_count[str])
					break;
			}
			if(j == n) 
				result.push_back(i);
		}
		return result;
    }
};

































// pass 2
class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
		// create a map from S's position to L's position
		vector<int> result;
		int n = S.size();
		int m = L.size();
		if(!n || !m || !L[0].size())
			return result;
		int k = L[0].size();
		
		unordered_map<string, int> wordcount;
		for(int i=0; i<m; ++i)
			++wordcount[L[i]];
		
		// check
		for(int i=0; i<=n-m*k; ++i) {
			unordered_map<string, int> wordAppears;
			int j = i;
			for(; j<i+m*k; j+=k) {
				string str = S.substr(j, k);
				if(wordcount.find(str) == wordcount.end())
					break;
				++wordAppears[str];
				if(wordAppears[str] > wordcount[str])
					break;
			}
			if(j == i+m*k)
				result.push_back(i);
		}
		
		return result;
    }
};









































class Solution {
public:

    /**
		Maintain a map<string, int> to record the number of each string in L.
		Then slide the N*M length string, the length is the total length of the strings in L, in S from left to right, we examin all the N length substrings to check the number of apperance in the substring.
		So we maintain a map<string, int>. 
		
		At anytime, we found a string in the substring exceeded the total string number in L, the checking fails.
	*/
	vector<int> findSubstring(string S, vector<string> &L) {
		vector<int> result;
		int N = L.size();
		int len = S.size();
		if(!len || !N || !L[0].size())
			return result;
		int M = L[0].size();
		
		map<string, int> words; // maintain the number of appearance of each string in L
		for(int i=0; i<N; ++i)
			++words[L[i]]; // NOTE: words[string] will automatically add one item if no key exists yet
		
		for(int i=0; i<=len-M*N; ++i) {
			map<string, int> wordsAppears;
			int j = i;
			for(; j<i+N*M; j+=M) {
				string str = S.substr(j, M);
				if(words.find(str) == words.end())  
					break;  
				++wordsAppears[str];
				if(wordsAppears[str] > words[str])
					break;
			}
			
			if(j == i+N*M)
				result.push_back(i);
		}
		
		return result;
	}
};


class Solution {
public:
	vector<int> findSubstring(string S, vector<string> &L)
	{
		vector<int> result;
		if(!S.size() || !L.size() || !L[0].size() || S.size()<L.size() * L[0].size())
			return result;
			
		int m = S.size();
		int n = L.size();
		int len = L[0].size();
		
		vector<bool> selection(n, false);
		vector<vector<int> > positions(n); // for each element in L, record the ordered position list

		for(int i=0; i<n; ++i)
		{
			generatePositionList(S, L[i], positions[i]);
			if(!positions[i].size())
				return result;
		}
			
		for(int i=0; i<=m-n*len; ++i)
		{
			if(hasSolution(i, len, selection, positions))
				result.push_back(i);
		}
		
		return result;
	}

	bool hasSolution(int pos, int len, vector<bool> &selection, const vector<vector<int> >& positions)
	{
		int n = selection.size();
		if(find(selection.begin(), selection.end(), false) == selection.end())
			return true;
			
		for(int i=0; i<n; ++i)
		{
			if(selection[i])
				continue;
			bool bPosExists = positionExists(pos, positions[i]);
			if(!bPosExists)
				continue;
				
			selection[i] = true;
			if(find(selection.begin(), selection.end(), false) == selection.end())
			{
				selection[i] = false;
				return true;
			}
			
			bool hasSol = hasSolution(pos+len, len, selection, positions);
			selection[i] = false;
			if(hasSol)
				return true;
		}

		return false;
	}
	void generatePositionList(const string& S, const string &str, vector<int> &pos)
	{
		int len = str.size();
		for(int i=0; i<=S.size()-len; ++i)
		{
			bool bInclude = true;
			for(int j=0; j<len; ++j)
				if(str[j] != S[i+j])
				{
					bInclude = false;
					break;
				}
			if(bInclude)
				pos.push_back(i);
		}
	}
	bool positionExists(int pos, const vector<int>& poslist)
	{
		int s = 0;
		int e = poslist.size() - 1;
		while(s <= e)
		{
			int m = (s + e) / 2;
			if(pos == poslist[m])
				return true;
			else if(pos > poslist[m])
				s = m + 1;
			else
				e = m - 1;
		}
		return false;
	}
};

