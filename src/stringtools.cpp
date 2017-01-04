#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace strtools
{
	void ltrim(std::string &s)
	{
		s.erase(
			s.begin(), 
			std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace)))
		);
	}

	void rtrim(std::string &s)
	{
	    s.erase(
	    	std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
			s.end()
		);	
	}

	void trim(std::string &s)
	{
	    ltrim(s);
	    rtrim(s);
	}

	void toupper(std::string &s)
	{
		std::locale loc;
		for (std::string::size_type i = 0; i < s.length(); ++i)
		{
			s[i] = std::toupper(s[i], loc);
		}
	}

	void tolower(std::string &s)
	{
		std::locale loc;
		for (std::string::size_type i = 0; i < s.length(); ++i)
		{
			s[i] = std::tolower(s[i], loc);
		}	
	}

	std::string ltrim_cp(std::string s)
	{
		ltrim(s);
		return s;
	}

	std::string rtrim_cp(std::string s)
	{
		rtrim(s);
		return s;
	}

	std::string trim_cp(std::string s)
	{
		trim(s);
		return s;
	}

	std::string toupper_cp(std::string s)
	{
		toupper(s);
		return s;
	}

	std::string tolower_cp(std::string s)
	{
		tolower(s);
		return s;
	}
	
	std::vector<std::string> strsplit(std::string s, char delim)
	{
		std::vector<std::string> tokens;
		std::istringstream iss(s);
		
		copy(std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter(tokens));
		
		return tokens;
	}
	
}	// namespace strtools