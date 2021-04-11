/**
		Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

		If the last word does not exist, return 0.

		Note: A word is defined as a character sequence consists of non-space characters only.

		For example, 
		Given s = "Hello World",
		return 5.
*/
// pass 3
class Solution {
public:
    int lengthOfLastWord(const char *s) {
		int result = 0;
		int state = 0;
		int tmp = 0;
		while(*s) {
			if(*s == ' ') {
				if(tmp)
					result = tmp;
				tmp = 0;
			}
			else
				++tmp;
			++s;
		}
		if(tmp)
			result = tmp;
		return result;
    }
};
















































// pass 2
class Solution {
public:
    int lengthOfLastWord(const char *s) {
		const char *first = NULL;
		const char *last = NULL;
		int state = 0; // 0 - need first, 1 - need last
		while(*s) {
			if(*s == ' ')
				state = 0;
			else if(state == 0) {
				first = s;
				last = s;
				state = 1;
			} else
				last = s;
			++s;
		}
		
		if(!first)
			return 0;
		return last - first + 1;
    }
};

































class Solution {
public:
	int lengthOfLastWord(const char *s) {
		if(!s)
			return 0;
		
		int nValue = 0;
		bool bInOneWord = false;
		int nLen = 0;
		while(*s) {
			if(*s != ' ') {
				if(!bInOneWord) {
					nLen = 1;
					bInOneWord = true;
				} else
					++nLen;
			} else {
				if(bInOneWord)
					nValue = nLen;
				nLen = 0;
				bInOneWord = false;
			}
			++s;
			if(!*s && bInOneWord)
				nValue = nLen;
		}
		
		return nValue;
	}
};

