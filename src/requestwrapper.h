#ifndef __DYNWS_REQWRAPPER_H__
#define __DYNWS_REQWRAPPER_H__

#include "socket.h"

#define JSON_DEFAULT_INDENT 3

namespace dynws
{
	class RequestWrapper
	{
		public:
			void Process(Socket&, Router&);

		private:
			static Logger l_;
			void ParseRequestHeadLine(HttpRequest&, const std::string);
			void ParseHeader(HttpRequest&, const std::string);
			void ParseQueryString(HttpRequest&, const std::string);
			void TransmitResponse(Socket&, HttpResponse&);
			void SetResponseContentHeaders(HttpResponse&, std::size_t);
	};

}	// namespace dynws

#endif
