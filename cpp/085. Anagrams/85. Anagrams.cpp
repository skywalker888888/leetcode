/**
		Given an array of strings, return all groups of strings that are anagrams.
		Note: All inputs will be in lower-case.
		
		anagrams: a word and the other word contains the same characters
*/
// pass 3
class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
		unordered_map<string, vector<string> > M;
		for(int i=0; i<strs.size(); ++i) {
			string str = strs[i];
			sort(str.begin(), str.end());
			M[str].push_back(strs[i]);
		}
		vector<string> result;
		unordered_map<string, vector<string> >::iterator itr = M.begin();
		while(itr != M.end()) {
			if(itr->second.size() > 1)
				result.insert(result.end(), itr->second.begin(), itr->second.end());
			++itr;
		}
		return result;
    }
};











































// pass 
class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
		unordered_map<string, vector<string> > mapGroups;
		for(int i=0; i<strs.size(); ++i) {
			string str = strs[i];
			sort(str.begin(), str.end());
			mapGroups[str].push_back(strs[i]);
		}
		
		vector<string> result;
		for(unordered_map<string, vector<string> >::iterator itr = mapGroups.begin(); itr!=mapGroups.end(); ++itr) {
			const pair<string, vector<string> > &val = *itr;
			if(val.second.size()>1)
				result.insert(result.end(), val.second.begin(), val.second.end());
		}
		
		return result;
    }
};









































bool isLess(string s1, string s2)
{
	string ss1 = s1;
	sort(ss1.begin(), ss1.end());
	
	string ss2 = s2;
	sort(ss2.begin(), ss2.end());
	
	return ss1 < ss2;
}

class Solution {
public:
	vector<string> anagrams(vector<string> &strs) {
		vector<string> result;
		int n = strs.size();
		if(!n)
			return result;
			
		map<string, vector<string> > groups;
		vector<string>::iterator itr = strs.begin();
		while(itr != strs.end()) {
			string keystr = *itr;
			sort(keystr.begin(), keystr.end());
			
			groups[keystr].push_back(*itr);
			++itr;
		}

		map<string, vector<string> >::const_iterator itrmap = groups.begin();
		while(itrmap != groups.end())
		{
			const pair<string, vector<string> > &item = *itrmap;
			const vector<string> &grp = item.second;
			if(grp.size() > 1)
				result.insert(result.end(), grp.begin(), grp.end());
			++itrmap;
		}
		
		return result;
	}
};


class Solution {
public:
	vector<string> anagrams(vector<string> &strs) {
		vector<string> result;
		int n = strs.size();
		if(!n)
			return result;
		sort(strs.begin(), strs.end(), isLess);
		
		vector<string>::iterator itr = strs.begin();
		while(itr != strs.end()) {
			vector<string> res;
			string str = *itr;
			res.push_back(str);
			itr = strs.erase(itr);
			while(itr != strs.end()) {
				string str2 = *itr;
				if(areAnagrams(str, str2)) {
					res.push_back(str2);
					itr = strs.erase(itr);
				} else {
					break;
				}
			}
			if(res.size() > 1)
				result.insert(result.end(), res.begin(), res.end());
			itr = strs.begin();
		}
		return result;
	}
};

class Solution {
	vector<string> anagrams(vector<string> &strs) {
		vector<string> result;
		int n = strs.size();
		if(!n)
			return result;

		vector<string>::iterator itr = strs.begin();
		while(itr != strs.end()) {
			vector<string> res;
			string str = *itr;
			res.push_back(str);
			itr = strs.erase(itr);
			while(itr != strs.end()) {
				string str2 = *itr;
				if(areAnagrams(str, str2)) {
					res.push_back(str2);
					itr = strs.erase(itr);
				} else {
					++itr;
				}
			}
			if(res.size() > 1)
				result.insert(result.end(), res.begin(), res.end());
			itr = strs.begin();
		}
		return result;
	}
	bool areAnagrams(const string &s1, const string& s2)
	{
		if(s1.size() != s2.size())
			return false;
			
		string ss1 = s1;
		sort(ss1.begin(), ss1.end());
		
		string ss2 = s2;
		sort(ss2.begin(), ss2.end());
		
		return ss1 == ss2;
	}
};





