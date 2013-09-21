/**
		You are climbing a stair case. It takes n steps to reach to the top.
		Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
// pass 3
class Solution {
public:
    int climbStairs(int n) {
		if(n == 0)
			return 0;
		else if(n == 1)
			return 1;
		else if(n == 2)
			return 2;
		
		// f(n) = f(n-1) + f(n-2)
		int M[2] = {1, 2};
		int flag = 0;
		for(int i=3; i<=n; ++i) {
			M[flag] = M[flag] + M[!flag];
			flag = !flag;
		}
		return M[!flag];
    }
};


















































// pass 2
// recursive version
class Solution {
public:
    int climbStairs(int n) {
	
		if(n<=0)
			return 0;
        else if(n==1)
			return 1;
		else if(n == 2)
			return 2;
		
		// n > 2
		vector<int> M(n, 0);
		M[0] = 1;
		M[1] = 2;
		for(int i=2; i<M.size(); ++i) {
			M[i] = M[i-1] + M[i-2];
		}
		
		return M[n-1];
    }
};




class Solution {
public:
    int climbStairs(int n) {
		if(n<=0)
			return 0;
        else if(n==1)
			return 1;
		else if(n == 2)
			return 2;
		return climbStairs(n-1) + climbStairs(n-2);
    }
};











































class Solution {
public:
    int climbStairs(int n);
};

int Solution::climbStairs(int n)
{
	vector<int> steps(n , 0);
	for(int i=0; i<n; ++i)
	{
		if(!i)
			steps[i] = 1;
		else if(i==1)
			steps[i] = 2;
		else
		{
			int n1 = steps[i-1]; // 
			int n2 = steps[i-2];
			steps[i] = n1 + n2;
		}
	}
	
	return steps[n-1];
}

