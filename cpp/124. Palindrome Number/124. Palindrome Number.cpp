/**
		Determine whether an integer is a palindrome. Do this without extra space.
*/
// pass 3
class Solution {
public:
    bool isPalindrome(int x) {
		if(x < 0)
			return false;
		long long llx = x;
		long long llhigh = 1;
		while(llhigh*10 <= x)
			llhigh *= 10;
		while(llhigh >= 1) {
			if(llx/llhigh != llx%10)
				return false;
			
			llx -= (llx/llhigh * llhigh) + llx%10;
			llx /= 10;
			
			llhigh /= 100;
		}
		
		return true;
    }
};






























// pass 2
class Solution {
public:
    bool isPalindrome(int x) {
		if(x < 0)
			return false;
		long long llx = x;
		long long llhigh = 1;
		while(llhigh*10 < x)
			llhigh *= 10;
		while(llhigh >= 1) {
			if(llx/llhigh != llx%10)
				return false;
			
			llx -= (llx/llhigh * llhigh) + llx%10;
			llx /= 10;
			
			llhigh /= 100;
		}
		
		return true;
    }
};









































class Solution {
public:
	bool isPalindrome(int x)
	{
		if(x < 0)
			return false;
			
		int div = 1;
		while(x/div >= 10)
			div *= 10;
		
		while(div > 1)
		{
			if(x < 10)
				return true;
				
			if(x%10 != x/div)
				return false;
			x -= x/div * div;
			x /= 10; // removed the two ends
			div /= 100;
			if(!div)
				return true;
			while(x && div && x/div == 0)
			{
				if(x%10)
					return false;
				div /= 100;
				x /= 10;
			}
		}
		
		return true;
	}
};






