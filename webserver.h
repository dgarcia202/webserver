
#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include <string>
#include <sstream>

using namespace std;

#define NEWLINE "\n"

#define STR(x) static_cast<ostringstream&>(ostringstream() << dec << x).str()

class webserver
{
	public:
		struct httpRequest
		{
			string method;
		};

		
		webserver(unsigned int port, void (*handler)(httpRequest*));

	private:
		unsigned __stdcall requestProcessor(void *pScket);
		void (*requestHandler)(httpRequest*);
};

#endif