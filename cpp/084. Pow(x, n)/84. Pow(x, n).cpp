/**
		Implement pow(x, n).
		
		Requirements:
		Runtime in O( lg(n) ) and space of O(1).
*/
// pass 3
class Solution {
public:
    double pow(double x, int n) {
		if(x == 1.0)
			return 1.0;
		else if(x == -1.0)
			return n%2?-1.0:1.0;
		else if(!n)
			return 1.0;
		else if(n < 0)
			return 1.0/pow(x, -n);
		
		if(n%2)
			return x * pow(x, n-1);
		
		double res = pow(x, n/2);
		return res*res;
    }
};












































// pass 2
class Solution {
public:
    double pow(double x, int n) {
		if(!n)
			return 1;
		else if(x == 1.0)
			return 1.0;
		else if(x == -1.0)
			return (n%2?-1.0:1.0);
		else if(n < 0)
			return 1/pow(x, -n);
		
		if(n % 2) {
			double res = pow(x, n-1);
			return res * x;
		}
		
		double res = pow(x, n/2);
		return res * res;
    }
};















































class Solution {
public:
	double pow(double x, int n)
	{
		if(!n)
			return 1;
		else if(!x || x==1)
			return x;
		else if(x == -1)
			return (n%2?-1.0:1.0);
		else if(n < 0)
			return 1/pow(x, -n);
		
		double rem = n%2?x:1.0;
		n = n%2?n-1:n;
		double result = pow(x, n/2);
		return result*result*rem;
	}
};

