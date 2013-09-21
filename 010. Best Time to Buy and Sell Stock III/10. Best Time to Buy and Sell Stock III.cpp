/**
		Say you have an array for which the ith element is the price of a given stock on day i.

		Design an algorithm to find the maximum profit. You may complete at most two transactions.

		Note:
		You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
		A transaction means buy and sell.
		The sell and buy can happens in same day.
*/
// pass 3
class Solution {
public:
    int maxProfit(vector<int> &prices) {
    	int n = prices.size();
		if(n < 2)
			return 0;
		
		vector<int> leftProf(n, 0);
		vector<int> rightProf(n, 0);
		
		leftProf[0] = 0;
		int minIndex = 0;
		for(int i=1; i<n; ++i)
			if(prices[i] < prices[minIndex]) {
				minIndex = i;
				leftProf[i] = leftProf[i-1];
			} else {
				leftProf[i] = max(leftProf[i-1], prices[i] - prices[minIndex]);
			}
			
		rightProf[n-1] = 0;
		int maxIndex = n-1;
		for(int i=n-2; i>=0; --i)
			if(prices[i] > prices[maxIndex]) {
				maxIndex = i;
				rightProf[i] = rightProf[i+1];
			} else {
				rightProf[i] = max(rightProf[i+1], prices[maxIndex]-prices[i]);
			}
		int result = 0;
		for(int i=0; i<n; ++i)
			result = max(result, leftProf[i]+rightProf[i]);
		return result;
    }
};














































#define MININFI  -9999

class Solution
{
	//static const int MININFI;
public:
	/*
		First check from left to right to find the maximum profit between the start to the i-th day.
		Then check from right to left to find the maximum profit between the i-th day to the end.
		Add two arrays and find the maximum profit.	
	 */
	int maxProfit(vector<int> &prices) {
		if (prices.size() < 2) return 0;
		int leftProfit[prices.size()];
		int rightProfit[prices.size()];
		int minv = 0, profit = 0;
		leftProfit[0] = 0;
		for(int i = 1; i < prices.size(); i++) {
			if (prices[i] < prices[minv])
				minv = i;
			leftProfit[i] = max(prices[i] - prices[minv], leftProfit[i-1]);
		}
		rightProfit[prices.size() - 1] = 0;
		int maxv = prices.size() - 1;
		for(int i = prices.size() - 2; i >= 0; i--) {
			if (prices[i] > prices[maxv])
				maxv = i;
			rightProfit[i] = max(prices[maxv] - prices[i], rightProfit[i+1]);

			if (profit < leftProfit[i] + rightProfit[i])
				profit = leftProfit[i] + rightProfit[i];
		}
		return profit;
	}
};





class Solution
{
	//static const int MININFI;
public:
	int maxProfitBruteForce(vector<int> &prices) {
		generateMatrix(prices);
		int n = prices.size();
		int nMax = 0;
		for(int i=0; i<n; i++)
			for(int j=i+1; j<n; j++) {
				int num1 = m_vMatrix[i][j];
				int num2 = calculateMaxProfit(j+1, j+2);
				nMax = max(nMax, num1+num2);
				nMax = max(nMax, num2);
				nMax = max(nMax, num1);
			}
		//cout << "max profit: " << nMax << endl;
		return nMax;
	}
	void generateMatrix(vector<int> &prices) {
		m_vMatrix.clear();
		int n = prices.size();
		for(int i=0; i<n; i++) {
			vector<int> line;
			for(int j=0; j<n; j++) {
				line.push_back(MININFI);
				if(j > i)
					line[j] = prices[j] - prices[i];
			}
			m_vMatrix.push_back(line);
		}
	}
	
	// i < j
	int calculateMaxProfit(int i, int j) {
		int nMax = MININFI;
		int n = m_vMatrix.size();
		for(int a=i; a<n; a++)
			for(int b=j; b<n; b++)
				if(a < b)
					nMax = max(nMax, m_vMatrix[a][b]);

		return nMax;
	}

private:
	vector<vector<int> >	m_vMatrix;
};

class Solution
{
	//static const int MININFI;
public:
	int maxProfitBruteForce(vector<int> &prices) {
		int nMax = 0;
		int n = prices.size();
		for(int i=0; i<n; i++)
			for(int j=i+1; j<n; j++) {
				int num1 = prices[j]-prices[i];
				int num2 = 0;
				for(int a=j+1; a<n; a++)
					for(int b=a+1; b<n; b++)
						num2 = max(num2, prices[b]-prices[a]);
				nMax= max(nMax, num1);
				nMax= max(nMax, num2);
				nMax= max(nMax, num1+num2);
			}
			
		return nMax;
	}
};



