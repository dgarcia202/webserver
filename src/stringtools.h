
#ifndef __STRINGTOOLS_H__
#define __STRINGTOOLS_H__

#include <string>
#include <vector>
#include <sstream>

#define STR(x) static_cast<ostringstream&>(ostringstream() << dec << x).str()

namespace strtools
{
	void ltrim(std::string &s);
	void rtrim(std::string &s);
	void trim(std::string &s);
	void toupper(std::string &s);
	void tolower(std::string &s);
	std::vector<std::string> strsplit(std::string s, char delim);
	std::string ltrim_cp(std::string s);
	std::string rtrim_cp(std::string s);
	std::string trim_cp(std::string s);
	std::string toupper_cp(std::string s);
	std::string tolower_cp(std::string s);
}

#endif