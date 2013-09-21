/**
		Say you have an array for which the ith element is the price of a given stock on day i.
		If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/
// pass 3
class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if(n < 2)
			return 0;
		vector<int> prof(n, 0);
		int minIndex = 0;
		for(int i=1; i<n; ++i) 
			if(prices[i] < prices[minIndex]) {
				minIndex = i;
				prof[i] = prof[i-1];
			} else if(prices[i] - prices[minIndex] > prof[i-1]) {
				prof[i] = prices[i] - prices[minIndex];
			} else {
				prof[i] = prof[i-1];
			}
		return prof[n-1];
	}
};

class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if(n < 2)
			return 0;
		vector<int> minLeft(n, 0);
		vector<int> maxRight(n, 0);
		
		for(int i=0; i<n; ++i)
			if(!i)
				minLeft[i] = i;
			else if(prices[i] < prices[minLeft[i-1]])
				minLeft[i] = i;
			else 
				minLeft[i] = minLeft[i-1];
				
		for(int i=n-1; i>=0; --i)
			if(i == n-1)
				maxRight[i] = i;
			else if(prices[i] > prices[maxRight[i+1]])
				maxRight[i] = i;
			else
				maxRight[i] = maxRight[i+1];
		int result = 0;
		for(int i=0; i<n; ++i)
			if(minLeft[i] != maxRight[i])
				result = max(result, prices[maxRight[i]] - prices[minLeft[i]]);
		return result;
    }
};











































class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
		int n = prices.size();
		if(n<2)
			return 0;
		
		vector<int> prof(n, 0);
		int minindex = 0;
		for(int i=1; i<n; ++i)
		{
			if(prices[i]<prices[minindex])
			{
				minindex = i;
				prof[i] = prof[i-1];
			}
			else if(prices[i] - prices[minindex]>prof[i-1])
				prof[i] = prices[i] - prices[minindex];
			else
				prof[i] = prof[i-1];
				
		}
        return prof[n-1];
	}
};



class Solution
{
public:
	int maxProfit(vector<int> &prices)
	{
		int n = prices.size();
		if(n < 2)
			return 0;
			
		return maxProfit(0, n-1, prices);
	}

	int maxProfit(int i, int j, vector<int> &prices)
	{
		if( i== j)
			return 0;

		if(i+1 == j)
			return max(0, prices[j]-prices[i]);
		
		int k = (i+j)/2;
		int nMinPrice = prices[i];
		for(int t=i+1; t<=k; t++)
			nMinPrice = min(nMinPrice, prices[t]);

		int nMaxPrice = prices[k+1];
		for(int t=k+2; t<=j; t++)
			nMaxPrice = max(nMaxPrice, prices[t]);
			
		int nResult = max(0, nMaxPrice - nMinPrice);
		int nMaxL = maxProfit(i, k, prices);
		int nMaxR = maxProfit(k+1, j, prices);
		
		nResult = max(nResult, nMaxL);
		nResult = max(nResult, nMaxR);
		
		return nResult;
	}
};


