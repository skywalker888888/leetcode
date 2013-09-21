/**
		Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

		If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

		The replacement must be in-place, do not allocate extra memory.

		Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
		1,2,3 ¡ú 1,3,2
		3,2,1 ¡ú 1,2,3
		1,1,5 ¡ú 1,5,1
*/
// pass 3
class Solution {
public:
    void nextPermutation(vector<int> &num) {
		int n = num.size();
		if(n < 2)
			return;
		int i = n-1;
		while(i>0 && num[i-1]>=num[i])
			--i;
		if(!i) {
			reverse(num.begin(), num.end());
			return;
		}
		--i;
		int j = n-1;
		while(num[j] <= num[i])
			--j;
		swap(num[i], num[j]);
		reverse(num.begin()+i+1, num.end());
		return;
    }
};























// pass 2
class Solution {
public:
    void nextPermutation(vector<int> &num) {
		int n = num.size();
		int i = n - 1;
		while(i-1>=0 && num[i-1]>=num[i])
			--i;
		if(!i)
			sort(num.begin(), num.end());
		else {
			reverse(num.begin()+i, num.end());
			int j = i;
			while(num[j] <= num[i-1])
				++j;
			swap(num[i-1], num[j]);
		}
    }
};










































class Solution {
public:
	/**
		From end to head, find the first increasing element which num[i]<num[i+1]
		Then it is easy to find the next permutation
		
	*/
	void nextPermutation(vector<int> &num)
	{
		int n = num.size();
		if(n < 2)
			return;
		
		int i = n - 2;
		while(i>=0 && num[i]>=num[i+1])
			--i;
		if(i < 0)
			reverse(num.begin(), num.end());
		else {
			// 
			reverse(num.begin()+i+1, num.end());
			
			// swap 
			int j = i+1;
			while(j<n && num[j]<=num[i])
				++j;
			
			swap(num[i], num[j]);
		}
	}
};


