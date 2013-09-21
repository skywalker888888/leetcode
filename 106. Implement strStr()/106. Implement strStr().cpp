/**
		Implement strStr().
		Returns a pointer to the first occurrence of needle in haystack, or null if needle is not part of haystack.
*/
// pass 3
// KMP
class Solution {
public:
    char *strStr(char *haystack, char *needle) {
    	if(!haystack || !*haystack)
			return (!needle || !*needle)?haystack:NULL;
		if(!needle || !*needle)
			return haystack;
		vector<int> fun = calculateKMPFun(needle);
		int n = fun.size();
		int i = 0;
		int j = 0;
		while(i<strlen(haystack) && j<n) {
			if(j==-1 || haystack[i]==needle[j]) {
				++i;
				++j;
			} else {
				j = fun[j];
			}
		}
		if(j < n) {
			return NULL;
		}
		
		char *result = haystack + i - j;
		return result;
	}
	
	vector<int> calculateKMPFun(char *needle) {
		int n = strlen(needle);
		vector<int> fun(n, 0);
		fun[0] = -1;
		int i = 0;
		int k = fun[0];
		while(i < n-1) {
			if(k==-1 || needle[i]==needle[k]) {
				++k;
				++i;
				fun[i] = k;
			} else {
				k = fun[k];
			}
		}
		return fun;
	}
};

class Solution {
public:
    char *strStr(char *haystack, char *needle) {
		if(!haystack || !*haystack)
			return (!needle || !*needle)?haystack:NULL;
		if(!needle || !*needle)
			return haystack;
		
		vector<int> fun = calculateKMPFun(needle);
		int n = fun.size();
		
		int k = fun[0];
		int i = 0;
		while(haystack[i]) {
			while(k>0 && haystack[i]!=needle[k])
				k = fun[k-1];
			if(needle[k] == haystack[i]) {
				++k;
			}
			if(k == n) {
				return haystack+i-n+1;
				// k = fun[k]
			}
			++i;
		}
        return NULL;
	}
	vector<int> calculateKMPFun(char *needle) {
		int n = strlen(needle);
		vector<int> result(n, 0);
		result[0] = 0;
		for(int i=1; i<n; ++i) {
			int k = result[i-1];
			while(k>0 && needle[i]!=needle[k])
				k = result[k-1];
			if(needle[i] == needle[k])
				++k;
			result[i] = k;
		}
		return result;
	}
};

class Solution {
public:
    char *strStr(char *haystack, char *needle) {
    	if(!haystack || !*haystack)
			return (!needle || !*needle)?haystack:NULL;
		if(!needle || !*needle)
			return haystack;
		
		vector<int> fun = calculateKMPFun(needle);
		int n = fun.size();
		
		int k = fun[0];
		int i = 0;
		while(haystack[i]) {
			while(k>=0 && haystack[i]!=needle[k+1])
				k = fun[k];
			if(needle[k+1] == haystack[i]) {
				++k;
			}
			if(k == n-1) {
				return haystack+i-n+1;
				// k = fun[k]
			}
			++i;
		}
        return NULL;
	}
	vector<int> calculateKMPFun(char *needle) {
		int n = strlen(needle);
		vector<int> result(n, 0);
		result[0] = -1;
		for(int i=1; i<n; ++i) {
			int k = result[i-1];
			while(k>=0 && needle[i]!=needle[k+1])
				k = result[k];
			if(needle[i] == needle[k+1])
				++k;
			result[i] = k;
		}
		return result;
	}
};


// Brute force
class Solution {
public:
    char *strStr(char *haystack, char *needle) {
    	if(!haystack || !*haystack)
			return (!needle || !*needle)?haystack:NULL;
		if(!needle || !*needle)
			return haystack;
		
		while(*haystack) {
			int i = 0;
			while(haystack[i]) {
				if(!needle[i])
					return haystack;
				else if(needle[i] != haystack[i])
					break;
				++i;
			}
			if(!haystack[i] && !needle[i])
				return haystack;
				
			if(!haystack[i])
				return NULL;
			++haystack;
		}
		
		return NULL;
    }
};
















































// pass 2
class Solution {
public:
    char *strStr(char *haystack, char *needle) {
		if(!haystack || !needle)
			return NULL;
		
		char *p = haystack;
		while(p) {
			int i = 0;
			while(needle[i]) {
				if(!p[i])
					return NULL;
				else if(p[i] != needle[i])
					break;
				++i;
			}
			if(!needle[i])
				return p;
			++p;
		}
		return NULL;
    }
};











































class Solution {
public:
	char *strStr(char *haystack, char *needle)
	{
		if(!haystack|| !needle)
			return NULL;
		
		if(!*haystack && !*needle)
			return haystack;
		
		char *p = haystack;
		while(*p)
		{
			int i=0;
			while(needle[i])
			{
				if(!p[i])
					return NULL;
				else if(needle[i] != p[i])
				{
					++p;
					break;
				}
				++i;
			}
			if(!needle[i])
				return p;
		}
		
		return NULL;
	}
};




