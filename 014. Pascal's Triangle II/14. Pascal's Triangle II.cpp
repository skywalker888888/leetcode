/**
		Given an index k, return the kth row of the Pascal's triangle.

		For example, given k = 3,
		Return [1,3,3,1].

		Note:
		Could you optimize your algorithm to use only O(k) extra space?
		
		http://en.wikipedia.org/wiki/Pascal's_triangle
		
 */
// pass 3
class Solution {
public:
    vector<int> getRow(int rowIndex) {
		vector<int> result(rowIndex+1, 0);
		vector<vector<int> > data(2, vector<int>(rowIndex+1, 0));
		data[0][0] = 1;
		int flag = 1;
		for(int i=1; i<=rowIndex; ++i) {
			for(int j=0; j<=i; ++j) {
				if(!j || j==i)
					data[flag][j] = 1;
				else
					data[flag][j] = data[!flag][j-1]+data[!flag][j];
			}
			flag = !flag;
		}
		return data[!flag];
    }
};



































 
/// Pass 2
class Solution
{
public:
    vector<int> getRow(int rowIndex)
	{
		if(rowIndex < 0)
			return vector<int>();
		int flag = 1;
		
		vector<vector<int> > result(2, vector<int>(rowIndex+1, 0));
		result[!flag][0] = 1;
		for(int i=1; i<=rowIndex; ++i)
		{
			for(int k=0; k<=i; ++k)
			{
				if(k==0 || k==i)
					result[flag][k] = 1;
				else
					result[flag][k] = result[!flag][k-1] + result[!flag][k];
			}
			flag = !flag;
		}
		
		return result[!flag];
	}
};






 
class Solution
{
public:
    vector<int> getRow(int rowIndex);
};


vector<int> Solution::getRow(int rowIndex)
{
	vector<int> result;
	if(rowIndex < 0)
		return result;
	int n = rowIndex + 1;

	vector<int> ptri;
	ptri.resize(n);
	result.resize(n);
	
	result[0] = 1;
	for(int i=1; i<n; i++)
	{
		for(int j=0; j<=i; j++)
		{
			ptri[j] = 0;
			// ptri[j] = result[j-1] + result[j]
			if(j-1 >= 0)
				ptri[j] += result[j-1];
			if(j <= i-1)
				ptri[j] += result[j];
		}
		
		//
		result = ptri;
	}
	
	return result;
}
