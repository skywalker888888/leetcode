/**
		Given an array of integers, find two numbers such that they add up to a specific target number.

		The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

		You may assume that each input would have exactly one solution.

		Input: numbers={2, 7, 11, 15}, target=9
		Output: index1=1, index2=2
*/
// pass 3
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
		unordered_map<int, int> M;
		for(int i=0; i<numbers.size(); ++i) {
			M[numbers[i]] = i;
		}
		for(int i=0; i<numbers.size(); ++i) {
			int num1 = numbers[i];
			int num2 = target-num1;
			if(M.find(num2) != M.end()) {
				int ind1 = i+1;
				int ind2 = M[num2]+1;
				if(ind1 != ind2) {
					vector<int> result;
					result.push_back(min(ind1, ind2));
					result.push_back(max(ind1, ind2));
					return result;
				}
			}
		}
		return vector<int>(2, -1);
    }
};








































// pass 2
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
		vector<int> result;
		unordered_map<int, int> val2ind;
		for(int i=0; i<numbers.size(); ++i)
			val2ind[numbers[i]] = i+1;
		for(int i=0; i<numbers.size(); ++i) {
			if(val2ind.find(target-numbers[i])!=val2ind.end() && val2ind[target-numbers[i]]!=i+1) {
				result.push_back(min(i+1, val2ind[target-numbers[i]]));
				result.push_back(max(i+1, val2ind[target-numbers[i]]));
				break;
			}
		}
		return result;
    }
};









































struct itemRecord {
	int index;
	int val;
	itemRecord(int i, int v): index(i), val(v) {}
};
bool itemRecordLess(itemRecord i1, itemRecord i2) {
	return i1.val < i2.val;
}
class Solution {
public:
	vector<int> twoSum(vector<int> &numbers, int target) {
		vector<int> result;
		int n = numbers.size();
		
		vector<itemRecord> numRecords;
		for(int i=0; i<n; ++i)
			numRecords.push_back(itemRecord(i, numbers[i]));
		sort(numRecords.begin(), numRecords.end(), itemRecordLess);
			
		for(int i=0; i<n; ++i) {
			int num = target - numRecords[i].val;
			int ind = binarySearch(numRecords, i+1, n-1, num);
			if(ind > i) {
				if(numRecords[i].index > numRecords[ind].index) {
					result.push_back(numRecords[ind].index+1);
					result.push_back(numRecords[i].index+1);
				} else {
					result.push_back(numRecords[i].index+1);
					result.push_back(numRecords[ind].index+1);
				}
				return result;
			}
		}
		return result;
	}
	int	binarySearch(vector<itemRecord> &numbers, int i, int j, int target) {
		while(i <= j) {
			int m = (i+j)/2;
			if(target == numbers[m].val)
				return m;
			else if(target > numbers[m].val)
				i = m + 1;
			else
				j = m - 1;
		}
		return -1;
	}
};


