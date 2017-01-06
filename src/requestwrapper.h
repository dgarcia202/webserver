#ifndef __DYNWS_REQWRAPPER_H__
#define __DYNWS_REQWRAPPER_H__

#include "socket.h"

namespace dynws
{
	class RequestWrapper
	{
		public:
			void Process(Socket&, Router&);

		private:
			static Logger l_;
			void ParseRequestHeadLine(HttpRequest&, std::string);
			void ParseHeader(HttpRequest&, std::string);
			void ParseQueryString(HttpRequest&, std::string);
			void TransmitResponse(Socket&, HttpResponse&);
	};

}	// namespace dynws

#endif
