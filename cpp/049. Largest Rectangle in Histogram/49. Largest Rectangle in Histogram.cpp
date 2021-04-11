/**
		Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

		       _
		     _| |
		    | | |
		    | | |  _
		 _  | | |_| |
		| |_| | | | |
		| | | | | | |

		Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
		The largest rectangle is shown in the shaded area, which has area = 10 unit.
		For example,
		Given height = [2,1,5,6,2,3],
		return 10.
		
*/
// pass 3
class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
    	int n = height.size();
		if(!n)
			return 0;
		
		// left[i]: the minimum indes which is higher than height[i]
		vector<int> left(n, 0);
		stack<int> stkLeft;
		for(int i=0; i<n; ++i) {
			while(!stkLeft.empty() && height[stkLeft.top()]>=height[i])
				stkLeft.pop();
			left[i] = stkLeft.empty()?0:stkLeft.top()+1;
			stkLeft.push(i);
		}
		
		// left[i]: the maximum indes which is higher than height[i], not including position i
		vector<int> right(n, 0);
		stack<int> stkRight;
		for(int i=n-1; i>=0; --i) {
			while(!stkRight.empty() && height[stkRight.top()]>=height[i])
				stkRight.pop();
			right[i] = stkRight.empty()?n-1:stkRight.top()-1;
			stkRight.push(i);
		}
		
		int nmax = 0;
		for(int i=0; i<n; ++i) {
			nmax = max(nmax, height[i] *(right[i]-left[i]+1));
		}
		
		return nmax;
    }
};


































/**
		There is a histogram with integer heights and constant width 1. I want to maximize the rectangular area under a histogram. e.g.:
		 _
		| |
		| |_ 
		|   |
		|   |_
		|     |
		
		The answer for this would be 6, 3 * 2, using col1 and col2.
		O(n^2) brute force is clear to me, I would like an O(n log n) algorithm. I'm trying to think dynamic programming along the lines of maximum increasing subsequence O(n log n) algo, but am not going forward. Should I use divide and conquer algorithm?
		PS: People with enough reputation are requested to remove the divide-and-conquer tag if there is no such solution.
		After mho's comments: I mean the area of largest rectangle that fits entirely. (Thanks j_random_hacker for clarifying :) ).
		
		See: http://blog.csdn.net/arbuckle/article/details/710988
		
		Problem H: Largest Rectangle in a Histogram
		Note that the area of the largest rectangle may exceed the largest 32-bit integer. Due to the large numbers of rectangles, the naive O(n^2) solution is too slow. Even though O(n*log(n)) or O(n) is required, there are several kinds of solutions to this problem. In the following, we will identify a histogram with the sequence of the heights of its rectangles.
		
		1. Divide-and-conquer using order-statistic trees. 
		Initially, build a binary, node- and leaf-labeled tree that contains the histogram as its frontier, i.e., as its leaves from left to right. Mark each inner node with the minimum of the labels of its subtree. Note that such a tree is most efficiently stored in an array using the heap data structure, where the children of node i are located at positions i*2 and i*2+1, respectively. With such an order-statistic tree, the minimum element in a subhistogram (i.e., a subsegment of the sequence of heights) can be found in O(log(n)) steps by using the additional information in the inner nodes to avoid searching all leaves. 
		To calculate the maximum rectangle under a subhistogram, we thus find the minimum height in that subhistogram, and divide it at just that place into two smaller histograms. The maximum rectangle is either completely in the left part, or completely in the right part, or it contains the rectangle with minimum height. The first two cases are solved recursively, while in the third case we know that the width of the maximum rectangle is the width of the whole subhistogram, since we chose the minimum height. Because every element serves exactly once as a place to divide, and we spend O(log(n)) for every division, the complexity of this algorithm is O(n*log(n)).
		2. Linear search using order-statistic trees. 
		Initially, construct an order-statistic tree as just described. For every element, we find the largest rectangle that includes that element. The height of the rectangle is, of course, the value of the element. Use the order-statistic tree to efficiently find the nearest elements that have smaller heights, both to the left and to the right. The width, and therefore the area of the rectangle can thus be calculated in O(log(n)) steps, giving a total runtime of O(n*log(n)).
		3. Sweeping line maintaining intervals. 
		Initially, sort the heights so they can be processed in non-increasing order. We sweep a horizontal line downwards through the histogram, maintaining a list of those intervals, where the line intersects the histogram. Actually, the intervals are maintained in an array with one entry for every element of the histogram in the following manner. At the element corresponding to the left end of an interval we store a pointer to the right end, and vice versa. 
		As a new element arrives during the sweeping process, this element forms a new interval, and, if there are adjacent intervals, these can be merged in constant time using our representation. The largest rectangle including this element, just as described in the previous algorithm, is available without further expense, since we can read its width from our representation. Actually, it is not quite the largest rectangle, because there may be further elements with equal heights adjacent to the current interval. Performing the sweep in a non-increasing order, however, guarantees that the largest rectangle will have been considered by the time the last element of a group having equal heights is examined. The complexity is dominated by the sorting phase, thus O(n*log(n)), although a radix sort is possible if the heights are bounded.
		4. Linear search using a stack of incomplete subproblems 
		We process the elements in left-to-right order and maintain a stack of information about started but yet unfinished subhistograms. Whenever a new element arrives it is subjected to the following rules. If the stack is empty we open a new subproblem by pushing the element onto the stack. Otherwise we compare it to the element on top of the stack. If the new one is greater we again push it. If the new one is equal we skip it. In all these cases, we continue with the next new element. 
		If the new one is less, we finish the topmost subproblem by updating the maximum area w.r.t. the element at the top of the stack. Then, we discard the element at the top, and repeat the procedure keeping the current new element. This way, all subproblems are finished until the stack becomes empty, or its top element is less than or equal to the new element, leading to the actions described above. If all elements have been processed, and the stack is not yet empty, we finish the remaining subproblems by updating the maximum area w.r.t. to the elements at the top. 
		For the update w.r.t. an element, we find the largest rectangle that includes that element. Observe that an update of the maximum area is carried out for all elements except for those skipped. If an element is skipped, however, it has the same largest rectangle as the element on top of the stack at that time that will be updated later. 
		The height of the largest rectangle is, of course, the value of the element. At the time of the update, we know how far the largest rectangle extends to the right of the element, because then, for the first time, a new element with smaller height arrived. The information, how far the largest rectangle extends to the left of the element, is available if we store it on the stack, too. 
		We therefore revise the procedure described above. If a new element is pushed immediately, either because the stack is empty or it is greater than the top element of the stack, the largest rectangle containing it extends to the left no farther than the current element. If it is pushed after several elements have been popped off the stack, because it is less than these elements, the largest rectangle containing it extends to the left as far as that of the most recently popped element. 
		Every element is pushed and popped at most once and in every step of the procedure at least one element is pushed or popped. Since the amount of work for the decisions and the update is constant, the complexity of the algorithm is O(n) by amortized analysis.
		5. Recursive search 
		For a recursive version of the algorithm just described, see the reference below. Indeed, if the recursion is eliminated the necessary stack is analogous to the explicit stack in the iterative version.
		6. Rewrite System 
		The problem may be generalized by allowing histograms to be composed of rectangles with varying widths. Then, the stack used in the just described algorithms can be concatenated with the yet unprocessed part of the histogram into one list. 
		A three element window is moved over this list, starting at the left end. In every step, different actions are performed according to the relative heights of the three elements under inspection. The actions include updating the maximum, merging two of the three elements by taking the minimum of their heights and the sum of their widths, and sliding the window one element to the left or to the right. Rules are provided that specify the actions for each configuration. 
		Actually, the behaviour of the stack-based algorithm is simulated. The correctness of the rewrite system can be shown by proving an invariant about the maximum area of the histogram, observing that every configuration is matched by some rule, and giving a termination proof using a variant expression. Additionally, it can be proved that O(n) rewrite steps (each with a constant amount of work) are performed.
		Judges' test data consisted of 32 hand-crafted test cases, 33 randomly generated test cases, and one test case with a histogram of width 99998.
		Rating: Hard
		Reference
		Morgan, C. 
		Programming from Specifications 
		Chapter 21, pages 209-216, Prentice Hall International (UK) Limited, second edition, 1994 
		ISBN 0-13-123274-6
		
		
		See also: 48. Maximal Rectangle
*/
// pass 2
class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
		int n = height.size();
		if(!n)
			return 0;
		// calculate left side
		vector<int> vtrLeft(n, 0);
		stack<int> stkLeft;
		for(int i=0; i<n; ++i) {
			while(!stkLeft.empty() && height[stkLeft.top()]>=height[i])
				stkLeft.pop();
			vtrLeft[i] = (!stkLeft.empty())?: (i-stkLeft.top()-1):i;
			stkLeft.push(i);
		}
		
		// right side
		vector<int> vtrRight(n, 0);
		stack<int> stkRight;
		for(int i=n-1; i>=0; --i) {
			while(!stkRight.empty() && height[stkRight.top()]>=height[i])
				stkRight.pop();
			vtrRight[i] = (!stkRight.empty())?(stkRight.top()-i-1):(n-i-1);
			stkRight.push(i);
		}
		
		int maxArea = (vtrLeft[0]+vtrRight[0]+1) * height[0];
		for(int i=1; i<n; ++i)
			maxArea = max(maxArea, (vtrLeft[i]+vtrRight[i]+1) * height[i]);
		return 	maxArea;
    }
};






























class Solution
{
public:
    int largestRectangleArea(vector<int> &height);
    int largestRectangleArea2(vector<int> &height);
    int largestRectangleArea3(vector<int> &height);
private:
	void calculateLeftAdjacentColumnNumber(vector<int> &height, vector<int> &leftCols);
	void calculateRightAdjacentColumnNumber(vector<int> &height, vector<int> &rightCols);
};


/**
	For each column i, we calculate the left and right adjacent columnum number. Then we can get the interval wich includes the column i. So the maximum area are the interval withth * the hight(i)
 */
int Solution::largestRectangleArea(vector<int> &height)
{
	if(!height.size())
		return 0;
		
	vector<int> leftCols(height.size(), 0);
	calculateLeftAdjacentColumnNumber(height, leftCols);
	
	vector<int> rightCols(height.size(), 0);
	calculateRightAdjacentColumnNumber(height, rightCols);
	
	int nMax = 0;
	for(int i=0; i<height.size(); ++i)
	{
		int nCount = 1;
		nCount += leftCols[i];
		nCount += rightCols[i];
		
		int nNum = nCount * height[i]; 
		if(nMax < nNum)
			nMax = nNum;
	}
	return nMax;
}


/**
	Use a stack to save the columns to the  left which are higher than the current column. 
	When we see the current column height is bigger than the left adjacent column, clear the stack
 */
void Solution::calculateLeftAdjacentColumnNumber(vector<int> &height, vector<int> &leftCols)
{
	stack<int> stkRec;
	for(int i=0; i<height.size(); ++i)
	{
		// the stack keeps all the items to the left which hight is smaller than column i
		// here, we remove all the bars which is higher than column i
		while(!stkRec.empty() && height[i]<=height[stkRec.top()])
		{
			stkRec.pop();
		}
		// when stack is empty, means all the items to the left are bigger than this one, so we set i to leftCols
		if(stkRec.empty())
			leftCols[i] = i;
		else
		{
			// the top of stack is the first element which value is smaller than this item
			int n = stkRec.top();
			leftCols[i] = i-n-1; // to the left and not including this item itself
		}
		
		// put current bar into the stack
		stkRec.push(i);
	}
}


/**
	Use a stack to save the columns to the  right which are higher than the current column. 
	When we see the current column height is bigger than the right adjacent column, clear the stack
 */
void Solution::calculateRightAdjacentColumnNumber(vector<int> &height, vector<int> &rightCols)
{
	stack<int> stkRec;
	for(int i=height.size()-1; i>=0; --i)
	{
		// remove all the items which are higher than this item
		while(!stkRec.empty() && height[i]<=height[stkRec.top()])
			stkRec.pop();
		
		// it stack is empty, all items to the right are smaller than this item
		if(stkRec.empty())
			rightCols[i] = height.size() - i - 1;
		else
		{
			int n = stkRec.top();
			rightCols[i] = n - i - 1;
		}
		stkRec.push(i);
	}
}


/**
	Use DP :
	Basic idea: use the n*n matrix dp[i][j] to cache the minimal height between bar[i] and bar[j]. Start filling the matrix from rectangles of width 1.
 */
int Solution::largestRectangleArea2(vector<int> &height)
{
	int n = height.size();
	if(!n)
		return 0;
	
	int nMax = 0;
	vector<vector<int> > matrix(height.size(), vector<int>(height.size(), 0));
	for(int nWidth=0; nWidth<n; ++nWidth)
		for(int i=0; i<n-nWidth; ++i)
		{
			int j = i + nWidth;
			if(i == j)
				matrix[i][j] = height[i];
			else
				matrix[i][j] = min(height[j], matrix[i][j-1]); 
				
			nMax = max(nMax, matrix[i][j]*(j-i+1)); 
		}
		
	return nMax;
}


/**
	time: O(n^2), space: O(n)

	Basic idea: this solution is like solution 1, but saves some space. The idea is that in solution 1 we build the matrix from row 1 to row n. But in each iteration, only the previous row contributes to the building of the current row. So we use two arrays as previous row and current row by turns.
 */
int Solution::largestRectangleArea3(vector<int> &height)
{
	int n = height.size();
	if(!n)
		return 0;
	
	int nMax = 0;
	vector<int> row1(height.size(), 0);
	vector<int> row2(height.size(), 0);
	
	for(int nWidth=0; nWidth<n; ++nWidth)
	{
		for(int i=0; i<n-nWidth; ++i)
		{
			int j = i + nWidth;
			if(i == j)
			{
				//matrix[i][j] = height[i];
				row1[i] = height[i];
				nMax = max(nMax, row1[i]*(j-i+1)); 
			}
			else
			{
				//matrix[i][j] = min(height[j], matrix[i][j-1]); 
				row2[j] = min(height[j], row1[j-1]);
				nMax = max(nMax, row2[j]*(j-i+1)); 
			}
		}
		
		if(nWidth)
			row1 = row2;
	}	
	return nMax;
}