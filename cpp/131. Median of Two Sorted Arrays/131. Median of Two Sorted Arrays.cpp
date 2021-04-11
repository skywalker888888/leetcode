/**
	There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
	http://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/
	http://www.youtube.com/watch?v=_H50Ir-Tves&feature=player_detailpage
*/
// pass 2

//http://leetcode.com/2011/03/median-of-two-sorted-arrays.html
class Solution {
    public:
    double findMedianBaseCase(int med, int C[], int n) {
        if (n == 1)
        return (med+C[0])/2.0;
        
        if (n % 2 == 0) {
            int a = C[n/2 - 1], b = C[n/2];
            if (med &lt;= a)
            return a;
            else if (med &lt;= b)
            return med;
            else /* med &gt; b */
            return b;
            } else {
            int a = C[n/2 - 1], b = C[n/2], c = C[n/2 + 1];
            if (med &lt;= a)
            return (a+b) / 2.0;
            else if (med &lt;= c)
            return (med+b) / 2.0;
            else /* med &gt; c */
            return (b+c) / 2.0;
        }
    }
    
    double findMedianBaseCase2(int med1, int med2, int C[], int n) {
        if (n % 2 == 0) {
            int a = (((n/2-2) &gt;= 0) ? C[n/2 - 2] : INT_MIN);
            int b = C[n/2 - 1], c = C[n/2];
            int d = (((n/2 + 1) &lt;= n-1) ? C[n/2 + 1] : INT_MAX);
            if (med2 &lt;= b)
            return (b+max(med2,a)) / 2.0;
            else if (med1 &lt;= b)
            return (b+min(med2,c)) / 2.0;
            else if (med1 &gt;= c)
            return (c+min(med1,d)) / 2.0;
            else if (med2 &gt;= c)
            return (c+max(med1,b)) / 2.0;
            else  /* a &lt; med1 &lt;= med2 &lt; b */
            return (med1+med2) / 2.0;
            } else {
            int a = C[n/2 - 1], b = C[n/2], c = C[n/2 + 1];
            if (med1 &gt;= b)
            return min(med1, c);
            else if (med2 &lt;= b)
            return max(med2, a);
            else  /* med1 &lt; b &lt; med2 */
            return b;
        }
    }
    double findMedianSingleArray(int A[], int n) {
        assert(n &gt; 0);
        return ((n%2 == 1) ? A[n/2] : (A[n/2-1]+A[n/2])/2.0);
    }
    
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        assert(m+n &gt;= 1);
        if (m == 0)
			return findMedianSingleArray(B, n);
        else if (n == 0)
			return findMedianSingleArray(A, m);
        else if (m == 1)
			return findMedianBaseCase(A[0], B, n);
        else if (n == 1)
			return findMedianBaseCase(B[0], A, m);
        else if (m == 2)
			return findMedianBaseCase2(A[0], A[1], B, n);
        else if (n == 2)
			return findMedianBaseCase2(B[0], B[1], A, m);
        
        int i = m/2, j = n/2, k;
        if (A[i] &lt;= B[j]) {
				k = ((m%2 == 0) ? min(i-1, n-j-1) : min(i, n-j-1));
				assert(k &gt; 0);
				return findMedianSortedArrays(A+k, m-k, B, n-k);
            } else {
            k = ((n%2 == 0) ? min(m-i-1, j-1) : min(m-i-1, j));
            assert(k &gt; 0);
            return findMedianSortedArrays(A, m-k, B+k, n-k);
        }
    }
}; 




class Solution {
public:
    double findMedianSortedArrays(int A[], int l, int B[], int m) {
		if(!l && !m)
			return 0;
		if(l == 0) {
			if(m % 2)
				return B[m/2];
			else {
				double result = B[m/2]+B[m/2+1];
				return result/2;
			}
		} else if(m == 0) {
			if(l % 2)
				return A[l/2];
			else {
				double result = A[l/2]+A[l/2+1];
				return result/2;
			}
		}
		
		if((m+l)%2) {
			int left = max(1, div2Ceiling(m+l)-m);
			int right = min(l, div2Ceiling(n+l));
			return findMedianSortedArrays(A, l, B, n, left, right); 
		}
		
		int res1 = ;
		if(A[l-1] >= B[m-1]) {
			int *AA = new int[l-1];
			for(int i=0; i<l-1; ++i)
				AA[i-1] = A[i];
			res2 = findMedianSortedArrays(AA, l-1, B, m);
		} else {
			int *BB = new int[m-1];
			for(int i=0; i<m-1; ++i)
				BB[i-1] = B[i];
			res2 = findMedianSortedArrays(A, l, BB, m-1);
		}

		int res2 = 0.0;
		if(A[0] <= B[0]) {
			int *AA = new int[l-1];
			for(int i=1; i<l; ++i)
				AA[i-1] = A[i];
			res2 = findMedianSortedArrays(AA, l-1, B, m);
		} else {
			int *BB = new int[m-1];
			for(int i=1; i<m; ++i)
				BB[i-1] = B[i];
			res2 = findMedianSortedArrays(A, l, BB, m-1);
		}
		
		double result = res1+res2;
		result /= 2;
		
		return result;
	}
    double findMedianSortedArrays(int A[], int l, int B[], int m, int left, int right) {
		if(left > right) {
			left = max(1, div2Ceiling(n)-m);
			right = min(m, div2Ceiling(m+l));
			return findMedianSortedArrays(B, n, A, m, left, right);
		}
		int i = div2Ceiling(left + right);
		int j = div2Ceiling(l+m) - i;
		if((j==0 || A[i]>B[j]) &&(j==m || A[i]<=B[j+1]))
			return A[i-1];
		else if((j==0 || A[i]<B[j]) && (j!=m && A[i]>B[j+1]))
			return 	findMedianSortedArrays(A, l, B, m, left, i-1);
		return 	findMedianSortedArrays(A, l, B, m, i+1, right);
	}
	
	int div2Floor(int n) {
		if(n%2 ==0)
			return n/2;
		else
			return (n-1)/2;
	}
	int div2Ceiling(int n) {
		if(n%2 == 0)
			return n/2;
		return (n+1)/2;
	}
	
};




// http://ideone.com/FtqjM
class Solution {
public:
    double findMedianSortedArrays(int A[], int n, int B[], int m) {
		if(!n && !m)
			return 0;
		if(!n) {
			if(m % 2)
				return B[m/2];
			else {
				double result = B[m/2]+B[m/2+1];
				return result/2.0;
			}
		} else if(m == 0) {
			if(n % 2)
				return A[n/2];
			else {
				double result = A[n/2]+A[n/2+1];
				return result/2.0;
			}
		}
		//base case # 1
        if ( n == 1 ) {
                if ( m == 1 ) 
                        return (A[0] + B[0]) / 2.0; 
                if ( m % 2 == 1) 
                         return ( B[m/2] + MedianOfThree (A[0], B[m/2-1], B[m/2+1]) ) / 2.0 ;
                else 
                        return MedianOfThree ( A[0], B[m/2-1], B[m/2] );
        }
        //base case # 2
        if ( n == 2 ) {
			if ( m == 2 )
				return MedianOfFour (A[0], A[1], B[0], B[1]);
			if ( m % 2 == 1 )
				return MedianOfThree ( B[m/2], min(A[0], B[m/2+1]), max (A[1], B[m/2-1]) ) ;
			else 
				return MedianOfFour ( B[m/2-1], B[m/2], min(A[0], B[m/2+1]), max(A[1], B[m/2-2]) );
        }
        int minRemoved, idxA = n/2 , idxB = m/2 ;
        if ( A[idxA] < B[idxB]  ) {
			if ( n % 2 == 0 ) --idxA;       //for even number of elements --idxA points to lower median of A[]
			minRemoved = min ( idxA, m - idxB - 1) ;        
			return findMedianSortedArrays ( A + minRemoved, n - minRemoved, B, m - minRemoved); 
        } else {
			if ( m % 2 == 0 ) --idxB;       //for even number of elements --idxB points to lower median of B[]
			minRemoved = min ( n - idxA - 1, idxB) ;        
			return findMedianSortedArrays ( A, n - minRemoved, B + minRemoved, m - minRemoved); 
        }
	}
	
	double MedianOfFour (int a, int b, int c, int d) {
		int minValue = min (d, min (a, min (b,c) ) );
		int maxValue = max (d, max (a, max (b,c) ) );
		return (a + b + c + d - minValue - maxValue) / 2.0 ;
	}
	 
	double MedianOfThree (int a, int b, int c) {
		int minValue = min (a, min (b,c) ) ;
		int maxValue = max (a, max (b,c) ) ;
		return (a + b + c - minValue - maxValue);
	}
};



double MedianOfFour (int a, int b, int c, int d)
{
        int minValue = min (d, min (a, min (b,c) ) );
        int maxValue = max (d, max (a, max (b,c) ) );
        return (a + b + c + d - minValue - maxValue) / 2.0 ;
}
 
double MedianOfThree (int a, int b, int c)
{
        int minValue = min (a, min (b,c) ) ;
        int maxValue = max (a, max (b,c) ) ;
        return (a + b + c - minValue - maxValue);
}
 
//constraint : n <= m
double MedianSortedArrays (int A[MAX], int n, int B[MAX], int m)
{
        //base case # 1
        if ( n == 1 ) 
        {
                if ( m == 1 ) 
                        return (A[0] + B[0]) / 2.0; 
                if ( m % 2 == 1) 
                         return ( B[m/2] + MedianOfThree (A[0], B[m/2-1], B[m/2+1]) ) / 2.0 ;
                else 
                        return MedianOfThree ( A[0], B[m/2-1], B[m/2] );
        }
 
        //base case # 2
        if ( n == 2 ) 
        {
                if ( m == 2 )
                        return MedianOfFour (A[0], A[1], B[0], B[1]);
                if ( m % 2 == 1 )
                        return MedianOfThree ( B[m/2], min(A[0], B[m/2+1]), max (A[1], B[m/2-1]) ) ;
                else 
                        return MedianOfFour ( B[m/2-1], B[m/2], min(A[0], B[m/2+1]), max(A[1], B[m/2-2]) );
        }
 
 
        int minRemoved, idxA = n/2 , idxB = m/2 ;
 
        if ( A[idxA] < B[idxB]  )                                               
        {
                if ( n % 2 == 0 ) --idxA;       //for even number of elements --idxA points to lower median of A[]
                minRemoved = min ( idxA, m - idxB - 1) ;        
                return MedianSortedArrays ( A + minRemoved, n - minRemoved, B, m - minRemoved); 
        }
        else                                                                                    
        {
                if ( m % 2 == 0 ) --idxB;       //for even number of elements --idxB points to lower median of B[]
                minRemoved = min ( n - idxA - 1, idxB) ;        
                return MedianSortedArrays ( A, n - minRemoved, B + minRemoved, m - minRemoved); 
        }
 
}
 







































// Time: O(m + n)
// Space: O(1)
class Solution {
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n)
	{
		int nCount = 0;
		int nFound = 0;
		
		double nSum = 0.0;
		
		int nIndex = 0;
		if((m+n) %2)
			nCount = 1;
		else
			nCount = 2;
		nIndex = (m+n-1)/2;
		
		int i=0, j=0;
		while(i<m && j<n) {
			if(A[i] < B[j]) {
				if(pickNum(i+j, nIndex, nCount, nFound)) {
					nSum += A[i];
					if(nFound >= nCount)
						break;
				}
				++i;
			} else if(A[i] > B[j]) {
				if(pickNum(j+i, nIndex, nCount, nFound)) {
					nSum += B[j];
					if(nFound >= nCount)
						break;
				}
				++j;
			} else {
				if(pickNum(i+j, nIndex, nCount, nFound)) {
					nSum += A[i];
					if(nFound >= nCount)
						break;
				}
				++i;
				if(pickNum(j+i, nIndex, nCount, nFound)) {
					nSum += B[j];
					if(nFound >= nCount)
						break;
				}
				++j;
			}
		}
		while(i<m && nFound<nCount) {
			if(pickNum(i+j, nIndex, nCount, nFound)) {
				nSum += A[i];
				if(nFound >= nCount)
					break;
			}
			++i;
		}
		while(j<n && nFound<nCount) {
			if(pickNum(j+i, nIndex, nCount, nFound)) {
				nSum += B[j];
				if(nFound >= nCount)
					break;
			}
			++j;
		}
		
		double dres = nSum/nCount;
		return dres;
	}

	bool pickNum(int i, int& nIndex, int nCount, int& nFound) {
		bool bPick = i==nIndex;
		if(bPick) {
			++ nFound;
			++ nIndex;
		}
		return bPick;
	}
};


// =======================================
// http://www.geeksforgeeks.org/median-of-two-sorted-arrays/
// http://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/
class Solution{
public:
	// A wrapper function around findMedianUtil(). This function makes
	// sure that smaller array is passed as first argument to findMedianUtil
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		if(!m && !n)
			return 0.0;
		else if(!m) {
			if(n % 2) // odd number
				return B[n/2];
			else { // even number
				double val = B[(n-1)/2];
				val += B[(n-1)/2 + 1];
				return val/2.0;
			}
		}
		
		if ( m > n )
		   return findMedianSortedArrays( B, n, A, m );
		return findMedianUtil( A, m, B, n );
	}

	// A utility function to find maximum of two integers
	int max( int a, int b )
	{ return a > b ? a : b; }
	 
	// A utility function to find minimum of two integers
	int min( int a, int b )
	{ return a < b ? a : b; }
	 
	// A utility function to find median of two integers
	float MO2( int a, int b )
	{ return ( a + b ) / 2.0; }
	 
	// A utility function to find median of three integers
	float MO3( int a, int b, int c )
	{
		return a + b + c - max( a, max( b, c ) )
						 - min( a, min( b, c ) );
	}
	 
	// A utility function to find median of four integers
	float MO4( int a, int b, int c, int d )
	{
		int Max = max( a, max( b, max( c, d ) ) );
		int Min = min( a, min( b, min( c, d ) ) );
		return ( a + b + c + d - Max - Min ) / 2.0;
	}
	 
	// This function assumes that N is smaller than or equal to M
	float findMedianUtil( int A[], int N, int B[], int M )
	{
		// If the smaller array has only one element
		if( N == 1 )
		{
			// Case 1: If the larger array also has one element, simply call MO2()
			if( M == 1 )
				return MO2( A[0], B[0] );
	 
			// Case 2: If the larger array has odd number of elements, then consider
			// the middle 3 elements of larger array and the only element of
			// smaller array. Take few examples like following
			// A = {9}, B[] = {5, 8, 10, 20, 30} and
			// A[] = {1}, B[] = {5, 8, 10, 20, 30}
			if( M & 1 )
				return MO2( B[M/2], MO3(A[0], B[M/2 - 1], B[M/2 + 1]) );
	 
			// Case 3: If the larger array has even number of element, then median
			// will be one of the following 3 elements
			// ... The middle two elements of larger array
			// ... The only element of smaller array
			return MO3( B[M/2], B[M/2 - 1], A[0] );
		}
	 
		// If the smaller array has two elements
		else if( N == 2 )
		{
			// Case 4: If the larger array also has two elements, simply call MO4()
			if( M == 2 )
				return MO4( A[0], A[1], B[0], B[1] );
	 
			// Case 5: If the larger array has odd number of elements, then median
			// will be one of the following 3 elements
			// 1. Middle element of larger array
			// 2. Max of first element of smaller array and element just
			//    before the middle in bigger array
			// 3. Min of second element of smaller array and element just
			//    after the middle in bigger array
			if( M & 1 )
				return MO3 ( B[M/2],
							 max( A[0], B[M/2 - 1] ),
							 min( A[1], B[M/2 + 1] )
						   );
	 
			// Case 6: If the larger array has even number of elements, then
			// median will be one of the following 4 elements
			// 1) & 2) The middle two elements of larger array
			// 3) Max of first element of smaller array and element
			//    just before the first middle element in bigger array
			// 4. Min of second element of smaller array and element
			//    just after the second middle in bigger array
			return MO4 ( B[M/2],
						 B[M/2 - 1],
						 max( A[0], B[M/2 - 2] ),
						 min( A[1], B[M/2 + 1] )
					   );
		}
	 
		int idxA = ( N - 1 ) / 2;
		int idxB = ( M - 1 ) / 2;
	 
		 /* if A[idxA] <= B[idxB], then median must exist in
			A[idxA....] and B[....idxB] */
		if( A[idxA] <= B[idxB] )
			return findMedianUtil( A + idxA, N / 2 + 1, B, M - idxA );
	 
		/* if A[idxA] > B[idxB], then median must exist in
		   A[...idxA] and B[idxB....] */
		return findMedianUtil( A, N / 2 + 1, B + idxA, M - idxA );
	}
};


