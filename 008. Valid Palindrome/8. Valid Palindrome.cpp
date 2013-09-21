/**
		Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

		For example,
		"A man, a plan, a canal: Panama" is a palindrome.
		"race a car" is not a palindrome.

		Note:
		Have you consider that the string might be empty? This is a good question to ask during an interview.

		For the purpose of this problem, we define empty string as valid palindrome.Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

		For example,
		"A man, a plan, a canal: Panama" is a palindrome.
		"race a car" is not a palindrome.

		Note:
		Have you consider that the string might be empty? This is a good question to ask during an interview.

		For the purpose of this problem, we define empty string as valid palindrome.
*/
// pass 3
class Solution {
public:
    bool isPalindrome(string s) {
    	if(s.size() == 0)
			return true;
		
		int i=0, j=s.size()-1;
		while(i < j)
			if(!(s[i]>='a'&&s[i]<='z' || s[i]>='A'&&s[i]<='Z' || s[i]>='0'&&s[i]<='9'))
				++i;
			else if(!(s[j]>='a'&&s[j]<='z' || s[j]>='A'&&s[j]<='Z' || s[j]>='0'&&s[j]<='9'))
				--j;
			else if(tolower(s[i]) == tolower(s[j]))
				++i, --j;
			else
				return false;
		return true;
    }
};































// Non recursion
class Solution
{
public:
	bool isPalindrome(string s)
	{
		string s1 = s;
		string s2 = s;
		//reverse(s2.begin(), s2.end());
		int i=0; 
		int j = s2.size() - 1;
		
		while(i<s1.size() && j>=0)
			if(!isValidChar(s1[i]) && !isValidChar(s2[j]))
				++i, --j;
			else if(!isValidChar(s1[i]) && isValidChar(s2[j]))
				++i;
			else if(isValidChar(s1[i]) && !isValidChar(s2[j]))
				--j;
			else if(charsequal(s1[i], s2[j]))
				++i, --j;
			else
				return false;
				
		while(i<s1.size() && !isValidChar(s1[i]))
			++i;
		while(j>=0 && !isValidChar(s2[j]))
			--j;
			
		return i>=s1.size() && j<0;
	}
	bool isValidChar(char ch)
	{
		return ch>='0'&&ch<='9' || ch>='a'&&ch<='z' || ch>='A'&&ch<='Z';
	}
	 
	bool charsequal(char ch1, char ch2)
	{
		if(ch1 == ch2)
			return true;
		
		if(ch1>='A' && ch1<='Z')
			ch1 = 'a' + (ch1 - 'A');
		if(ch2>='A'&&ch2<='Z')
			ch2 = 'a' + (ch2 - 'A');
			
		return ch1 == ch2;
	}
};





// Recursion
class Solution
{
public:
    bool isPalindrome(string s);
	
private:
	bool isValidChar(char c);
	bool isEqualChars(char c1, char c2);
};


bool Solution::isPalindrome(string s)
{
	// ignore case
	if(s.size() <= 1)
		return true;

	if(!isValidChar(s[0]))
		return isPalindrome(s.substr(1, s.size()-1));
	else if(!isValidChar(s[s.size()-1]))
		return isPalindrome(s.substr(0, s.size()-1));
	else
	{
		if(!isEqualChars(s[0], s[s.size()-1]))
			return false;
		else
			return isPalindrome(s.substr(1, s.size()-2));
	}
}

bool Solution::isValidChar(char c)
{
	 return c<='9'&& c>='0' || c<='Z'&& c>='A' || c<='z'&& c>='a';
}

bool Solution::isEqualChars(char c1, char c2)
{
	if(!isValidChar(c1) || !isValidChar(c2))
		return false;

	if( tolower(c1) == tolower(c2) )
		return true;
	
	return false;
}




