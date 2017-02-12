#include <iostream>
#include <windows.h>

int main(int argc, char const *argv[]) {
  std::cout << "This is the parent process";

  SECURITY_ATTRIBUTES secAttr;

  secAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
  secAttr.lpSecurityDescriptor = NULL;
  secAttr.bInheritHandle = TRUE;

  return 0;
}
