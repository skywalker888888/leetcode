/**
		Given a digit string, return all possible letter combinations that the number could represent.
		A mapping of digit to letters (just like on the telephone buttons) is given below.
		Input:Digit string "23"
		Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
		Note:
		Although the above answer is in lexicographical order, your answer could be in any order you want.
*/
// pass 3
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<vector<char> > valueToCharMaps(10);
		
		for(int i=0; i<10; ++i) {
			int len = 0;
			char st = 'a';
			switch(i) {
			case 0:
			case 1: len = 0; break;
			case 2: len = 3; st = 'a'; break;
			case 3: len = 3; st = 'd'; break;
			case 4: len = 3; st = 'g'; break;
			case 5: len = 3; st = 'j'; break;
			case 6: len = 3; st = 'm'; break;
			case 7: len = 4; st = 'p'; break;
			case 8: len = 3; st = 't'; break;
			case 9: len = 4; st = 'w'; break;
			}
			
			for(int j=0; j<len; ++j)
				valueToCharMaps[i].push_back(st+j);
		}
		
		vector<vector<string> > M(2);
		M[0].push_back(string());
		int flag = 1;
		for(int i=0; i<digits.size(); ++i) {
			M[flag].clear();
			for(int j=0; j<M[!flag].size(); ++j) {
				string str = M[!flag][j];
				for(int k=0; k<valueToCharMaps[digits[i]-'0'].size(); ++k) {
					char ch = valueToCharMaps[digits[i]-'0'][k];
					string item = str;
					item.push_back(ch);
					M[flag].push_back(item);
				}
			}
			flag = !flag;
		}
		return M[!flag];
    }
};






































// pass 2
class Solution {
public:
    vector<string> letterCombinations(string digits) {
    	vector<vector<char> > valueToCharMaps(10);
		
		for(int i=0; i<10; ++i) {
			int len = 0;
			char st = 'a';
			switch(i) {
			case 0:
			case 1: len = 0; break;
			case 2: len = 3; st = 'a'; break;
			case 3: len = 3; st = 'd'; break;
			case 4: len = 3; st = 'g'; break;
			case 5: len = 3; st = 'j'; break;
			case 6: len = 3; st = 'm'; break;
			case 7: len = 4; st = 'p'; break;
			case 8: len = 3; st = 't'; break;
			case 9: len = 4; st = 'w'; break;
			}
			
			for(int j=0; j<len; ++j)
				valueToCharMaps[i].push_back(st+j);
		}
		
		// 
		vector<string> result;
		int n = digits.size();
		if(!n) {
			result.push_back("");
			return result;
		}
		
		vector<int> digvalues(n);
		for(int i=0; i<n; ++i)
			digvalues[i] = digits[i] - '0';
		
		vector<int> digcombinations(n, 0);
		
		while(digcombinations[0] < valueToCharMaps[digvalues[0]].size()) {
			// add one item
			string item;
			for(int i=0; i<n; ++i) {
				char ch = valueToCharMaps[digvalues[i]][digcombinations[i]];
				item.push_back(ch);
			}
			
			result.push_back(item);
			
			++digcombinations[n-1];
			for(int j=n-1; j>0; --j)
				if(digcombinations[j] >= valueToCharMaps[digvalues[j]].size()) {
					digcombinations[j] = 0;
					++digcombinations[j-1];
				} else
					break;
		}
		return result;
    }
};






































class Solution {
public:
	vector<string> letterCombinations(string digits) {
		// digchmap[' '] = 0;
		vector<vector<char> > phonekeys(10); // 0 ~ 9
		for(int i=0; i<10; ++i) {
			int len = 0;
			char st = 'a';
			switch(i) {
			case 0: break;
			case 1: break;
			case 2:
				len = 3; st = 'a'; break;
			case 3:
				len = 3; st = 'd'; break;
			case 4:
				len = 3; st = 'g'; break;
			case 5:
				len = 3; st = 'j'; break;
			case 6:
				len = 3; st = 'm'; break;
				break;
			case 7:
				len = 4; st = 'p'; break;
				break;
			case 8:
				len = 3; st = 't'; break;
				break;
			case 9:
				len = 4; st = 'w'; break;
				break;
			}
			for(int j=0; j<len; ++j)
				phonekeys[i].push_back(st + j);
		}
		
		vector<string> result;
		int n = digits.size();
		if(!n) {
			result.push_back("");
			return result;
		}
		vector<int> numdigs(n);
		for(int i=0; i<n; ++i) {
			numdigs[i] = digits[i] - '0';
			if(numdigs[i]<2 || numdigs[i]>9) {
				result.push_back("");
				return result;
			}
		}
		
		vector<int> digcharindices(n, 0);

		while(digcharindices[0] < phonekeys[numdigs[0]].size()) {
			// increase the last element index
			string item;
			for(int i=0; i<n; ++i) {
				int &digval = numdigs[i];
				int &ind = digcharindices[i];
				item.push_back(phonekeys[digval][ind]);
			}
			result.push_back(item);
			++digcharindices[n-1];
			for(int j=n-1; j>0; --j) {
				int &digval = numdigs[j];
				int &ind = digcharindices[j];
				int maxindex = phonekeys[digval].size();
				if(ind >= maxindex) {
					++digcharindices[j-1];
					for(int k=j; k<n; ++k)
						digcharindices[k] = 0;
				}
				else
					break;
			}
		}
		return result;
	}
};




