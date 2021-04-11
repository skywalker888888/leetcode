/**
		Divide two integers without using multiplication, division and mod operator.
*/
// pass 3
class Solution {
public:
    int divide(int dividend, int divisor) {
    	if(!dividend)
			return 0;
		
		bool bNeg = false;

		long long ldividend = dividend;
		long long ldivisor = divisor;
		long long lresult = 0;
		
		if(ldividend < 0) {
			bNeg = !bNeg;
			ldividend = -ldividend;
		}
		
		if(ldivisor < 0) {
			bNeg = !bNeg;
			ldivisor = -ldivisor;
		}
		
		if(ldivisor == 1)
			return bNeg?-ldividend: ldividend;
		else if(ldividend < ldivisor)
			return 0;
		else if(ldividend == ldivisor)
			return bNeg?-1:1;
		else if(ldivisor == 2) {
			int res = (ldividend>>1);
			return bNeg?-res:res;
		}
		
		while(ldividend >= ldivisor) {
			long long ldivisor2 = ldivisor;
			long long lres = 1;
			while((ldivisor2<<1) <= ldividend) {
				ldivisor2 <<= 1;
				lres <<= 1;
			}
			
			ldividend -= ldivisor2;
			
			lresult += lres;
		}
		
		int result = (int)lresult;
		
		return bNeg?-result:result;
    }
};




































// pass 2
class Solution {
public:
    int divide(int dividend, int divisor) {
		long long lldividend = dividend;
		long long lldivisor = divisor;
		
		int multi = 1;
		if(lldividend < 0) {
			lldividend = -lldividend;
			multi = -multi;
		}
		if(lldivisor < 0) {
			lldivisor = -lldivisor;
			multi = -multi;
		}
		
		if(!lldividend)
			return 0;
		else if(lldivisor == 1)
			if(multi > 0)
				return lldividend;
			else 
				return -lldividend;
		else if(lldivisor == 2)
			if(multi > 0)
				return lldividend>>1;
			else 
				return -lldividend>>1;
		else if(lldividend < lldivisor)
			return 0;
		else if(lldividend == lldivisor)
			return multi;
		
		// lldividend >  lldivisor
		long long res1 = 0;
		while(lldividend >= lldivisor) {
			int i = 0;
			while(lldivisor<<(i+1) <= lldividend)
				++i;
			res1 += 1<<i;
			lldividend -= lldivisor<<i;
		}
		
		int result = (int)res1;
		
		if(multi > 0)
			return result;
		
		return -result;
    }
};



















































class Solution {
public:
	int divide(int dividend, int divisor) {
		long long lldividend = dividend;
		long long lldivisor = divisor;
		int mult = 1;
		if(!lldividend)
			return 0;
		if(lldividend < 0) {
			lldividend = -lldividend;
			mult = -mult;
		}
		if(lldivisor < 0) {
			lldivisor = -lldivisor;
			mult = -mult;
		}
		
		if(lldividend < lldivisor)
			return 0;
		int result = dividepos(lldividend, lldivisor);
		if(mult < 0)
			return -result;
		return result;
	}


	int dividepos(long long dividend, long long divisor)
	{
		if(divisor == 1)
			return dividend;
		if(divisor == 2)
			return dividend>>1;
		if(dividend == divisor)
			return 1;
		int result = 0;
		int tmp = divisor;
		while(dividend >= divisor) {
			int i = 0;
			while(divisor<<(i+1) <= dividend)
				++i;
			result += 1<<i;
			dividend -= divisor<<i;
		}
		
		return result;
	}
};


