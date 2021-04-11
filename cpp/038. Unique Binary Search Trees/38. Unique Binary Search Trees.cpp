/**
		Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
		For example,
		Given n = 3, there are a total of 5 unique BST's.

		   1         3     3      2      1
			\       /     /      / \      \
			 3     2     1      1   3      2
			/     /       \                 \
		   2     1         2                 3
*/
// pass 3
class Solution {
public:
    int numTrees(int n) {
		if(!n)
			return 1;
		
		vector<int> M(n+1, 0);
		M[0] = 1;
		for(int len=1; len<=n; ++len) {
			if(len == 1) {
				M[len] = 1;
			} else {
				M[len] = 0;
				for(int j=0; j<len; ++j) 
					M[len] += M[j] * M[len-j-1];
			}
		}
		return M[n];
    }
};








































//////// pass 2
class Solution {
public:
    int numTrees(int n){
		int result = 0;
		if(!n)
			return 1;
		for(int i=1; i<=n; ++i){
			int left = numTrees(i-1);
			int right = numTrees(n-i);
			result += left * right;
		}
		
		return result;
    }
};



class Solution {
public:
    int numTrees(int n){
		vector<int> M(n+1, 1);
		for(int len=1; len<=n; ++len) {
			if(len == 1)
				M[len] = 1;
			else {
				M[len] = 0;
				for(int i=1; i<=len; ++i) {
					M[len] += M[i-1] * M[len-i];
				}
			}
		}
		return M[n];
    }
};





int getUnique(int n) {
	if(n== 0)
		return 1;
		
	int result = 0;
	for(int i=1; i<=n; ++i)
		result += getUnique(i-1) * getUnique(n-i);
	return result;
}


int getUnique(int n) {
	vector<int> M(n+1, 0);
	for(int len=1; len<n; ++len) {
		if(len == 0)
			M[len] = 1;
		else {
			for(int i=1; i<=len; ++i)
				M[len] += M[i-1] * M[len-i];
		}
	}
	return M[len];
}
















class Solution{
public:
    int numTrees(int n)
	{
		return numTrees(1, n);
	}
	
    int numTrees(int i, int j)
	{
		if(i>j)
			return 0;
		if(i==j)
			return 1;
		int num = 0;
		for(int k=i; k<=j; ++k)
		{
			int numl = numTrees(i, k-1);
			int numr = numTrees(k+1, j);
			if(!numl)
				num += numr;
			else if(!numr)
				num += numl;
			else
				num += numl * numr;
		}
		return num;
	}
};


int main(int argc, char **argv)
{
	Solution sol;
	int num = sol.numTrees(2);
	cout << "2 ==> " << num << "\n";
}

