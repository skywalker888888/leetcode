/**
		Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.
		You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.
		Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

		For the last line of text, it should be left justified and no extra space is inserted between words.

		For example,
		words: ["This", "is", "an", "example", "of", "text", "justification."]
		L: 16.

		Return the formatted lines as:
		[
		   "This    is    an",
		   "example  of text",
		   "justification.  "
		]
		Note: Each word is guaranteed not to exceed L in length.
*/
// pass 3
class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        vector<string> result;
		int n = words.size();
		if(!L)
			return words;
		int i = 0;
		while(i < n) {
			int len = words[i].size();
			int j = i+1;
			while(j<n && len+words[j].size()+1<=L) {
				len += words[j].size() + 1;
				++j;
			}
			
			// organize i....j-1
			if(j==n || len==L || j==i+1) {
				stringstream ss;
				ss << words[i];
				for(int k=i+1; k<j; ++k)
					ss << " " << words[k];
				while(len < L) {
					ss << " ";
					++len;
				}
				result.push_back(ss.str());
			} else {
				int padding = L - len;
				int count = j - i - 1;
				int padperslot = padding/count;
				int cnt = padding%count;

				stringstream ss;
				ss << words[i];
				
				for(int k=i+1; k<j; ++k) {
					if(cnt) {
						ss << " ";
						--cnt;
					}
					if(padperslot)
						ss << string(padperslot, ' ');
					
					ss << " " << words[k];
				}
				result.push_back(ss.str());
			}
			i = j;
		}
		return result;
    }
};
































/*
		Corner Cases:
		A line other than the last line might contain only one word. What should you do in this case?
		In this case, that line should be left-justified.	
*/
// pass 2
class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
		vector<string> result;
			
		int i = 0;
		while(i < words.size()) {
			int nLen = words[i].size();
			int j = i;
			stringstream linestream;
			linestream << words[i];
			
			while(j+1<words.size() && nLen+1+words[j+1].size()<=L) {
				nLen += 1 + words[j+1].size();
				++j;
			}
			if(j == i) {
				if(L - nLen)
					linestream << string(L-nLen, ' ');
				++i;
			} else if(j>=words.size()-1) {
				for(int k=i+1; k<=j; ++k)
					linestream << " " << words[k];
				linestream << string(L-nLen, ' ');
				i = j+1;
			}
			else {
				int nWordCount = j-i+1;
				
				// there are L-nLen + (nWordCount-1) space
				int nTotalSpaces = L - nLen + (nWordCount-1);
				int nSlots = nWordCount - 1;
				
				int spacePerSlot = nTotalSpaces / nSlots;
				int remainder = nTotalSpaces % nSlots;
				for(int k=i+1; k<=j; ++k) {
					linestream << string( spacePerSlot+(remainder?1:0), ' ') << words[k];
					if(remainder)
						--remainder;
				}
				i = j+1;
			}
			result.push_back(linestream.str());
		}
		return result;
    }
};

































class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L);
};


vector<string> Solution::fullJustify(vector<string> &words, int L)
{
	vector<string> result;
	for(int i=0; i<words.size(); )
	{
		int nLen = 0;
		for(int j=i; j<words.size(); ++j)
		{
			if(j == i)
				nLen += words[j].size();
			else 
				nLen += 1 + words[j].size();
			
			if(j==words.size()-1 || nLen+1+words[j+1].size()>L)
			{
				// words[i..j]
				string line;
				int spaceCount = j - i;
				// only one word can be used
				if(!spaceCount)
					line = words[j] + string(L-words[j].size(), ' ');
				else
				{
					int nWordsLen = 0;
					for(int k=i; k<=j; ++k)
						nWordsLen += words[k].size();

					int spaceNum = L - nWordsLen;
					
					int spacePerSlot = spaceNum/spaceCount;
					// last line
					if(j == words.size()-1)
						spacePerSlot = 1;
						
					int nAdditionalSpace = spaceNum - spacePerSlot*spaceCount;
					
					for(int k=i; k<=j; ++k)
					{
						if(k == i)
							line += words[k];
						else if(k < j)
						{
							int nCount = 0;
							if(j != words.size()-1 && nAdditionalSpace)
							{
								--nAdditionalSpace;
								nCount = 1;
							}
							string spaceStr = string(spacePerSlot+nCount, ' ');
							line += spaceStr + words[k];
						}
						else if(k == j)
						{
							if(j != words.size()-1)
							{
								line += string(spacePerSlot, ' ') + words[k];
							}
							else
							{
								line += string(spacePerSlot, ' ') + words[k] + string(nAdditionalSpace, ' ');
							}
						}
					}
				}
				result.push_back(line);
				i = j+1;
				break;
			}
		}
	}
	
	return result;
}
