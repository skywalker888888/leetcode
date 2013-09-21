/**
		Implement int sqrt(int x).
		Compute and return the square root of x.	
*/
// pass 3
class Solution {
public:
    int sqrt(int x) {
		if(x <= 0)
			return 0;
		long long lx = x;
		long long s = 0;
		long long e = lx/2 + 1;
		while(s <= e) {
			long long m = (s + e) / 2;
			long long value = m * m;
			if( value == lx)
				return (int)m;
			else if(value > lx)
				e = m - 1;
			else
				s = m + 1;
		}
		
		return e;
    }
};
















































// pass 2
class Solution {
public:
    int sqrt(int x) {
        // find a number m, that m*m<=x and (m+1)^2 > x
		long long lBegin = 0;
		long long lEnd = x;
		while(lBegin <= lEnd) {
			long long lMid = (lBegin+lEnd)/2;
			long long lSque = lMid * lMid;
			if(lSque == x)
				return lMid;
			else if(lSque > x)
				lEnd = lMid-1;
			else
				lBegin = lMid+1;
		}
		return (int)lEnd;
    }
};




































class Solution {
public:
	/**
		Use binary search
	 */
	int sqrt(int x)
	{
		if(x < 2)
			return x;
			
		long long nBegin = 0;
		long long nEnd = x;
		
		while(nBegin <= nEnd)
		{
			long long nMid = (nEnd + nBegin)/2;
			//cout << nBegin << ", " << nMid << ", " << nEnd << "\n";
			long long nSqu = nMid * nMid;
			if(nSqu < nMid)
				nEnd = nMid-1;
			else if(nSqu == x)
				return nMid;
			else if(nSqu < x)
				nBegin = nMid+1;
			else
				nEnd = nMid-1;
		}

		return (int)nEnd;
	}
};




int main(int argc, char **argv)
{
	Solution sol;
	int x = 2147395599;
	
	int res = sol.sqrt(x);
	cout << x << " : " << res << "\n";
}
