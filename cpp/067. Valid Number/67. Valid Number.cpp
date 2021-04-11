/**
		Validate if a given string is numeric.

		Some examples:
		"0" => true
		" 0.1 " => true
		"abc" => false
		"1 a" => false
		"2e10" => true
		Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.
*/
// pass 3
class Solution {
public:
    bool isNumber(const char *s) {
		if(!s || !*s)
			return false;
		while(*s && isspace(*s))
			++s;
		if(*s=='+' || *s=='-')
			++s;
		if(!*s)
			return false;
		const char *e = s + strlen(s) - 1;
		while(isspace(*e))
			--e;
		
    	bool bIsDigit = false;
		bool bIsExpo = false;
		bool bIsDot = false;
		bool bIsSign = false;
		while(s <= e) {
			if(*s>='0' && *s<='9') {
				bIsDigit = true;
			} else if(*s == '.') {
				if(!bIsDigit && s==e)
					return false;
				if(bIsExpo || bIsDot)
					return false;
				bIsDot = true;
			} else if(*s=='e' || *s=='E') {
				if(bIsExpo || !bIsDigit)
					return false;
				if(s==e)
					return false;
				bIsExpo = true;
			} else if(*s=='+' || *s=='-') {
				if(*(s-1)!='e' && *(s-1)!='E')
					return false;
				if(bIsSign || !bIsExpo)
					return false;
				bIsSign = true;
				bIsDigit = false;
			} else {
				return false;
			}
			++s;
		}
		if(!bIsDigit)
			return false;
		
		return true;
    }
};


































// pass 2
class Solution {
public:
    bool isNumber(const char *s) {
		// 
		if(!s || !*s)
			return false;
		while(s && *s!='\0' && isspace(*s)) 
			++s;
		if(*s=='+' || *s=='-')
			++s;

		if(!s || !*s)
			return false;

		const char *e = s + strlen(s) - 1;
		while (e > s && isspace(*e)) e--;
			
		bool bPastPointer = false;
		bool bPassExpo = false;
		bool bFirstIsZero = false;
		bool bHasNum = false;
		while(s < e+1) {
			if(*s>='0' && *s<='9') {
				// do nothing
				bHasNum = true;
			} else if(*s == '.') {
				if(!bHasNum && s==e )
					return false;
				if(bPastPointer || bPassExpo)
					return false;
				bPastPointer = true;
			} else if(*s == 'E' || *s == 'e') {
				if(bPassExpo || !bHasNum)
					return false;
				if(s == e)
					return false;
				bPassExpo = true;
				bHasNum = false;
			} else if(*s=='+' || *s=='-') {
				if(*(s-1)!='E' && *(s-1)!='e')
					return false;
			} else
				return false;
			++s;
		}
		
		return bHasNum;
    }
};











































class Solution {
public:
	bool isNumber(const char *s) {
	 // trim leading/trailing spaces
			while (*s != '\0' && isspace(*s)) s++;
			if (*s == '\0') return false;
			const char *e = s + strlen(s) - 1;
			while (e > s && isspace(*e)) e--;
			// skip leading +/-
			if (*s == '+' || *s == '-') s++;

			bool num = false; // is a digit
			bool dot = false; // is a '.'
			bool exp = false; // is a 'e'
			while (s != e + 1) {
				if (*s >= '0' && *s <= '9') {
					num = true;
				}
				else if (*s == '.') {
					if(exp || dot) return false;
					dot = true;
				}
				else if (*s == 'e') {
					if(exp || num == false) return false;
					exp = true;
					num = false;
				}
				else if (*s == '+' || *s == '-') {
					if (*(s-1) != 'e') return false;
				}
				else {
					return false;
				}
				s++;
			}
			return num;
	}
};


