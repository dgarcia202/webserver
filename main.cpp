#include <iostream>

#include "DynWS.h"

using namespace std;

void handler(DynWS::HttpRequest *request)
{
	cout << request->Method;
}

int main() 
{
	DynWS(8886, &handler);
}