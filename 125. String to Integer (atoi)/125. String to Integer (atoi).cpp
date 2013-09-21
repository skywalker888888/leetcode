/**
		Implement atoi to convert a string to an integer.
		Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.
		Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.
*/
// pass 2
class Solution {
public:
    int atoi(const char *str) {
		
    }
};






























































class Solution {
public:
	int atoi(const char *str)
	{
		if(!str || !*str)
			return 0;
			
		int sign = 1;
		
		while(*str == ' ' || *str=='\t')
			++str;
		if(*str == '+')
			++str;
		else if(*str == '-')
			++str, sign = -1;
		
		int base = 10;
		if(*str=='0')
			if(*(str+1) == 'X' || *(str+1) == 'x')
			{
				base = 16;
				str += 2;
			}
			else if(*(str+1))
			{
				//base = 8;
				//++ str;
			}
			else
				return 0;
		
		long long value = 0;
		while(*str>='0' && *str <= '9')
		{
			int num = *str - '0';
			value = value*base + num;
			++str;
		}
		
		if(sign < 0) value = -value;

		if (value < INT_MIN) value = INT_MIN;
		if (value > INT_MAX) value = INT_MAX;
		
		return value;
	}
};


class Solution {
public:
    int atoi(const char *str) {
        int sign = 1;
        while(*str == ' ') str++;
        if (*str == '+') str++;
        else if (*str == '-') str++, sign = -1;
        long long val = 0;
        int digit;
        while (*str != '\0') {
            if (*str < '0' || *str > '9') break;
            digit = (*str - '0');
            val = val * 10 + digit;
            str++;
        }
        if (sign == -1) val = -val;
        if (val < INT_MIN) val = INT_MIN;
        if (val > INT_MAX) val = INT_MAX;
        return val;
    }
};

