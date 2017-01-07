#include <iostream>
#include <string>
#include <regex>

int main()
{
  std::string s("/home?id=123&name=abcde");
  std::regex expr("[(\\?|\\&)]([^=]+)\\=([^&#]+)");

  // std::string s = "1526-5268-5552-1523";
  // std::regex expr("(\\d{4}[- ]){3}\\d{4}");

  std::smatch m;

  int match_counter = 0;
  while(std::regex_search(s, m, expr))
  {
    match_counter++;
    // std::cout << "Match found (" << match_counter << ") :" << m.size() << "---" << s << std::endl;
    for (auto it = m.cbegin(); it != m.cend(); ++it) {
      std::cout << "found ->" << *it << std::endl;
    }

    s = m.suffix();
  }
}
