#include <iostream>

#include "DynWS.h"

using namespace std;

void handler(DynWS::HttpRequest *request, DynWS::HttpResponse *response)
{
	cout << request->Method;
	response->Status = "200 OK";
	response->Body = "<h1>Hello World!!</h1>";
}

int main() 
{
	DynWS(8886, &handler);
}