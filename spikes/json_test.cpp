#include <iostream>

#include "json/json.hpp"

using json = nlohmann::json;

// g++ -std=c++11 json_test.cpp -o json_test.exe
int main()
{
/*
  auto j = R"(
    {
      "happy": true,
      "pi": 3.141,
      "cula": "caca"
    }
  )"_json;*/

  auto j = "{ \"mylist\" : [1, 2, 3, 4, 5] }"_json;

  std::cout << j["mylist"][3] << std::endl;
  /*std::cout << j["happy"] << std::endl;
  std::cout << j["cula"] << std::endl;*/
}
