/**
		The count-and-say sequence is the sequence of integers beginning as follows:
		1, 11, 21, 1211, 111221, ...

		1 is read off as "one 1" or 11.
		11 is read off as "two 1s" or 21.
		21 is read off as "one 2, then one 1" or 1211.
		Given an integer n, generate the nth sequence.

		Note: The sequence of integers will be represented as a string.
*/
//  pass 3
class Solution {
public:
    string countAndSay(int n) {
    	vector<vector<int> > M(2);
		M[0].push_back(1);
		int flag = 1;
		for(int i=2; i<=n; ++i) {
			M[flag].clear();
			int ind = 0;
			while(ind < M[!flag].size()) {
				int j = ind+1;
				while(j<M[!flag].size() && M[!flag][j]==M[!flag][ind])
					++j;
				int count = j-ind;
				int tag = 1;
				while(tag * 10 <= count)
					tag *= 10;
				while(tag) {
					M[flag].push_back(count/tag);
					count %= tag;
					tag /= 10;
				}
				M[flag].push_back(M[!flag][ind]);
				ind = j;
			}
			flag = !flag;
		}
		string result;
		for(int i=0; i<M[!flag].size(); ++i)
			result.push_back('0' + M[!flag][i]);
		return result;
    }
};







































// pass2
class Solution {
public:
    string countAndSay(int n) {
		vector<vector<int> > vctr(2);
		vctr[0].push_back(1);
		int flag = 1;
		for(int i=0; i<n-1; ++i) {
			vctr[flag].clear();
			int ind = 0;
			while(ind < vctr[!flag].size()) {
				int cnt = 1;
				for(int j=ind+1; j<vctr[!flag].size()&&vctr[!flag][j]==vctr[!flag][ind]; ++j, ++cnt) ;
				stack<int> vals;
				int count = cnt;
				while(cnt) {
					vals.push(cnt%10);
					cnt /= 10;
				}
				while(!vals.empty()) {
					vctr[flag].push_back(vals.top());
					vals.pop();
				}
				vctr[flag].push_back(vctr[!flag][ind]);
				ind += count;
			}
			flag = !flag;
		}
		
		string result;
		for(int i=0; i<vctr[!flag].size(); ++i)
			result.push_back(vctr[!flag][i] + '0');
			
		return result;
    }
};





































class Solution {
public:
	string countAndSay(int n)
	{
		string result = "1";
		for(int i=0; i<n-1; ++i)
		{
			string str = sayString(result);
			result = str;
		}
			
		return result;
	}

	string sayString(string str)
	{
		string result;
		
		int n = str.size();
		for(int i=0; i<n; )
		{
			char ch = str[i];
			int count = 0;
			int j=i;
			for(; j<n && ch==str[j]; ++j)
				++count;
			
			assert(count < 10);
			
			result.append(1, '0'+count);
			result.append(1, ch);
			i = j;
		}
		return result;
	}
};

