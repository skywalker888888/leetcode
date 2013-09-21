/**
		Given two binary strings, return their sum (also a binary string).

		For example,
		a = "11"
		b = "1"
		Return "100".
*/
// pass 3
class Solution {
public:
    string addBinary(string a, string b) {
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		
		stringstream ss;
		int carry = 0;
		int i = 0;
		while(i<a.size() && i<b.size()) {
			int value = (a[i]-'0') + (b[i]-'0') + carry;
			ss.put(value%2 + '0');
			carry = value/2;
			++i;
		}
		
		string &c = (i<a.size())?a:b;
		while(i < c.size() ){
			int value = (c[i]-'0')+ carry;
			ss.put(value%2 + '0');
			carry = value/2;
			++i;
		} 
		if(carry)
			ss.put(carry + '0');
		string result = ss.str();
		reverse(result.begin(), result.end());
		return result;
    }
};











































// pass 2
class Solution {
public:
    string addBinary(string a, string b) {
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		
		string result;
		int i = 0; 
		int j = 0;
		int carry = 0;
		while(i<a.size() && j<b.size()) {
			int val1 = a[i] - '0';
			int val2 = b[j] - '0';
			int valsum = val1 + val2 + carry;
			result.push_back('0' + valsum%2);
			carry = valsum/2;
			++i;
			++j;
		}
		
		string &remainder = i<a.size()?a:b;
		int remainderindex = i<a.size()?i:j;
		int indexmax = i<a.size()?a.size():b.size();
		while(remainderindex < indexmax) {
			int val = remainder[remainderindex] - '0' + carry;
			result.push_back('0' + val%2);
			carry = val/2;
			++remainderindex;
		}
		if(carry)
			result.push_back('0' + carry);
		
		reverse(result.begin(), result.end());
		return result;
    }
};









































class Solution {
public:
    string addBinary(string a, string b);
};


string Solution::addBinary(string a, string b)
{
	string result;
	
	reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());	
	
	string::iterator itra = a.begin();
	string::iterator itrb = b.begin();
	bool bCarry = false;
	while(true)
	{
		int nval = 0;
		if(itra!=a.end())
			nval += *(itra++) - '0';
		if(itrb!=b.end())
			nval += *(itrb++) - '0';
		
		if(bCarry)
			++nval;
		bCarry = nval/2;
		result.push_back('0' + nval%2);
		
		if(itra==a.end() && itrb==b.end())
		{
			if(bCarry) result.push_back('1');
			break;
		}
	}
	
	reverse(result.begin(), result.end());
	return result;
}

