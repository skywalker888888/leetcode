/**
	Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

	For "(()", the longest valid parentheses substring is "()", which has length = 2.

	Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/
// pass 3
class Solution {
public:
    int longestValidParentheses(string s) {
		int result = 0;

		// forward
		int left = 0;
		int right = 0;
		int len = 0;
		for(int i=0; i<s.size(); ++i) {
			if(s[i] == '(')
				++left;
			else {
				++right;
				if(right > left) {
					left = right = 0;
					len = 0;
				} else {
					len += 2;
					if(left == right)
						result = max(len, result);
				}
			}
		}
		
		// backward
		left = right = 0;
		len = 0;
		for(int i=s.size()-1; i>=0; --i) {
			if(s[i] == ')') {
				++right;
			} else {
				++left;
				if(left > right) {
					left = right = 0;
					len = 0;
				} else {
					len += 2;
					if(left == right)
						result = max(len, result);
				}
			}
		}
		
		return result;
    }
};
































// pass 2
class Solution {
public:
    int longestValidParentheses(string s) {
		int count_left = 0;
		int count_right = 0;
		int maxlen = 0;
		int len = 0;
		
		// forward
		for(int i=0; i<s.size(); ++i) {
			if(s[i] == '(')
				++count_left;
			else {
				++count_right;
				if(count_right > count_left) {
					count_left = 0;
					count_right = 0;
					len = 0;
				} else {
					len += 2;
					if(count_right == count_left)
						maxlen = max(maxlen, len);
				}
			}
		}
		
		// backward
		count_left = 0;
		count_right = 0;
		len = 0;
		for(int i=s.size()-1; i>=0; --i) {
			if(s[i] == ')')
				++count_right;
			else {
				++count_left;
				if(count_left > count_right) {
					count_left = 0;
					count_right = 0;
					len = 0;
				} else {
					len += 2;
					if(count_right == count_left)
						maxlen = max(maxlen, len);
				}
			}
		}
		
		return maxlen;
    }
};





 
class Solution {
public:
    int longestValidParentheses(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<pair<char, int> > st;
        st.push(pair<char, int>(')', -1));
        int ret = 0;
        for(int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(')
                st.push(pair<char, int>(c, i));
            else {
                pair<char, int> node = st.top();
                if (node.first == '(') {
                    st.pop();
                    ret = max(ret, i - st.top().second);
                }
                else
                    st.push(pair<char, int>(c, i));                   
            }
        }
        
        return ret;
    }
};




































class Solution {
public:

	/**
			http://yewenxing.wordpress.com/2012/03/11/longest-valid-parentheses/
			思路：从头到尾扫描字符串，遇到’(‘计数+1,遇到’)'计数-1,每当计数为0时,我们找到一个有效子串,如果计数<0,从下一个位置开始重新扫描.重复上述过程字符串尾向头扫描.最终最长的有效子串即所求.
	*/
	int longestValidParentheses(string s)
	{
		int n = s.length();
		int maxl = 0;
		int count = 0;
		int len = 0;
		for(int i = 0;i < n;i++){
			if(s[i] == '('){
				count++;
				len++;
			}
			if(s[i] == ')') {
				count--;
				len++;
			}
			if(count == 0 && len > maxl){// one valid substring found
				maxl = len;
			}
			else if(count < 0){//invalid pre-fix 
				len = 0;
				count = 0;
			}
		}
		count = 0;
		len = 0;
		for(int i = n-1;i >= 0;i--){
			if(s[i] == ')'){
				count++;
				len++;
			}
			if(s[i] == '(') {
				count--;
				len++;
			}
			if(count == 0 && len > maxl){// one valid substring found
				maxl = len;
			}
			else if(count < 0){//invalid pre-fix 
				len = 0;
				count = 0;
			}
		}
		return maxl;
	}
};


 
class Solution {
	struct Node
	{
		char c;
		int index;
		Node(){}
		Node(char _c, int idx):c(_c), index(idx){}
	};
public:
    int longestValidParentheses(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<Node> st;
        st.push(Node(')', -1));
        int ret = 0;
        for(int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            if (c == '(')
                st.push(Node(c, i));
            else // c==')'
            {
                Node node = st.top();
                if (node.c == '(')
                {
                    st.pop();
                    ret = max(ret, i - st.top().index);
                }
                else
                    st.push(Node(c, i));                   
            }
        }
        
        return ret;
    }
};

