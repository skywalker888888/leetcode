/**
		Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
		For example,
		Given [100, 4, 200, 1, 3, 2],
		The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
		Your algorithm should run in O(n) complexity.
*/
// pass 3
class Solution {
public:
    int longestConsecutive(vector<int> &num) {
		unordered_set<int> hashSetNums;
		for(int i=0; i<num.size(); ++i)
			hashSetNums.insert(num[i]);
		
		int result = 0;
		while(!hashSetNums.empty()) {
			int i = *(hashSetNums.begin());
			int count = 0;
			for(int k=i; hashSetNums.find(k)!=hashSetNums.end(); --k) {
				hashSetNums.erase(k);
				++count;
			}
			for(int k=i+1; hashSetNums.find(k)!=hashSetNums.end(); ++k) {
				hashSetNums.erase(k);
				++count;
			}
			
			result = max(result, count);
		}
		return result;
    }
};

































/**
		Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
		For example,
		Given [100, 4, 200, 1, 3, 2],
		The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
		Your algorithm should run in O(n) complexity.
		
		Use hash table, java implement:
			using System;
			using System.Collections.Generic;
			using System.Linq;

			class Test
			{
				static void Main(string[] args)
				{
					int[] input = {10,21,45,22,7,2,67,19,13,45,12,
							11,18,16,17,100,201,20,101};

					HashSet<int> values = new HashSet<int>(input);

					int bestLength = 0;
					int bestStart = 0;
					// Can't use foreach as we're modifying it in-place
					while (values.Count > 0)
					{
						int value = values.First();
						values.Remove(value);
						int start = value;
						while (values.Remove(start - 1))
						{
							start--;
						}
						int end = value;
						while (values.Remove(end + 1))
						{
							end++;
						}

						int length = end - start + 1;
						if (length > bestLength)
						{
							bestLength = length;
							bestStart = start;
						}
					}
					Console.WriteLine("Best sequence starts at {0}; length {1}",
									  bestStart, bestLength);
				}
			}
 */
// pass 2
class Solution {
public:
    int longestConsecutive(vector<int> &num) {
    	unordered_set<int> data(num.begin(), num.end());
		int result = 0;
		
		while(!num.empty()) {
            int nMin, nMax;
			// remove the segments which includes num[0];
			nMin = nMax = num[num.size()-1];
			num.pop_back();
            unordered_set<int>::iterator itr;
			while((itr=data.find(nMax+1)) != data.end()) {
				data.erase(itr);
				++nMax;
			}
			while((itr=data.find(nMin-1)) != data.end()) {
				data.erase(itr);
				--nMin;
			}
			result = max(result, nMax-nMin+1);
		}
		return result;
    }
};




























// pass 1
class Solution {
public:
	int longestConsecutive(vector<int> &num) {
		int rag = 0;
		set<int> nums(num.begin(), num.end());  // use hashset for O(n). Here, it is O(n lg n)
		
		while(!nums.empty()) {
			int nmax, nmin;
			nmin = nmax = *nums.begin();
			nums.erase(nums.begin());
			
			set<int>::iterator itr;
			while((itr=nums.find(nmax+1)) != nums.end()) {
				++nmax;
				nums.erase(itr);
			}
			while((itr=nums.find(nmin-1)) != nums.end()) {
				--nmin;
				nums.erase(itr);
			}
			rag = max(rag, nmax-nmin+1);
		}
		return rag;
	}
};





http://blog.sina.com.cn/s/blog_b9285de20101iqar.html
int getCount(Set<Integer> hs, int v, boolean asc){
	int count=0;
	while(hs.contains(v)){
		hs.remove(v);
		count++;
		if(asc) v++; else v--;
	}
	return count;
}

public int longestConsecutive(int[] num) {
	Set<Integer> hs=new HashSet<Integer>();
	for(int v:num) hs.add(v);
	int ans=0;
	
	for(int v:num) 
		if(hs.contains(v)) 
			ans=Math.max(ans, getCount(hs, v, false)+getCount(hs, v+1, true));
	return ans; 
}
