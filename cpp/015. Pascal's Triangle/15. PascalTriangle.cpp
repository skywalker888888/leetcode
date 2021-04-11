/**
		Given numRows, generate the first numRows of Pascal's triangle.

		For example, given numRows = 5,
		Return

		[
			 [1],
			[1,1],
		   [1,2,1],
		  [1,3,3,1],
		 [1,4,6,4,1]
		]
 */
// pass 3
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
    	if(!numRows)
			return vector<vector<int> >();
			
		vector<vector<int> > result;
		for(int i=0; i<numRows; ++i) {
			result.push_back(vector<int>(i+1));
			for(int j=0; j<=i; ++j)
				if(!j || j==i)
					result[i][j] = 1;
				else
					result[i][j] = result[i-1][j-1] + result[i-1][j];
		}

		return result;
    }
};









































//// pass 2 
class Solution
{
public:
    vector<vector<int> > generate(int numRows)
	{
		vector<vector<int> > result(numRows);
		for(int i=0; i<numRows; ++i)
			for(int j=0; j<=i; ++j)
				if(j==0 || j==i)
					result[i].push_back(1);
				else
					result[i].push_back(result[i-1][j-1]+result[i-1][j]);
		return result;
	}
};
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
class Solution
{
public:
    vector<vector<int> > generate(int numRows);
};


vector<vector<int> > Solution::generate(int numRows)
{
	int n = numRows;

	vector<vector<int> > result;
	if(!n)
		return result;
		
	result.resize(n);
		
	result[0].push_back(1);
	for(int i=1; i<n; i++)
		for(int j=0; j<=i; j++)
		{
			result[i].push_back(0);
			if(j-1 >= 0)
				result[i][j] += result[i-1][j-1];
			if(j < i)
				result[i][j] += result[i-1][j];
		}
	return result;
}
