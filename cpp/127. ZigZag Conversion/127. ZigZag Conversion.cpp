/**
		The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

		P   A   H   N
		A P L S I I G
		Y   I   R
		And then read line by line: "PAHNAPLSIIGYIR"
		Write the code that will take a string and make this conversion given a number of rows:

		string convert(string text, int nRows);
		convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
*/
// pass 3
class Solution {
public:
    string convert(string s, int nRows) {
    	int n = s.size();
		if(n<2 || nRows < 2)
			return s;
		
		string result;
		
		int numPerGroup = nRows + nRows-2;
		
		int nGroupNum = n/numPerGroup + (n%numPerGroup?1:0);
		for(int i=0; i<nRows; ++i) {
			for(int j=0; j<nGroupNum; ++j) {
				int topleft = j * numPerGroup;
				if(i == 0) {
					result.push_back(s[topleft]);
				} else {
					if(topleft+i < n )
						result.push_back(s[topleft+i]);
					if(i<nRows-1 && topleft+nRows-1+(nRows-1-i)<n)
						result.push_back(s[topleft+nRows-1+(nRows-1-i)]);
				}
			}
		}
		return result;
    }
};


























// pass 2
class Solution {
public:
    string convert(string s, int nRows) {
		string result;
		int n = s.size();
		if(!n || !nRows)
			return result;
		if(nRows == 1)
			return s;
		int numPerGroup = nRows + nRows -2;
		
		int numberOfGroups = (n%nRows)? (n/nRows+1):(n/nRows);
		for(int i=0; i<nRows; ++i) 
			for(int j=0; j<numberOfGroups; ++j) {
				int nFirst = numPerGroup * j;
				if(nFirst + i < n)
					result.push_back(s[nFirst + i]);
				if(i>0 && i<nRows-1) {
					int nIndex = nFirst + nRows-1 + (nRows-1-i);
					if(nIndex < n)
						result.push_back(s[nIndex]);
				}
			}
		return result;
    }
};








































class Solution {
public:
	string convert(string s, int nRows) {
		int n = s.size();
		if(nRows < 2)
			return s;
		int numPerCub = (nRows - 1) * 2;
		int nCubRow = nRows - 1;
		//int totalCubLine = n/numPerCub * nCubRow + (n-n/numPerCub * nCubRow <=nRows)?1: (n-n/numPerCub * nCubRow-nRows+1);
		int nCubNum = n/numPerCub + (n%numPerCub!=0);
		string result;
		int index = 0;
		for(int i=0; i<nRows; ++i) {
			int start = index;
			for(int j=0; j<nCubNum; ++j) {
				if(!i || i==nRows-1) {
					int ind = j * numPerCub + i;
					if(ind < n)
						result.push_back(s[ind]);
				} else {
					// 2 elements
					int ind = j * numPerCub + i;
					if(ind < n)
						result.push_back(s[ind]);
					ind += (nRows-1-i-1)*2 + 2;
					if(ind < n)
						result.push_back(s[ind]);
				}
			}
		}
		return result;
	}
};

