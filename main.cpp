#include <iostream>

#include "webserver.h"

using namespace std;

void handler(webserver::httpRequest *request)
{
	cout << request->method;
}

int main() 
{
	webserver(8886, &handler);
}