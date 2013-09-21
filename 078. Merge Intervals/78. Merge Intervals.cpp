/**
		Given a collection of intervals, merge all overlapping intervals.

		For example,
		Given [1,3],[2,6],[8,10],[15,18],
		return [1,6],[8,10],[15,18].	
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
    vector<Interval> merge(vector<Interval> &intervals) {
		int i = 0;
		while(i < intervals.size() ) {
			int j = i+1;
			bool bMerged = false;
			vector<Interval>::iterator itr = intervals.begin() + i + 1;
			while(itr != intervals.end())
				if(intersect(intervals[i], *itr)) {
					intervals[i].start = min(intervals[i].start, itr->start);
					intervals[i].end = max(intervals[i].end, itr->end);
					bMerged = true;
					itr = intervals.erase(itr);
				} else {
					++itr;
				}
			if(!bMerged)
				++i;
		}
		
		return intervals;
    }
	bool intersect(Interval &int1, Interval& int2) {
		if(int1.end<int2.start || int2.end<int1.start)
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
    vector<Interval> merge(vector<Interval> &intervals) {
		vector<Interval>::iterator itr = intervals.begin();
		while(itr != intervals.end()) {
			Interval &val1 = *itr;
			bool bMerged = false;
			vector<Interval>::iterator itrLast = itr+1;
			while(itrLast != intervals.end()) {
				Interval &val2 = *itrLast;
				if(val1.start>val2.end || val2.start>val1.end) {
					++itrLast;
				} else {
					val1.start = min(val1.start, val2.start);
					val1.end = max(val1.end, val2.end);
					bMerged = true;
					itrLast = intervals.erase(itrLast);
				}
			}
			
			if(!bMerged)
				++itr;
		}
		
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
class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals);
};

vector<Interval> Solution::merge(vector<Interval> &intervals)
{
	vector<Interval>::iterator itr = intervals.begin();
	while(itr != intervals.end())
	{
		Interval &itm = *itr;
		vector<Interval>::iterator itr2 = itr+1;
		bool bMerged = false;
		while(itr2 != intervals.end())
		{
			Interval itm2 = *itr2;
			if(itm2.start<=itm.end && itm2.end>=itm.start || itm.start<=itm2.end && itm.end>=itm2.start)
			{
				itm.start = min(itm.start, itm2.start);
				itm.end = max(itm.end, itm2.end);
				itr2 = intervals.erase(itr2);
				bMerged = true;
			}
			else 
				++itr2;
		}
		
		if(!bMerged)
			++itr;
	}
	
	return intervals;
	
}

