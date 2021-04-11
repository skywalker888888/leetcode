/**
		Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

		For example,
		If n = 4 and k = 2, a solution is:

		[
		  [2,4],
		  [3,4],
		  [2,3],
		  [1,2],
		  [1,3],
		  [1,4],
		]
*/
// pass 3

class Solution {
public:
	vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > result;
        result.clear();
        vector<int> combination;
        combineHeler(n, k, 1, combination, result);
        return result;
    }

    void combineHeler(int n, int k, int i, vector<int> combination, vector<vector<int> > &result) {
        if (combination.size() == k) {
            result.push_back(combination);
            return;
        }
        if (i == n + 1) return;
        combineHeler(n, k, i + 1, combination, result);
        combination.push_back(i);
        combineHeler(n, k, i + 1, combination, result);
    }
};
	
	
// non-recursion
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
		vector<vector<int> > result;
		if(n < k)
			return result;
		vector<int> values(k, 0);
		for(int i=1; i<=k; ++i)
			values[i-1] = i;
		// start to count
		int index = k-1;
		while(values[0] <= n) {
			if(values[index] <= n) {
				if(index == k-1) {
					vector<int> item;
					for(int i=0; i<k; ++i)
						item.push_back(values[i]);
					result.push_back(item);
					++values[index];
				} else {
					values[index+1] = values[index] + 1;
					++index;
				}
			} else if(index > 0) {
				++values[index-1];
				--index;
			}
		}
		return result;
	}
};

// recursion
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
		vector<vector<int> > result;
		if(m < k)
			return result;
		
		combine(1, n, k, result); 
    }
	
	void combine(int i, int j, int k, vector<vector<int> > &result) {
		if(j-i+1 < k)
			return;
		else if(k == 1) {
			for(int p=i; p<=j; ++p) {
				vector<int> item(1, p);
				result.push_back(item);
			}
			return;
		}
		} else {
			vector<vector<int> > r1;
			combine(i, j-1, k, r1);
			result.insert(result.end(). r1.begin(), r1.end());
			
			vector<vector<int> > r2;
			combine(i, j-1, k-1, r2);
			for(int p=0; p<r2.size(); ++p) {
				r2[p].push_back(j);
				result.push_back(r2[p]);
			}
		}
	}
};



































// pass 2
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
		vector<vector<int> > result;
		
		if(k>n || k<=0 || n<=0)
			return result;
		
		vector<int> values(k, 0);
		int index = 0;
		values[0] = 1;
		while(true) {
			if(values[0] > n)
				break;
			if(values[index] > n){
				if(!index)
					break;
				else {
					--index;
					++values[index];
				}
			} else if(index == k-1) {
				result.push_back(values);
				++values[index];
			} else {
				values[index+1] = values[index] + 1;
				// immediately go to state ind+1
				++index;
			}
		}
		
		return result;
	}
};

// Non-recursion.
class Solution {
public:
	/*
		make an array values[k], fill in numbers in this array till a valid item is in place
		Then, add the item to result 
	*/
    vector<vector<int> > combine(int n, int k) {
		vector<vector<int> > result;
		
		if(k>n || k<=0 || n<=0)
			return result;
		
		vector<int> values(k, 0);
		int index = 0;
		values[0] = 1;
		while(true) {
			// if all values are in place, add it to result
			if(values[0] > n)
				break;
			
			if(index == k-1) {
				result.push_back(values);
				while(index>=0 && values[index]>=n)
					--index;
				if(index < 0)
					break;
				++values[index];
			} else {
				// Fill the value for next slot, and continue to next slot
				values[index+1] = values[index] + 1;
				++index;
				if(values[index] > n) {
					while(index>=0 && values[index]>=n)
						--index;
					if(index < 0)
						break;
					++values[index];
				}
			}
		}
    }
};

// Recursion
class Solution {
public:
	// Total number should be C(n, k)
	// Use DP to make it polynormial time
    vector<vector<int> > combine(int n, int k) {
		vector<vector<int> > result;
		if(k>n || n<=0)
			return result;
		
		if(k == 1) {
			for(int i=1; i<=n; ++i) {
				result.resize(result.size()+1);
				result[result.size()-1].push_back(i);
			}
			return result;
		}
		// to calculate all items include n
		vector<vector<int> > res1 = combine(n-1, k-1);
		for(int i=0; i<res1.size(); ++i)
			res1[i].push_back(n);
		result.insert(result.end(), res1.begin(), res1.end());
	
		// to calculate all itmes not including n
		res1 = combine(n-1, k);
		result.insert(result.end(), res1.begin(), res1.end());
		
		return result;
    }
};
































class Solution {
public:
	vector<vector<int> > combine(int n, int k) {
		vector<vector<int> > result;
		if( n < k )
			return result;
		
		if( !k ) {
			result.resize(1);
			return result;
		}
		if(n == k) {
			result.resize(1);
			for(int i=1; i<=n; ++i)
				result[0].push_back(i);
			return result;
		}
				
		// take n
		vector<vector<int> > res = combine(n-1, k-1);
		for(int i=0; i<res.size(); ++i) {
			vector<int> item = res[i];
			item.push_back(n);
			result.push_back(item);
		}
		
		res = combine(n-1, k);
		for(int i=0; i<res.size(); ++i) {
			vector<int> item = res[i];
			if(item.size())
				result.push_back(item);
		}
		
		return result;
	}
};



class Solution {
public:
	/**
		Use state machine
	 */
	vector<vector<int> > combine(int n, int k)
	{
		vector<vector<int> > result;
		if( n < k )
			return result;
		
		if( !k ) {
			result.resize(1);
			return result;
		}
		if(n == k) {
			result.resize(1);
			for(int i=1; i<=n; ++i)
				result[0].push_back(i);
			return result;
		}

		vector<int> indices(k, 0);
		indices[0] = 1;
		int ind = 0;
		while(true) {
			// state ind
			if(indices[ind] > n) {
				if(!ind)
					break;
				// go to state ind-1
				--ind;
				++indices[ind];
				continue;
			}		
			
			if(ind == k-1) {
				result.push_back(indices);
				++indices[ind];
				continue;
			}
			
			indices[ind+1] = indices[ind] + 1;
			// immediately go to state ind+1
			++ind;
		}
	}
};



