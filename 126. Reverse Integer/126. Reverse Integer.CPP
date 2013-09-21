/**
		Reverse digits of an integer.

		Example1: x = 123, return 321
		Example2: x = -123, return -321

		Have you thought about this?
		Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!

		If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.

		Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?

		Throw an exception? Good, but what if throwing an exception is not an option? You would then have to re-design the function (ie, add an extra parameter).
*/
// pass 3
class Solution {
public:
    int reverse(int x) {
		bool bIsNeg = x<0;
		
		if(bIsNeg)
			x = -x;
		
		if(x < 10)
		return bIsNeg?-x:x;

		while(x %10 == 0)
			x /= 10;
		
			
		long long llx = x;
		
		long long high = 1;
		int count = 1;
		while(high *10 <= llx) {
			high *= 10;
			++count;
		}
		
		long long low = 1;
		while(high > low) {
			long long hvalue = llx%(high*10) / high;
			long long lvalue = llx %(low*10) / low;
			
			llx = (llx-hvalue*high-lvalue*low) + (lvalue*high + hvalue*low);
			low *= 10;
			high /= 10;
		}
		
		int result = (int)llx;
		
		return bIsNeg?-result:result;
    }
};




























// pass 2
class Solution {
public:
    int reverse(int x) {
		long long llx = x;
		if(llx < 0)
			llx = -llx;
		long long high = 1;
		while(high*10 <= llx)
			high *= 10;
		long long low = 1;
		long long value = 0;
		while(high >= low) {
			long long dighigh = (llx%(high*10))/high;
			long long diglow = llx/low%10;
			
			value += dighigh * low;
			if(high != low)
				value += diglow * high;
			
			high /= 10;
			low *= 10;
		}
		
		if(x < 0)
			value = -value;
		if(value>std::numeric_limits<int>::max() || value<std::numeric_limits<int>::min())
			return -1;
		int result = (int)value;
		return result;
    }
};



































class Solution {
public:
	int reverse(int x) {
		int mult = 1;
		if(x < 0) {
			mult = -1;
			x = -x;
		}
		
		int div =  1;
		while(x/div >= 10)
			div *= 10;
		
		if( div < 10)
			return x*mult;
		
		int div2 = 1;
		int result = 0;
		while(div > 0) {
			int nval = (x%10) * div + x/div;
			result += nval * div2;
			
			x -= x/div * div + x %10;
			x /= 10;
			
			if(!x)
				break;
				
			div /= 100;
			div2 *= 10;
			
			if(div == 1) {
				result += x*div2;
				break;
			}
		}
		
		result *= mult;
		
		return result;
	}
};


