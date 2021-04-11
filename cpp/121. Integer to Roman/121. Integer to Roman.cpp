#include <map>
#include <string>
using namespace std;

/**
		Given an integer, convert it to a roman numeral.
		Input is guaranteed to be within the range from 1 to 3999.
*/
// pass 2
class Solution {
public:
    string intToRoman(int num) {
		unordered_map<int, string> romanMap;
		vector<int> nums;
		romanMap[1] = "I"; nums.push_back(1);
		romanMap[4] = "IV"; nums.push_back(4);
		romanMap[5] = "V"; nums.push_back(5);
		romanMap[9] = "IX"; nums.push_back(9);
		romanMap[10] = "X"; nums.push_back(10);
		romanMap[40] = "XL"; nums.push_back(40);
		romanMap[50] = "L"; nums.push_back(50);
		romanMap[90] = "XC"; nums.push_back(90);
		romanMap[100] = "C"; nums.push_back(100);
		romanMap[400] = "CD"; nums.push_back(400);
		romanMap[500] = "D"; nums.push_back(500);
		romanMap[900] = "CM"; nums.push_back(900);
		romanMap[1000] = "M"; nums.push_back(1000);
		
		string result;
		for(int i=nums.size()-1; i>=0; --i) {
			while(num >= nums[i]) {
				result += romanMap[nums[i]];
				num -= nums[i];
			}
		}
		
		return result;
    }
};


































class Solution {
public:
	string intToRoman(int num)
	{
		map<int, string> romanMap;
		
		romanMap[1] = "I";
		romanMap[4] = "IV";
		romanMap[5] = "V";
		romanMap[9] = "IX";
		romanMap[10] = "X";
		romanMap[40] = "XL";
		romanMap[50] = "L";
		romanMap[90] = "XC";
		romanMap[100] = "C";
		romanMap[400] = "CD";
		romanMap[500] = "D";
		romanMap[900] = "CM";
		romanMap[1000] = "M";
		
		string result;
		for(map<int, string>::reverse_iterator i=romanMap.rbegin(); i!=romanMap.rend(); ++i)
		{
			while(num >= i->first)
			{
				result += i->second;
				num -= i->first;
			}
		}
		
		return result;
	}
};


