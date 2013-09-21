/**
		Given a roman numeral, convert it to an integer.
		Input is guaranteed to be within the range from 1 to 3999.
		
		
		http://en.wikipedia.org/wiki/Roman_numerals
		
		

		Symbol	Value
		I	1
		V	5
		X	10
		L	50
		C	100
		D	500
		M	1,000
		
	The numeral I can be placed before V and X to make 4 units (IV) and 9 units (IX) respectively
				X can be placed before L and C to make 40 (XL) and 90 (XC) respectively
				C can be placed before D and M to make 400 and 900 according to the same pattern[5]
*/
// pass 2
class Solution {
public:
    int romanToInt(string s) {
		unordered_map<string, int> numbermap;
		numbermap["I"] = 1;
		numbermap["II"] = 2;
		numbermap["III"] = 3;
		numbermap["IV"] = 4;
		numbermap["V"] = 5;
		numbermap["IX"] = 9;
		numbermap["X"] = 10;
		numbermap["XL"] = 40;
		numbermap["L"] = 50;
		numbermap["XC"] = 90;
		numbermap["C"] = 100;
		numbermap["CD"] = 400;
		numbermap["D"] = 500;
		numbermap["CM"] = 900;
		numbermap["M"] = 1000;
		
		int result = 0;
		for(int i=0; i<s.size(); ) {
			string str = s.substr(i, 2);
			if(numbermap.find(str) != numbermap.end()) {
				result += numbermap[str];
				i += 2;
			}
			else {
				int count = 1;
				for(int j=i+1; j<s.size() && s[j]==s[i]; ++j, ++count) ;
				string str = s.substr(i, 1);
				result += numbermap[str] * count;
				i += count;
			}
		}
		return result;
    }
};














































// Roman string ==> number
class Solution {
public:
	int romanToInt(string s) {
		map<string, int> romanMap;
		romanMap["I"] = 1;
		romanMap["IV"] = 4;
		romanMap["V"] = 5;
		romanMap["IX"] = 9;
		romanMap["X"] = 10;
		romanMap["XL"] = 40;
		romanMap["L"] = 50;
		romanMap["XC"] = 90;
		romanMap["C"] = 100;
		romanMap["CD"] = 400;
		romanMap["D"] = 500;
		romanMap["CM"] = 900;
		romanMap["M"] = 1000;
		
		int result = 0;
		for(int i=0; i<s.size();) {
			if(i<s.size()-1) {
				string str = s.substr(i, 2);
				if(romanMap.find(str) != romanMap.end()) {
					result += romanMap[str];
					i += 2;
					continue;
				}
			}
			string str = s.substr(i, 1);
			if(romanMap.find(str) != romanMap.end()) {
				result += romanMap[str];
				i += 1;
			}
		}
		
		return result;
	}
};


// Number ==> Roman string
class Solution {
public:
    string intToRoman(int num) {
		map<int, string> dict;
        dict.clear();
        dict[1] = "I";
        dict[4] = "IV";
        dict[5] = "V";
        dict[9] = "IX";
        dict[10] = "X";
        dict[40] = "XL";
        dict[50] = "L";
        dict[90] = "XC";
        dict[100] = "C";
        dict[400] = "CD";
        dict[500] = "D";
        dict[900] = "CM";
        dict[1000] = "M";
        string result = "";
        for (map<int, string>::reverse_iterator it = dict.rbegin(); it != dict.rend(); it++) {
            while (num >= it->first) {
                result += it->second;
                num -= it->first;
            }
        }
        return result;
    }
};


// Bad solution
class Solution {
public:

	int romanToInt(string s) {
		int result = 0;
		for(int i=0; i<s.size();) {
			switch(s[i]) {
			case 'I':
				result += processLetterI(s, i);
				break;
			case 'V':
				result += 5;
				++i;
				break;
			case 'X':
				result += processLetterX(s, i);
				break;
			case 'L':
				result += 50;
				++i;
				break;
			case 'C':
				result += processLetterC(s, i);
				break;
			case 'D':
				result += 500;
				++i;
				break;
			case 'M':
				result += 1000;
				++i;
				break;
			}		
		}
		
		return result;
	}

	int processLetterI(string& s, int &i) {
		int res = 0;
		int j=i;
		for(; j<s.size()-1; ++j) {
			if(s[j] != 'I')
				break;
			else if(s[j+1] == 'V') {
				res += 4;
				i = j+2;
				return res;
			} else if(s[j+1] == 'X') {
				res += 9;
				i = j+2;
				return res;
			}
			++res;
		}
		if(j==s.size()-1 && s[j] == 'I') {
			++res;
			++j;
		}
		i = j;
		return res;
	}

	int processLetterX(string& s, int &i) {
		int res = 0;
		int j=i;
		for(; j<s.size()-1; ++j) {
			if(s[j] != 'X')
				break;
			else if(s[j+1] == 'L') {
				res += 40;
				i = j+2;
				return res;
			} else if(s[j+1] == 'C') {
				res += 90;
				i = j+2;
				return res;
			}
			res += 10;
		}
		
		if(j==s.size()-1 && s[j] == 'X') {
			res += 10;
			++j;
		}
		
		i = j;
		return res;
	}

	int processLetterC(string& s, int &i) {
		int res = 0;
		int j=i;
		for(; j<s.size()-1; ++j) {
			if(s[j] != 'C')
				break;
			else if(s[j+1] == 'D') {
				res += 400;
				i = j+2;
				return res;
			} else if(s[j+1] == 'M') {
				res += 900;
				i = j+2;
				return res;
			}
			res += 100;
		}
		
		if(j==s.size()-1 && s[j] == 'C') {
			res += 100;
			++j;
		}
		
		i = j;
		return res;
	}
};


