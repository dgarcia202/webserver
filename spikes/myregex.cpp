#include <iostream>
#include <string>
#include <regex>

int main()
{
  std::string s("id=123&name=abcde");
  std::regex expr("([^=])");
  std::smatch m;

  std::regex_match(s, m, expr);
  std::cout << "Matches found " << m.size() << std::endl;

  for (auto it = m.cbegin(); it != m.cend(); ++it) {
    std::cout << "item ->" << *it << std::endl;
  }
}
