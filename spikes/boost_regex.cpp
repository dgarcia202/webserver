#include <boost/regex.hpp>
#include <string>
#include <iostream>

int main()
{
  std::string s = "/home?id=123&name=abcde";
  // std::string s = "1526-5268-5552-1523";
  boost::regex expr("[=]?\\w*[=]?");
  std::cout << std::boolalpha << boost::regex_search(s, expr) << '\n';
}
