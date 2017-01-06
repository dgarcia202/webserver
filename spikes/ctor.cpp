#include <iostream>

class MyObject
{
public:
  MyObject() { std::cout << "MyObject has been constructed..."; };
};

int main()
{
  MyObject o;
  std::cout << "Hello";
}
