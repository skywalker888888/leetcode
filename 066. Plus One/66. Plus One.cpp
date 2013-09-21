/**
		Given a number represented as an array of digits, plus one to the number.
*/
// pass 3
class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
		reverse(digits.begin(), digits.end());
		int carry = 1;
		for(int i=0; i<digits.size(); ++i) {
			digits[i] += carry;
			carry = digits[i]/10;
			digits[i] %= 10;
		}
		
		if(carry)
			digits.push_back(carry);
		reverse(digits.begin(), digits.end());
		return digits;
	}
};





















































// pass 2
class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
		if(digits[digits.size()-1] < 9) {
			++digits[digits.size()-1];
			return digits;
		}
		
    	reverse(digits.begin(), digits.end());
		int carry = 1;
        int i = 0;
		for(; i<digits.size(); ++i) {
			digits[i] += carry;
			if(digits[i] >= 10) {
				carry = digits[i]/10;
				digits[i] %= 10;
			} else 
				break;
		}
		
		if(i==digits.size() && carry)
			digits.push_back(carry);
		reverse(digits.begin(), digits.end());
		return digits;
    }
};











































class Solution{
public:
	vector<int> plusOne(vector<int> &digits)
	{
		int i = 0;
		for(i=digits.size()-1; i>=0; --i) {
			if(digits[i] < 9)
				break;
		}
		
		if(i < 0) {
			vector<int> result(digits.size() + 1, 0);
			result[0] = 1;
			return result;
		}
		
		vector<int> result(digits);
		++result[i];
		++i;
		for(; i< digits.size(); ++i)
			result[i] = 0;
		
		return result;
	}

};



