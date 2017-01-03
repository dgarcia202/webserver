
#ifndef __STRINGTOOLS_H__
#define __STRINGTOOLS_H__

#include <string>
#include <sstream>

#define NEWLINE "\n"

#define STR(x) static_cast<ostringstream&>(ostringstream() << dec << x).str()


void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);
void to_upper(std::string &s);
void to_lower(std::string &s);

#endif