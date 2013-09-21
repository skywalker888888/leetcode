/**
		Given an absolute path for a file (Unix-style), simplify it.
		For example,
		path = "/home/", => "/home"
		path = "/a/./b/../../c/", => "/c"
		
		Corner Cases:
		Did you consider the case where path = "/../"?
		In this case, you should return "/".
		Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
		In this case, you should ignore redundant slashes and return "/home/foo".
*/
// pass 3
class Solution {
public:
    string simplifyPath(string path) {
		int n = path.size();
		if(!n)
			return path;
			
		int i = 0;
		if(path[i] != '/')
			return path;
		
		int j = i+1;
		while(j < n) {
			if(path[i] == '/') {
				if(path[j] == '/')
					++j;
				else if(j+1<n&&path[j]=='.'&&path[j+1]=='/' || j==n-1&&path[j]=='.')
					j += 2;
				else if(j+2<n && path[j]=='.' && path[j+1]=='.' && path[j+2]=='/' || j+1==n-1 && path[j]=='.' && path[j+1]=='.') {
					if(i > 0) {
						do {
							--i;
						} while(path[i]!='/');
					}
					j += 3;
				} else {
					path[++i] = path[j++];
				}
			} else {
				path[++i] = path[j++];
			}
		}
		if(i>0 && path[i] == '/')
			--i;
		return path.substr(0, i+1);
    }
};








































// pass 2
// Inplace and no movement
class Solution {
public:
    string simplifyPath(string path) {
		if(!path.size())
			return path;
		if(path[0] != '/')
			return string();
			
		int i = 0;
		int j = 1;
		while(j < path.size()) {
			if(path[j]=='.' && (j+1<path.size()&&path[j+1]=='/' || j==path.size()-1))
				j += 2;
			else if(path[j]=='.' && j+1<path.size() && path[j+1]=='.' && (j+2>=path.size()||path[j+2]=='/')) {
				while(i>0 && path[i] != '/')
					--i;
				if(i>0 && path[i] == '/')
					--i;
					
				j += 3;
			} else if(path[j] == '/') {
				++j;
			}
			else {
				if(path[i] != '/')
					path[++i] = '/';
				while(j<path.size() && path[j]!='/') {
					path[++i] = path[j++];
				}
			}
		}
		
		path.resize(i+1);
		return path;
    }
};


class Solution {
public:
    string simplifyPath(string path) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
		string result;
		stack<char> stkChars;
		int j = 1;
		
		if(path.empty() || path[0] != '/')
			return result;
			
		stkChars.push('/');
		while(j < path.size()) {
			if(j+1<path.size() && path[j]=='.' && path[j+1]=='/' || j==path.size()-1 && path[j]=='.') {
				j += 2;
			}
			else if(j+2<path.size() && path[j]=='.' && path[j+1]=='.' && path[j+2]=='/' || j+2==path.size() && path[j]=='.' && path[j+1]=='.') {
				j += 3;
				//
				stkChars.pop();
				if(stkChars.empty())
					stkChars.push('/');
				else
					while(stkChars.top() != '/')
						stkChars.pop();
			} else if(path[j]=='/')
				++j;
			else {
				while(j<path.size() && path[j]!='/') {
					stkChars.push(path[j]);
					++j;
				}
				if(j<path.size() && path[j]=='/' ) {
					++j;
					stkChars.push('/');
				}
			}
		}
		
		if(stkChars.top() == '/') {
			stkChars.pop();
			if(stkChars.empty())
				stkChars.push('/');
		}
		
		deque<char> dqeChars;
		while(!stkChars.empty()) {
			dqeChars.push_front(stkChars.top());
			stkChars.pop();
		}
		
		result.insert(result.end(), dqeChars.begin(), dqeChars.end());
		return result;
    }
};





























class Solution {
public:
    string simplifyPath(string path);
    string simplifyPath2(string path);
    string simplifyPath3(string path);
	
private:
	// state machine states
	void S0(string& path, int &i, int &j, stack<int>& stkSlashes);
	void S1(string& path, int &i, int &j, stack<int>& stkSlashes);
	void S2(string& path, int &i, int &j, stack<int>& stkSlashes);
	void S3(string& path, int &i, int &j, stack<int>& stkSlashes);
	void S4(string& path, int &i, int &j, stack<int>& stkSlashes);
	void END(string& path, int &i, int &j, stack<int>& stkSlashes);
	void ERROR(string& path, int &i, int &j, stack<int>& stkSlashes);
	enum
	{
		E_STATE_S0,
		E_STATE_S1,
		E_STATE_S2,
		E_STATE_S3,
		E_STATE_S4,
		E_STATE_END,
		E_STATE_ERROR
	} m_eStatue;
};


string Solution::simplifyPath3(string path)
{
	stack<int> stkSlashes;
	for(int i=0; i<path.size();)
	{
		if(path[i] == '/')
		{
			if(stkSlashes.empty())
			{
				stkSlashes.push(i);
				++i;
			}
			else
			{
				int nLast = stkSlashes.top();
				// XXXXX//YYYYYYYYYYY
				if(nLast == i-1)
					path.erase(i, 1);
				else
				{
					stkSlashes.push(i);
					++i;
				}
			}
		}
		else if(path[i] == '.')
		{
			// XXXXX/.YYYYYYYY
			if(!stkSlashes.empty() && stkSlashes.top()==i-1)
			{
				// XXXXX/./YYYY
				if(i<path.size()-1 && path[i+1]=='/')
				{
					path.erase(i, 2);
				}
				else if(i == path.size()-1) // XXXXX/.
				{
					if(stkSlashes.size() == 1)
						path.erase(i, 1);
					else
					{
						// AAAAA/BBBBBB/.
						int n = stkSlashes.top();
						stkSlashes.pop();
						int nLen = i - n + 1;
						path.erase(n, nLen);
						i = n;
					}
				}
				else if(i<path.size()-2 && path[i+1]=='.' && path[i+2]=='/' ) // XXXXXX/../YYYYYYYY
				{
					if(stkSlashes.size() == 1)
					{
						// /../YYYYYYYYYYY
						int n = stkSlashes.top();
						path.erase(n+1, 3);
						i = n + 1;
					}
					else
					{
						// XXXXXX/YYYY/../ZZZZZ
						stkSlashes.pop();
						int n = stkSlashes.top();
						int len = i - n + 2;
						path.erase(n+1, len);
						i = n + 1;
					}
				}
				else if(i==path.size()-2 && path[i+1]=='.') // // XXXXXX/..
				{
					if(stkSlashes.size() == 1)
					{
						// /..
						int n = stkSlashes.top();
						path.erase(n+1, 2);
						i = n + 1;
					}
					else
					{
						// XXXXXX/YYYY/..
						stkSlashes.pop();
						int n = stkSlashes.top();
						int len = i - n + 1;
						path.erase(n+1, len);
						i = n + 1;
					}
				}
				else 
					++i;
			}
			else
				++i;
		}
		else
			++i;
	}
	
	if(path.size() > 1 && path[path.size()-1]=='/')
		path.erase(path.size()-1, 1);
		
	return path;
}


/**
	in place and no movement
*/
string Solution::simplifyPath2(string path)
{
	stack<int> stkSlashes;
	int i = 0;
	int j = -1;
	while(i < path.size())
	{
		if(path[i] == '/')
		{
			if(stkSlashes.empty())
			{
				stkSlashes.push(i);
				j = i;
				++i;
			}
			else if(stkSlashes.top() == j) // AAAAA//
				++i; // skip 
			else if(j < i-1)  //  AAAAA/BBBB/
			{
				++j;
				path[j] = path[i++];
				stkSlashes.push(j);
			}
			else // j == i-1
			{
				stkSlashes.push(i);
				++j;
				++i;
			}
		}
		else if(path[i] == '.')
		{
			if(i == path.size()-1)
			{
				if(stkSlashes.top() == j) // AAAAA/.
					++i;
				else if(j < i-1)// AAAAAAAAAAAAAAA.
				{
					++j;
					path[j] = path[i++];
				}
				else
				{
					++i;
					++j;
				}
			}
			else if(i<path.size()-1 && path[i+1]=='/') // AAAAAAAA./
			{
				if(stkSlashes.top() == j) // AAAAA/./
					i+= 2;
				else if(j < i-1)   // AAAAAAAAAAAAAAA./
				{
					++j;
					path[j] = path[i++];
				}
				else
				{
					++i;
					++j;
				}
			}
			else if(i==path.size()-2 && path[i+1]=='.') // AAAAAAAAAAAAAAAAA..
			{
				if(stkSlashes.top() == j) // AAAAA/..
				{
					if(stkSlashes.size() > 1) // AAAAAA/BBBBBB/..
					{
						stkSlashes.pop();
					}
					i += 2;
					j = stkSlashes.top();
				}
				else if(j < i-1) // AAAAAAAAAAAAAAA/BBBBBBBB..
				{
					++j;
					path[j] = path[i++];
					++j;
					path[j] = path[i++];
				}
				else
				{
					++i;
					++j;
					++i;
					++j;
				}
			}
			else if(i<path.size()-2 && path[i+1]=='.' && path[i+2]=='/') // AAAAAAAAAAAAAAAAA../
			{
				if(stkSlashes.top() == j) // AAAAA/../
				{
					if(stkSlashes.size() > 1) // AAAAAA/BBBBBB/../
					{
						stkSlashes.pop();
					}
					i += 3;
					j = stkSlashes.top();
				}
				else if(j < i-1) // AAAAAAAAAAAAAAA/BBBBBBBB../
				{
					++j;
					path[j] = path[i++];
				}
				else
				{
					++i;
					++j;
				}
			}
			else
			{
				if(j < i-1) // AAAAAAAAAAAAAAAAAAAAAAAA.
				{
					++j;
					path[j] = path[i++];
				}
				else
				{
					++i;
					++j;
				}
			}
		}
		else
		{
			if(j < i-1) // AAAAAAAAAAAAAAA/BBBBBBBB../
			{
				++j;
				path[j] = path[i++];
			}
			else
			{
				++i;
				++j;
			}
		}
	}
	
	//
	if(path[j] == '/' && j > 0)
		--j;
	path.erase(j+1);
	return path;
}


/**
	Use state machine
	S0: start status
	S1: / status
	S2: /. status
	S3: /abc status
	S4: /.. status
	END: end status
	ERROR: end status
	
	enum
	{
		E_STATE_S0,
		E_STATE_S1,
		E_STATE_S2,
		E_STATE_S3,
		E_STATE_S4,
		E_STATE_END,
		E_STATE_ERROR
	} m_eStatue;
	
*/
string Solution::simplifyPath(string path)
{
	stack<int> stkSlashes;
	int i = 0;
	int j = -1;
	if(path.empty())
		return string();
		
	m_eStatue = E_STATE_S0;
		
	bool bFinished = false;
	while(!bFinished)
	{
		switch(m_eStatue)
		{
		case E_STATE_S0:
			S0(path, i, j, stkSlashes);
			break;
		case E_STATE_S1:
			S1(path, i, j, stkSlashes);
			break;
		case E_STATE_S2:
			S2(path, i, j, stkSlashes);
			break;
		case E_STATE_S3:
			S3(path, i, j, stkSlashes);
			break;
		case E_STATE_S4:
			S4(path, i, j, stkSlashes);
			break;
		case E_STATE_END:
			bFinished = true;
			break;
		case E_STATE_ERROR:
			bFinished = true;
			break;
		default:
			break;
		}
	}
	
	return path;
}

// state machine states
void Solution::S0(string& path, int &i, int &j, stack<int>& stkSlashes)
{
	i = 0;
	j = -1;
	if(path[i] == '/')
		m_eStatue = E_STATE_S1;
	else
		m_eStatue = E_STATE_ERROR;
}

void Solution::S1(string& path, int &i, int &j, stack<int>& stkSlashes)
{
	if(stkSlashes.empty())
	{
		stkSlashes.push(i);
		j = i;
	}
	else if(stkSlashes.top() != j)
	{
		if(j < i-1)
			path[j+1] = path[i];
		++j;
		stkSlashes.push(j);
	}
	
	if(i == path.size()-1)
	{
		if(stkSlashes.top()==j && stkSlashes.size()>1)
			--j;
		path.erase(j+1);
		m_eStatue = E_STATE_END;
	}
	else
	{
		++i;
		if(path[i] == '.')
			m_eStatue = E_STATE_S2;
		else if(path[i] == '/')
			m_eStatue = E_STATE_S1;
		else 
			m_eStatue = E_STATE_S3;
	}
	
}


void Solution::S2(string& path, int &i, int &j, stack<int>& stkSlashes)
{
	// ******/.
	if(i == path.size()-1)
	{
		if(stkSlashes.size() > 1)
			--j;
		path.erase(j+1);
		m_eStatue = E_STATE_END;
		return;
	}
	
	// **********/./
	++i;
	if(path[i] == '/')
	{
		m_eStatue = E_STATE_S1;
		return;
	}
	else if(path[i] == '.')
	{
		m_eStatue = E_STATE_S4;
		return;
	}
	else // ******/.abc
	{	
		// include the .
		if(j < i-2)
			path[j+1] = path[i-1];
		++j;
		m_eStatue = E_STATE_S3;
	}
}
void Solution::S3(string& path, int &i, int &j, stack<int>& stkSlashes)
{
	if(j < i-1)
		path[j+1] = path[i];
	++j; // include the new character
	
	if(i == path.size()-1)
	{
		path.erase(j+1);
		m_eStatue = E_STATE_END;
		return;
	}
	
	++i;
	if(path[i] == '/')
	{
		m_eStatue = E_STATE_S1;
		return;
	}
	m_eStatue = E_STATE_S3; //stay in state3
}

void Solution::S4(string& path, int &i, int &j, stack<int>& stkSlashes)
{
	// *****/..
	if(i == path.size()-1)
	{
		// ******/
		if(stkSlashes.size() == 1)
		{
			path.erase(j+1);
			m_eStatue = E_STATE_END;
			return;
		}
		else
		{
			stkSlashes.pop();
			j = stkSlashes.top();
			if(stkSlashes.size() == 1)
				path.erase(j+1);
			else
				path.erase(j);
			m_eStatue = E_STATE_END;
			return;
		}
	}
	//
	++i;
	if(path[i] == '/')
	{
		// ************/../
		if(stkSlashes.size() > 1)
			stkSlashes.pop();
		j = stkSlashes.top();
		m_eStatue = E_STATE_S1;
		return;
	}
	
	if(j < i-3)
	{
		path[j+1] = path[i-2];
		path[j+2] = path[i-1];
		j += 2;
	}
	else
		j = i -1;
		
	
	
}
void Solution::END(string& path, int &i, int &j, stack<int>& stkSlashes)
{
}
void Solution::ERROR(string& path, int &i, int &j, stack<int>& stkSlashes)
{
}
