/**
		Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

		For example,
		S = "ADOBECODEBANC"
		T = "ABC"
		Minimum window is "BANC".

		Note:
		If there is no such window in S that covers all characters in T, return the emtpy string "".

		If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
*/
class Solution {
public:
    string minWindow(string S, string T) {
    	unordered_map<char, int> seed;
		unordered_map<char, int> matched;
		
		int m = S.size();
		int n = T.size();
		if(m < n)
			return "";
		for(int i=0; i<T.size(); ++i)
			++seed[T[i]];
			
		int result_i = 0;
		int result_j = m;
		
		int count = 0;
		int i = 0;
		for(int j=0; j<S.size(); ++j) {
			if(seed.find(S[j]) != seed.end()) {
				++matched[S[j]];
				if(matched[S[j]] == seed[S[j]])
					++count;
				while(i<m) {
					if(seed.find(S[i]) != seed.end())
						if(matched[S[i]]<=seed[S[i]])
							break;
						else
							--matched[S[i]];
					++i;
				}
				
				if(count == seed.size()) {
					if(result_j-result_i > j-i) {
						result_j = j;
						result_i = i;
					}
				}
			}
		}
		if(result_j >= m)
			return "";
		return S.substr(result_i, result_j-result_i+1);
    }
};









































*/
		See: http://leetcode.com/2010/11/finding-minimum-window-in-s-which.html
		
		Analysis:
		Use two pointers, begin and end, to indicate a substring. 
		For each character, we record the number of appearance in this substring
		We have a bool array to indicate if a character exists in T.
		We advance end pointer, when there is a character in T found, we check if we need to advance the begin pointer to the right.
*/
// Pass 2
class Solution {
public:
    string minWindow(string S, string T) {
		int nNumOfPossibleCharacters = 256;
	
		int totChars = 0;
		// How many numbers appears in T for each character
		vector<int> totalCount(nNumOfPossibleCharacters, 0);
		for(int i=0; i<T.size(); ++i){
			if(!totalCount[T[i]])
				++totChars;
			++totalCount[T[i]];
		}
		
		vector<int> charCount(nNumOfPossibleCharacters, 0);
		
		int minInd = -1;
		int maxInd;

		int start = 0;

		int count = 0;
		for(int end=0; end<S.size(); ++end) {
			char ch = S[end];
			if(!totalCount[ch])
				continue;
			
			// if find a character which exists in T
			++charCount[ch];
			if(charCount[ch] == totalCount[ch])
				++count;
				
			// try to see if we can shrink the sub string
			for(int i=start; i<=end; ++i) {
				char ch2 = S[i];
				// the char does not exists in T, skip
				if(!totalCount[ch2])
					continue;
				
				if(charCount[ch2] <= totalCount[ch2]) {
					start = i;
					break;
				}
				
				// skip this character
				--charCount[ch2];
			}
			
			if(count==totChars && (maxInd-minInd+1>end-start+1 || minInd<0)){
				maxInd = end;
				minInd = start;
			}
		}
		
		string result;
		if(minInd >= 0)
			result = S.substr(minInd, maxInd-minInd+1);
		
		return result;
    }
};



































class Solution
{
public:
	string minWindow(string S, string T)
	{
		if(T.empty())
			return string();
			
		if(S.size() < T.size())
			return string();
			
		int nNumOfPossibleCharacters = 256;
		
		// how many number appears in T
		vector<int> charExistsInT(nNumOfPossibleCharacters, 0);
		for(int i=0; i<T.size(); ++i) {
			int nCh = T[i];
			++charExistsInT[nCh];
		}

		// how many times a char appears in current sub string
		vector<int> charNumberInSubstring(nNumOfPossibleCharacters, 0);
		
		int nBegin = 0;
		int nEnd = 0;
		int nCount = 0;
		
		int nMinSubStringLen = S.size() + 1;
		string minSubStr;
		
		while(nEnd < S.size()) {
			int nChEnd = S[nEnd];
			if(charExistsInT[nChEnd]) {
				// !!!! when there is no enough appreance in the substring, we encrease the nCount
				if(charNumberInSubstring[nChEnd] < charExistsInT[nChEnd])
					++nCount;
					
				++charNumberInSubstring[nChEnd];

				// try to move begin pointer to right side as long as possible
				int nChBegin = S[nBegin];
				while(charExistsInT[nChBegin]&&charNumberInSubstring[nChBegin]>charExistsInT[nChBegin] || !charExistsInT[nChBegin]) {
					if(charExistsInT[nChBegin])
						--charNumberInSubstring[nChBegin];
					++nBegin;
					nChBegin = S[nBegin];
				}
				if(nCount == T.size()) {
					if(nEnd-nBegin+1 < nMinSubStringLen) {
						nMinSubStringLen = nEnd-nBegin+1;
						minSubStr = S.substr(nBegin, nMinSubStringLen);
					}
				}
			}
			++nEnd;
		}
		
		return minSubStr;
	}
};



int main(int argc, char **argv)
{
	Solution sol;
	string S = "aa";
	string T = "aa";
	string str = sol.minWindow(S, T);
	cout << "output: " << str << "\n";
}
