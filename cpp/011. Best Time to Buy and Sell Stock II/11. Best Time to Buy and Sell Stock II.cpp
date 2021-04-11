/**
	Say you have an array for which the ith element is the price of a given stock on day i.

	Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
	
*/
// pass 3
class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int result = 0;
		int n = prices.size();
		if(n < 2)
			return 0;
		for(int i=1; i<n; ++i)
			if(prices[i] > prices[i-1])
				result += prices[i] - prices[i-1];
		return result;
    }
};









































/*
	Analysis:
		Let M[i] be the maximum profit for prices[0..i], we have:
			M[i] = 0 if i==0
			M[i] = prices[1]-prices[0]>0?prices[1]-prices[0]:0; if i==1
			M[i] = max{M[i-1],  M[i-1] + prices[i]-prices[i-1]}
*/
class Solution
{
	const int MININFI = numeric_limits<int>::min();
public:
	int maxProfit(vector<int> &prices)
	{
		int n = prices.size();
		if(n<2)
			return 0;
			
		vector<int> result(n);
		for(int i=0; i<n; i++)
			if(i==0)
				result[i] = 0;
			else if(i==1)
				result[i] = max(0, prices[i] - prices[0]);
			else
				result[i] = max(result[i-1], result[i-1]+prices[i]-prices[i-1]);
				
		return result[n-1];
	}
};
class Solution
{
	const int MININFI = numeric_limits<int>::min();
public:
	int maxProfit(vector<int> &prices)
	{
		int n = prices.size();
		if(n<2)
			return 0;
		
		vector<vector<int> > matrix;
		matrix.resize(n);
		for(int i=0; i<n; i++)
		{
			matrix[i].resize(n);
		}

		// init the matrix
		for(int i=0; i<n; i++)
		{
			matrix[i][i] = 0;
			if(i+1 < n)
				matrix[i][i+1] = max(0, prices[i+1] - prices[i]);
		}
		
		// 
		for(int i=0; i<n; i++)
			for(int nLen=2; nLen<n-i; ++nLen)
			{
				int j = i+nLen;
				// calculate M[i][j]
				int nMax = 0;
				// for(int k=i; k<j; k++)
				// 	nMax = max(nMax, matrix[i][k]+matrix[k][j]);
				//matrix[i][j] = nMax;
				matrix[i][j] = matrix[i][j-1]+matrix[j-1][j];
			}
			
		return matrix[0][n-1];
	}
};





