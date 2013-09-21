/**
		Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

		Note: You may not slant the container.
*/
// pass 3
class Solution {
public:
    int maxArea(vector<int> &height) {
		int n = height.size();
		if(n < 2)
			return 0;
		
		int i=0; 
		int j = n-1;
		int result = min(height[i], height[j]) * (j-i);
		while(i < j) {
			int area = min(height[i], height[j]) * (j-i);
			result = max(result, area);
			
			if(height[i] > height[j])
				--j;
			else
				++i;
		}
		return result;
    }
};















































// pass 2
class Solution {
public:
    int maxArea(vector<int> &height) {
		int i = 0;
		int j = height.size() - 1;
		
		int result = min(height[i], height[j]) * (j-i);
		while(i < j) {
			int area = min(height[i], height[j]) * (j-i);
			if(area > result)
				result = area;
			if(height[i] > height[j])
				--j;
			else
				++i;
		}
		
		return result;
    }
};







































class Solution {
public:
	int maxArea(vector<int> &height)
	{
		int n = height.size();
		int i=0; 
		int j = n-1;
		int maxarea = 0;
		while(i<j) {
			int area = min(height[i], height[j]) * (j - i);
			if(area > maxarea)
				maxarea = area;
			
			if(height[i] <= height[j]) {
				int k = i+1;
				while(k<j && height[i]>=height[k])
					++k;
				i  = k;
			} else {
				int k = j-1;
				while(k>i && height[j]>=height[k])
					--k;
				j  = k;
			}
		}
		
		return maxarea;
	}
};





/////////////////// Better solution /////////////////
class Solution {
public:
	int maxArea(vector<int> &height) {
		int n = height.size();
		int i=0; 
		int j = n-1;
		int maxarea = 0;
		while(i<j) {
			int area = min(height[i], height[j]) * (j - i);
			if(area > maxarea)
				maxarea = area;
			
			if(height[i] < height[j])
				++i;
			else
				--j;
		}
		return maxarea;
	}
};



