/**
		Given a string containing only digits, restore it by returning all possible valid IP address combinations.
		For example:
		Given "25525511135",
		return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/
// pass 3
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
		vector<string> result;
		int n = s.size();
		if(n < 4)
			return result;
		
		for(int i=0; i<n-3; ++i) {
			string str1 = s.substr(0, i+1);
			if(!validString(str1))
				continue;
			for(int j=i+1; j<n-2; ++j) {
				string str2 = s.substr(i+1, j-i);
				if(!validString(str2))
					continue;
				for(int k=j+1; k<n-1; ++k) {
					string str3 = s.substr(j+1, k-j);
					if(!validString(str3))
						continue;
					string str4 = s.substr(k+1, n-k-1);
					if(!validString(str4))
						continue;
					stringstream v;
					v << str1 << "." << str2 << "." << str3 << "." << str4;
					result.push_back(v.str());
				}
			}
		}
		return result;
    }
	
	bool validString(string s) {
		if(s.size()>1 && s[0]=='0')
			return false;
		stringstream ss(s);
		int value;
		ss >> value;
		if(value>255 || value<0)
			return false;
		return true;
	}
};











































// pass 2
class Solution {
public:
	bool validstr(const string &str){
		if(!str.size())
			return false;
		if(str[0]=='0' && str.size()>1)
			return false;
		stringstream converter(str);
		int val;
		converter >> val;
		if(val>255 || val<0)
			return false;
		return true;
	}
    vector<string> restoreIpAddresses(string s) {
		vector<string> result;
		if(s.size() < 4)
			return result;
		
		for(int i=0; i<s.size()-3; ++i){
			string str1 = s.substr(0, i+1);
			if(!validstr(str1))
				break;
			for(int j=i+1; j<s.size(); ++j){
				string str2 = s.substr(i+1, j-i);
				if(!validstr(str2))
					break;
				for(int k=j+1; k<s.size(); ++k){
					string str3 = s.substr(j+1, k-j);
					if(!validstr(str3))
						break;
					
					if(k+1<s.size()){
						string str4 = s.substr(k+1, s.size()-k-1);
						if(!validstr(str4))
							continue;
						
						stringstream itemstr;
						itemstr << str1 << "." << str2 << "." << str3 << "." << str4;
						result.push_back(itemstr.str());
					}
				}
			}
		}
    }
};





class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
    	vector<string> result;
		if(s.size()<4)
			return result;
		
		vector<vector<string> > ipsegments;
		getIpSegments(s, 0, 4, ipsegments);
		if(!ipsegments.size())
			return result;
			
		for(int i=0; i<ipsegments.size(); ++i){
			stringstream ss;
			for(int j=0; j<ipsegments[i].size(); ++j)
				if(!j)
					ss << ipsegments[i][j];
				else
					ss << "." << ipsegments[i][j];
			string s = ss.str();
			result.push_back(s);
		}
		
		return result;
    }
	
	void getIpSegments(const string &s, const int startindex, const int cnt, vector<vector<string> > &result){
		if(startindex >= s.size() || cnt<0)
			return;
		
		if(cnt == 1){
			if(s[startindex]=='0' && startindex<s.size()-1)
				return;
			string str = s.substr(startindex, s.size()-startindex);
			stringstream converter(str);
			int num;
			converter >> num;
			if(num > 255 || num<0)
				return;
			vector<string> res;
			res.push_back(str);
			result.push_back(res);
			return;
		}
		
		for(int i=startindex; i<s.size(); ++i){
			string str = s.substr(startindex, i-startindex+1);
			stringstream converter(str);
			int num;
			converter >> num;
			if(num>255 || num<0)
				break;
			vector<vector<string> > newres;
			getIpSegments(s, i+1, cnt-1, newres);
			if(newres.size()){
				for(int m=0; m<newres.size(); ++m){
					if(newres[m].size() != cnt-1)
						continue;
					vector<string> res;
					res.push_back(str);
					for(int n=0; n<newres[m].size(); ++n)
						res.push_back(newres[m][n]);
					result.push_back(res);
				}
			}
			if(s[startindex] == '0')
				break;
		}
	}
};





























class Solution
{
public:
    vector<string> restoreIpAddresses(string s);
	
	int toIpInt(string str);
};

int Solution::toIpInt(string str)
{
	if(!str.size())
		return -1;
	if(str[0]=='0' && str.size()>1)
		return -1;
		
	stringstream convert(str);
	int result;
	convert >> result;
	
	if(result>255)
		return -1;
		
	return result;
}


vector<string> Solution::restoreIpAddresses(string s)
{
	vector<string> result;
	if(s.size() < 4)
		return result;
	for(int i=0; i<s.size(); ++i)
	{
		if(s[i]>'9' || s[i]<'0')
			return result;
	}
	
	for(int i=0; i<s.size() && i<=2; ++i)
	{
		// s[0..i].
		string str = s.substr(0, i+1);
		if(toIpInt(str) < 0)
			break;
		
		string ip1;
		ip1 += str;
		ip1 += ".";
		for(int j=i+1; j<s.size() && j-i<=3; ++j)
		{
			// s[i+1...j]
			string str = s.substr(i+1, j-i);
			if(toIpInt(str) < 0)
				break;
				
			string ip2 = ip1;
			ip2 += str;
			ip2 += ".";
			for(int m=j+1; m<s.size() && m-j<=3; ++m)
			{
				// s[j+1...m]
				string str = s.substr(j+1, m-j);
				if(toIpInt(str) < 0)
					break;

				string ip3 = ip2;
				ip3 += str;
				ip3 += ".";
				
				// s[m+1...s.size()-1]
				string str2 = s.substr(m+1, s.size()-1-m);
				if(toIpInt(str2) < 0)
					continue;
					
				string ip4 = ip3;
				ip4 += str2;
				result.push_back(ip4);
			}
		}
	}
	
	return result;
}


