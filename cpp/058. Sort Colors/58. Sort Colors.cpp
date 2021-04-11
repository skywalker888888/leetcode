/**
		Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

		Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

		Note:
		You are not suppose to use the library's sort function for this problem.
		
		Follow up:
		A rather straight forward solution is a two-pass algorithm using counting sort.
		First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
		Could you come up with an one-pass algorithm using only constant space?
*/
// pass 3
class Solution {
public:
    void sortColors(int A[], int n) {
    	int i = -1; // point to the last RED at the left end of the array
		int j = n; // point to the first BLUE at the right end of the array
		
		int k = 0;
		while(k < j) {
			switch(A[k]) {
				case 0: // RED
					swap(A[i+1], A[k]);
					++i; ++k;
					break;
				case 1: // WHILE
					++k;
					break;
				case 2: // BLUE
					swap(A[j-1], A[k]);
					--j;
					break;
			}
		}
    }
};

































// pass 2
class Solution {
public:
    void sortColors(int A[], int n) {
		int i = -1;
		int j = n;
		
		int k = 0;
		while(k < j) {
			switch(A[k]) {
			case 0: // red
				swap(A[i+1], A[k]);
				++k;
				++i;
				break;
			case 1: // white
				++k;
				break;
			case 2: // blue
				swap(A[k], A[j-1]);
				--j;
				break;
			}
		}
    }
};







































class Solution {
public:
    void sortColors(int A[], int n);
};


/**
	Use three pointers: r, w, b to indicate the ones of color red, white, and blue
*/
void Solution::sortColors(int A[], int n)
{
	int r, w, b;
	
	r = w = b = -1;
	
	for(int i=0; i<n; ++i)
	{
		switch(A[i])
		{
		case 0: // red
			if(b >= 0)
			{
				if(w >= 0)
				{
					A[i] = A[b];
					A[b] = A[w];
					A[w] = 0;
					++w;
					++b;
				}
				else 
				{
					A[i] = A[b];
					A[b] = 0;
					++b;
				}
			}
			else
			{
				if(w >= 0)
				{
					A[i] = A[w];
					A[w] = 0;
					++w;
				}
			}
			break;
		case 1: // white
			if(b >= 0)
			{
				A[i] = A[b];
				A[b] = 1;
				if(w < 0)
					w = b;
				++b;
			}
			else if(w < 0)
				w = i;
			break;
		case 2: // blue
			if(b < 0)
				b = i;
			break;
		}
	}
	
	return;
}
