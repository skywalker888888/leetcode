/**
		Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
		You may assume that the intervals were initially sorted according to their start times.
		
		Example 1:
		Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

		Example 2:
		Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

		This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/
// pass 3
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
		// merge first
		bool bMerged = false;
		if(!intervals.size()) {
			intervals.push_back(newInterval);
			return intervals;
		}
		
		for(int i=0; i<intervals.size(); ++i) {
			if(intersect(intervals[i], newInterval)) {
				intervals[i].start = min(intervals[i].start, newInterval.start);
				intervals[i].end = max(intervals[i].end, newInterval.end);
				bMerged = true;
				break;
			} else if(newInterval.end<intervals[i].start) {
				intervals.insert(intervals.begin()+i, newInterval);
				break;
			} else if(i==intervals.size()-1) {
				intervals.insert(intervals.end(), newInterval);
				break;
			}
		}
		
		if(!bMerged)
			return intervals;
		
		// merge elements
		int i =0;
		int j = i+1;
		while(j < intervals.size()) {
			if(intersect(intervals[i], intervals[j])) {
				intervals[i].start = min(intervals[i].start, intervals[j].start);
				intervals[i].end = max(intervals[i].end, intervals[j].end);
			} else {
				intervals[i+1] = intervals[j];
				++i;
			}
			++j;
		}
		intervals.resize(i+1);
        return intervals;
    }
	
	bool intersect(Interval &interval1, Interval &interval2) {
		if(interval1.end<interval2.start || interval2.end<interval1.start)
			return false;
		return true;
	}
};
































// pass 2
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
		vector<Interval>::iterator itr = intervals.begin();
		vector<Interval>::iterator itrInResult = intervals.end();
		while(itr != intervals.end()) {
			Interval &itvl = *itr;
			// 
			Interval &cmpItvl = (itrInResult == intervals.end())?newInterval:*itrInResult;
			// if not overlap
			if(cmpItvl.end<itvl.start) {
				if(itrInResult == intervals.end()) {
					itr = intervals.insert(itr, newInterval);
					itrInResult = itr;
					++itr;
				} else
					break; // all done
			}
			else if(cmpItvl.start>itvl.end) {
				// ....
				++itr;
			} else {
				// overlapping
				if(itrInResult == intervals.end()) {
					itvl.start = min(itvl.start, cmpItvl.start);
					itvl.end = max(itvl.end, cmpItvl.end);
					itrInResult = itr;
					++itr;
				} else {
					cmpItvl.start = min(itvl.start, cmpItvl.start);
					cmpItvl.end = max(itvl.end, cmpItvl.end);
					itr = intervals.erase(itr);
				}
			}
		}
		if(itrInResult == intervals.end())
			intervals.insert(intervals.end(), newInterval);
		
		return intervals;
    }
};





































/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

 

class Solution {
public:
	vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
	{
		vector<Interval> result;
		int n = intervals.size();
		if(!n)
		{
			result.push_back(newInterval);
			return result;
		}
		
		int l, r;
		// find the left index that contains newInterval.start
		int nLeftIndex = 0;
		l = 0;
		r = n-1;
		while(l <= r)
		{
			int m = (l + r)/2;
			if(intervals[m].start < newInterval.start)
				l = m + 1;
			else if(intervals[m].start > newInterval.start)
				r = m - 1;
			else
			{
				nLeftIndex = m;
				break;
			}
		}
		if(l > r)
			nLeftIndex = l;
		
		// find the right index that contains newInterval.end
		
		int nRightIndex = 0;
		l = 0;
		r = n-1;
		bool bRightBetween = false;
		while(l <= r)
		{
			int m = (l + r)/2;
			if(intervals[m].end < newInterval.end)
				l = m + 1;
			else if(intervals[m].end > newInterval.end)
				r = m - 1;
			else
			{
				nRightIndex = m;
				break;
			}
		}
		if(l > r)
			nRightIndex = l;
			
		if(nRightIndex <= 0)
		{
			if(newInterval.end < intervals[0].start)
			{
				result.push_back(newInterval);
				result.insert(result.end(), intervals.begin(), intervals.end());
				return result;
			}
			else
			{
				result = intervals;
				result[0].start = min(newInterval.start, result[0].start);
				//result[0].end = max(newInterval.end, result[0].end);
				return result;
			}
		}
		if(nLeftIndex >= n)
		{
			result = intervals;
			if(result[n-1].end < newInterval.start)
				result.push_back(newInterval);
			else
				result[n-1].end = max(result[n-1].end, newInterval.end);
			return result;
		}
		
		
		
		if(nRightIndex < nLeftIndex)
		{
			// 1<= nRightIndex < nLeftIndex
			// here, nRightIndex must be nLeftIndex-1
			
			result = intervals;
			return result;
		}
		else
		{
			if(nLeftIndex <= 0)
			{
				if(nRightIndex >= n)
				{
					result.push_back(newInterval);
				}
				else
				{
					if(newInterval.end < intervals[nRightIndex].start)
					{
						result.push_back(newInterval);
						result.insert(result.end(), intervals.begin()+nRightIndex, intervals.end());
					}
					else
					{
						newInterval.end = intervals[nRightIndex].end;
						result.push_back(newInterval);
						result.insert(result.end(), intervals.begin()+nRightIndex+1, intervals.end());
					}
				}
			}
			else
			{
				if(newInterval.start > intervals[nLeftIndex-1].end)
				{
					result.insert(result.end(), intervals.begin(), intervals.begin()+nLeftIndex);
					if(nRightIndex >= n)
					{
						result.push_back(newInterval);
					}
					else
					{
						if(newInterval.end < intervals[nRightIndex].start)
						{
							result.push_back(newInterval);
							result.insert(result.end(), intervals.begin()+nRightIndex, intervals.end());
						}
						else
						{
							newInterval.end = intervals[nRightIndex].end;
							result.push_back(newInterval);
							result.insert(result.end(), intervals.begin()+nRightIndex+1, intervals.end());
						}
					}
				}
				else
				{
					result.insert(result.end(), intervals.begin(), intervals.begin()+nLeftIndex-1);
					newInterval.start = intervals[nLeftIndex-1].start;
					if(nRightIndex >= n)
					{
						result.push_back(newInterval);
					}
					else
					{
						if(newInterval.end < intervals[nRightIndex].start)
						{
							result.push_back(newInterval);
							result.insert(result.end(), intervals.begin()+nRightIndex, intervals.end());
						}
						else
						{
							newInterval.end = intervals[nRightIndex].end;
							result.push_back(newInterval);
							result.insert(result.end(), intervals.begin()+nRightIndex+1, intervals.end());
						}
					}
				}
			}
		}
		return result;
	}
};


int main(int argc, char **argv)
{

	Solution sol;
	// [1,5],[6,8]], [5,6]
	
	vector<Interval> intervals;
	Interval newInt(1, 5);
	Interval newInt2(6, 8);
	intervals.push_back(newInt);
	intervals.push_back(newInt2);

	Interval newInterval(5, 6);

	sol.insert(intervals, newInterval);

	return 0;
}
