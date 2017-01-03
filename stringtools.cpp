#include <string>
#include <locale>

void ltrim(std::string &s)
{
	std::locale loc;
}

void rtrim(std::string &s)
{
	
}

void trim(std::string &s)
{
	
}

void to_upper(std::string &s)
{
	std::locale loc;
	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		s[i] = std::toupper(s[i], loc);
	}
}

void to_lower(std::string &s)
{
	std::locale loc;
	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		s[i] = std::tolower(s[i], loc);
	}	
}