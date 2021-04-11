/**
		Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
		For example, 
		Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
		The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!
*/
// pass 3
class Solution {
public:
    int trap(int A[], int n) {
    	stack<int> slots;
		int result = 0;
		for(int i=0; i<n; ) {
			// look for a j, that is taller than i
			int value = 0;
			int j = i+1;
			while(j<n && A[j]<A[i]) {
				value += A[i] - A[j];
				++j;
			}
			if(j < n) {
				while(!slots.empty() && A[slots.top()]<A[j])
					slots.pop();
				if(!slots.empty()) {
					int k = slots.top();
					value += (A[j]-A[i]) * (j-k-1);
				} 
				result += value;
				i = j;
			} else {
				slots.push(i);
				++i;
			}
		}
		return result;
    }
};













































// pass 2
class Solution {
public:
    int trap(int A[], int n) {
		stack<int> highColumns;
		int result = 0;
		int i =0;
		while(i < n) {
			// find one which is higher than A[i]
			int j = i+1;
			int value = 0;
			while(j<n && A[j]<A[i]) {
				value += A[i]-A[j];
				++j;
			}
			// fond one
			if(j < n) {
				while(!highColumns.empty() && A[highColumns.top()]<A[j])
					highColumns.pop();
				if(!highColumns.empty()) {
					int k = highColumns.top();
					value += (A[j]-A[i]) * (j-k-1);
				}
				result += value;
				i = j;
			} else {
				highColumns.push(i);
				++i;
			}
		}
		return result;
    }
};




































class Solution {
public:
	/**
		Greedy algorithm:
		Go forward to find a position which is bigger than this one.
		Then, from that position go backward till find a position is bigger
		
		Accumulate the waters.
		
		Time: O(n)
		Space: O(1)
	 */
	int trap(int A[], int n)
	{
		int result = 0;
		
		if(n<2)
			return 0;
		
		int i=0;
		// skip all the 0's
		while(i<n&&!A[i])
			++i;
		
		while(i<n) {
			int sum = 0;
			int j=i+1;
			while(j<n) {
				if(A[j] >= A[i]) {
					// Check back 
					int k = j-1;
					while(k>=0 && A[k]<A[j])
						--k;
					if(k>=0)
						sum += (A[j] - A[i]) * (j-k-1);
					i = j;
					break;
				} else // 
					sum += A[i] - A[j];
				++j;
			}
			if( j>=n ) {
				++i;
				continue;
			} else
				result += sum;
		}
		return result;
	}
};


