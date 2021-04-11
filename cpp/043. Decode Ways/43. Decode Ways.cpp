/**
		A message containing letters from A-Z is being encoded to numbers using the following mapping:

		'A' -> 1
		'B' -> 2
		...
		'Z' -> 26
		Given an encoded message containing digits, determine the total number of ways to decode it.

		For example,
		Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

		The number of ways decoding "12" is 2.
*/
// pass 3
class Solution {
public:
    int numDecodings(string s) {
		int n = s.size();
		if(!n)
			return 0;
		vector<int> M(n);
		for(int i=0; i<s.size(); ++i)
			if(i == 0) {
				if(s[i] == '0')
					return 0;
				else
					M[i] = 1;
			} else {
				M[i] = 0;
				if(s[i] != '0')
					M[i] += M[i-1];
				if(s[i-1] != '0') {
					string str = s.substr(i-1, 2);
					stringstream ss(str);
					int value;
					ss >> value;
					if(value>=10 && value<=26)
						M[i] += (i==1)?1:M[i-2];
				}
			 }
		return M[n-1];
	}
};

class Solution {
public:
    int numDecodings(string s) {
		int n = s.size();
		if(!n)
			return 0;
		
		/*
			M[i] is the code way number of string s[0..i-1], So:
			M[i] =	1, if i==0
				 =	1, if i==1 and s[i-1]>0
				 =	(s[i]!='0'?M[i-1]:0) + (0<s[i-2..i-1]<26?M[i-2]:0)
			
		*/
		vector<int> M(n+1, 0);
		M[0] = 1;
		for(int i=1; i<=s.size(); ++i) {
			// calculate M[i]
			M[i] = 0;
			if(s[i-1] != '0')
				M[i] += M[i-1];
			if(i>1 && s[i-2]!='0') {
				string str = s.substr(i-2, 2);
				stringstream ss(str);
				int value;
				ss >> value;
				if(value<=26 && value>0)
					M[i] += M[i-2];
			}
		}
		return M[n];
    }
};









































// pass 2
class Solution {
public:
    int numDecodings(string s){
    	if(!s.size())
			return 0;
		int n = s.size();
		vector<int> vec(n, -1);
		
		for(int j=n-1; j>=0; --j){
			// calculate s[j..s.size()-1]
			if(s[j] == '0')
				vec[j] = 0;
			else if(j==n-1)
				vec[j] = 1;
			else{
				vec[j] = vec[j+1];
				//
				if(s[j]<'2' || s[j]=='2'&&s[j+1]<'7')
					if(j==n-2)
						++vec[j];
					else
						vec[j]+= vec[j+2];
					
			}
		}
		
		return vec[0];
	}
};


// Recursive solution
class Solution {
public:
    int numDecodings(string s){
    	if(!s.size())
			return 0;
		int n = s.size();
		//vector<vector<int> > matrix(n, vector<int>(n, -1));
		vector<int> vec(n, -1);
		return numDecodings(s, 0, vec);
    }
    int numDecodings(const string &s, const int index, vector<int> &vec){
		if(vec[index] >= 0)
			return vec[index];

		if(s[index] == '0'){
			vec[index] = 0;
			return vec[index];
		}
			
		if(index == s.size()-1){
			vec[index] = 0;
			if(s[index]>'0')
				vec[index] = 1;
			return vec[index];
		}
			
		int ntotal = 0;
		for(int i=index; i<s.size(); ++i){
			if(i==index+1&&(s[index]=='2'&&s[index+1]>'6' ||s[index]>'2') || i>index+1)
				break;
			if(i == s.size()-1)
				ntotal += 1;
			else{
				int cnt = numDecodings(s, i+1, vec);
				if(cnt > 0)
					ntotal += cnt;
			}
		}
		vec[index] = ntotal;
		return ntotal;
	}
};

























class Solution
{
public:
    int numDecodings(string s);
    int numDecodings2(string s);
	
private:
    int numDecodings(int nStart, string& s);
	int	getNumber(int i, int j, string& s);
};


int Solution::numDecodings2(string s)
{
	if(!s.size())
		return 0;
		
	return numDecodings(0, s);
}


int Solution::numDecodings(int nStart, string& s)
{
	if(nStart >= s.size())
		return 1;
		
	int nFirstNum = getNumber(nStart, nStart, s);
	if(nFirstNum < 1)
		return 0;
		
	int nNum = 0;
	for(int i=nStart; i<s.size() && getNumber(nStart, i, s)>=1 && getNumber(nStart, i, s)<=26; ++i)
		nNum += numDecodings(i+1, s);
	
	return nNum;
}


int	Solution::getNumber(int i, int j, string& s)
{
	if(i > j)
		return -1;
	
	int nRes = 0;
	for(int k=i; k<=j; ++k)
		nRes = 10 * nRes + s[k]-'0';
	
	return nRes;
}

/**
	M[i,j] = 	0 if s[i] == '0'
				1 if i==j and s[i]!=0
				M[i,j-1] if s[j-1]s[j]>26
				M[i,j-1]+M[i,j-2] if s[j-1]s[j]<=26
				
 */
int Solution::numDecodings(string s)
{
	int n = s.size();
	if(!n)
		return 0;
	
	for(int i=0; i<n; ++i)
		if(s[i]<'0' || s[i]>'9')
			return 0;
	
	if(s[0] == '0')
		return 0;
	
	vector<vector<int> > matrix(n, vector<int>(n, 0));
	for(int i=0; i<n; ++i)
		if(s[i] == '0')
			matrix[i][i] = 0;
		else 
			matrix[i][i] = 1;
	
	for(int nLen = 1; nLen<n; ++nLen)
	{
		for(int i=0; i<n-nLen; ++i)
		{
			int j = i+nLen;
			if(j >= n)
				break;
			if(s[i] == '0')
			{
				matrix[i][j] = 0;
				continue;
			}
			int nSum = 0;
			for(int k=j; k>=i; --k)
			{
				int nNum = getNumber(k, j, s);
				if(nNum > 26)
					break;
				if(nNum < 1)
					continue;
				if(s[k] == '0')
					continue;
				
				// valid 1<=nNum<=26
				if(k > i)
					nSum += matrix[i][k-1]; // s[k..j]
				else if(k == i)
					nSum += matrix[i][i]; // s[i...j]
			}
			matrix[i][j] = nSum;
		}
	}
	return matrix[0][n-1];
}
