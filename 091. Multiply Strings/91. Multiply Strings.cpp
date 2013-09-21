/**
		Given two numbers represented as strings, return multiplication of the numbers as a string.

		Note: The numbers can be arbitrarily large and are non-negative.
*/
// pass 3
class Solution {
public:
    string multiply(string num1, string num2) {
    	if(num1=="0" || num2=="0")
			return "0";
		if(num1 == "1")
			return num2;
		if(num2 == "1")
			return num1;
		
		reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		
		vector<long> result;
		for(int i=0; i<num1.size(); ++i) {
			for(int j=0; j<num2.size(); ++j) {
				long v1 = num1[i] - '0';
				long v2 = num2[j] - '0';
				
				long prod = v1 * v2;
				if(result.size() < i+j+1)
					result.push_back(0);
				result[i+j] += prod;
			}
		}
		
		string res;
		long carry = 0;
		for(int i=0; i<result.size(); ++i) {
			long num = result[i] + carry;
			res.push_back('0' + num%10);
			carry = num/10;
		}
		while(carry) { 
			res.push_back('0' + carry%10);
			carry /= 10;
		}
		
		reverse(res.begin(), res.end());
		return res;
    }
};














































// pass 2
class Solution {
public:
    string multiply(string num1, string num2) {
		if(num1=="0" || num2=="0")
			return "0";
		else if(num1=="1" || num2=="1")
			return (num1=="1")?num2: num1;
		
    	reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		
		vector<int> result_int;
		for(int i=0; i<num1.size(); ++i) {
			int n1 = num1[i] - '0';
			for(int j=0; j<num2.size(); ++j) {
				int n2 = num2[j] - '0';
				int prod = n1 * n2;
				if(result_int.size() < i+j+1) {
					result_int.resize(i+j+1);
					result_int[i+j] = 0;
				}
				result_int[i+j] += prod;
			}
		}
		
		int carry = 0;
		for(int i=0; i<result_int.size(); ++i) {
			result_int[i] += carry;
			carry = result_int[i]/10;
			result_int[i] %= 10;
		}
		while(carry) {
			result_int.push_back(carry%10);
			carry /= 10;
		}
		
		reverse(result_int.begin(), result_int.end());
#if 1
		stringstream ss; 
		for(int i=0; i<result_int.size(); ++i) {
			ss.put(result_int[i]+'0');
		}
		return ss.str();
#else
		string res;
		for(int i=0; i<result_int.size(); ++i) {
			res.push_back(result_int[i]+'0');
		}
		
		return res;
#endif
	}
};










































class Solution {
public:
	string multiply(string num1, string num2)
	{
		int len1 = num1.size();
		int len2 = num2.size();
		
		if(!len1 || !len2 || len1==1&&num1[0]=='0' ||len2==1&&num2[0]=='0')
			return "0";
		
		if(len1==1 && num1[0] == '1')
			return num2;
		if(len2==1 && num2[0] == '1')
			return num1;
		
		vector<int> sum(len1 + len2, 0);
		//reverse(num2.begin(), num2.end());
		
		int nmax = 0x1<<20;
		for(int i=num2.size()-1; i>=0; --i)
		{
			int a = num2[i] - '0';
			bool bDoReorganize = false;
			for(int j=num1.size()-1; j>=0; --j)
			{
				int b = num1[j] - '0';
				
				int pos = (num2.size()-1-i) + (num1.size()-1-j);
				
				int s = a*b;
				sum[pos] += s;
				
				if(sum[i+j] > nmax)
					bDoReorganize = true;
			}
			if(bDoReorganize)
				reorganizeSumArray(sum);
		}
		reorganizeSumArray(sum);
		reverse(sum.begin(), sum.end());
		int i = 0;
		while(!sum[i] && i<sum.size())
			++i;
		
		string result;
		for(; i<sum.size(); ++i)
		{
			char ch = sum[i] + '0';
			result.push_back(ch);
		}
		return result;
	}

	void reorganizeSumArray(vector<int> &sum)
	{
		//reverse(sum.begin(), sum.end());
		for(int i=0; i<sum.size()-1; ++i)
		{
			sum[i+1] += sum[i]/10;
			sum[i] %= 10;
		}
		//reverse(sum.begin(), sum.end());
	}
};



class Solution {
public:
	string multiply2(string num1, string num2)
	{
		if(num2.size()==1)
			if(num2[0]=='0')
				return "0";
			else if(num2[0]=='1')
				return num1;
			else
			{
				int carry = 0;
	#if 0
				reverse(num1.begin(), num1.end());
				for(int i=0; i<num1.size(); ++i)
				{
					int a = num1[i] - '0';
					int b = num2[0] - '0';
					int c = a*b + carry;
					
					int c1 = c%10;
					carry = c/10;
					
					num1[i] = c1 + '0';
				}
				
				if(carry > 0)
					num1.push_back(carry + '0');
				reverse(num1.begin(), num1.end());
	#else
				for(int i=num1.size()-1; i>=0; --i)
				{
					int a = num1[i] - '0';
					int b = num2[0] - '0';
					int c = a*b + carry;
					
					int c1 = c%10;
					carry = c/10;
					
					num1[i] = c1 + '0';
				}
				
				if(carry > 0)
					num1 = string(1, carry + '0') + num1;
	#endif
				
				return num1;
			}
		else
		{
			string sum = "0";
			reverse(num2.begin(), num2.end());
			for(int i=0; i<num2.size(); ++i)
			{
				//string s1 = multiply(num1, num2[i]);
				string s1 = multiply(num1, string(1, num2[i]));
				
				// sum = sum*10 + s1
				if(sum.size()>1 || sum[0]!='0')
					sum.push_back('0');
				reverse(sum.begin(), sum.end());
				reverse(s1.begin(), s1.end());
				// sum
				int carry = 0;
				for(int i=0; i<s1.size(); ++i)
				{
					if(i<sum.size())
					{
						int a = sum[i] - '0';
						int b = s1[i]-'0';
						
						int s = a + b + carry;
						
						carry = s / 10;
						sum[i] = s%10 + '0';
					}
					else
					{
						int b = s1[i]-'0';
						int s = b + carry;
						
						carry = s / 10;
						sum.push_back(s%10 + '0');
					}
					
					if(carry)
						sum.push_back(carry + '0');
				}
				
				reverse(sum.begin(), sum.end());
			}
		}
	}
};

