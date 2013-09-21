
/**
		The set [1,2,3,бн,n] contains a total of n! unique permutations.

		By listing and labeling all of the permutations in order,
		We get the following sequence (ie, for n = 3):

		"123"
		"132"
		"213"
		"231"
		"312"
		"321"
		Given n and k, return the kth permutation sequence.

		Note: Given n will be between 1 and 9 inclusive.
*/
// pass 3
class Solution {
public:
    string getPermutation(int n, int k) {
		string result;
		for(int i=1; i<=n; ++i)
			result.push_back(i + '0');
		
		unsigned long long n_prim = 1;
		for(int i=1; i<=n; ++i)
			n_prim *= i;
		
		unsigned long long index = k-1;
		unsigned long long tag = n;
		int i = 0;
		while(i < n) {
			n_prim /= tag;
			int j = index/n_prim + i;
			
			//swap(result[i], result[j]);
			char ch = result[j];
			for(int k=j-1; k>=i; --k)
				result[k+1] = result[k];
			result[i] = ch;
			
			index %= n_prim;
			-- tag;
			++i;
		}
		
		return result;
    }
};






































// pass 2
class Solution {
public:
    string getPermutation(int n, int k) {

		string result;
		long long n_i = 1;
		for(int i=0; i<n; ++i) {
			n_i *= i+1;
			result.push_back('1' + i);
		}
        
		--k;
		if(k >= n_i)
			return result;
		int i = n;
		int lst = 0;
		while(i > 0) {
			n_i /= i;
			int ind = k / n_i;
			k %= n_i;
			char c = result[lst + ind];
			
			// 
			for(int k=lst + ind; k>lst; --k)
				result[k] = result[k-1];
			result[lst] = c;
			++lst;
			--i;
		}
		
		return result;
    }
};

























class Solution {
public:
	string getPermutation(int n, int k)
	{
		string result;
		// calculate n!
		long long n_i = 1;
		for(int i=0; i<n; ++i) {
			n_i *= i+1;
			result.push_back('1' + i);
		}
		--k;
		
		if(k >= n_i)
			return result;
		
		int nInd = k;
		for(int i=n; i>1; --i) {
			n_i /= i; // (n-1)!
			int index = n - i; // index to fill in
		
			int cnt = nInd / n_i;
			nInd = nInd % n_i;
			
			char c = result[index + cnt];
			for(int k=index + cnt - 1; k>=index; --k)
				result[k+1] = result[k];
			result[index] = c;
			
			if(!nInd)
				break;
		}
		
		return result;
	}
};

