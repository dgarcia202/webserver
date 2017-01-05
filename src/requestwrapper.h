#ifndef __DYNWS_REQWRAPPER_H__
#define __DYNWS_REQWRAPPER_H__

#include "socket.h"

namespace dynws
{
	class RequestWrapper
	{
		public:
			void Process(Socket &, RequestHandler);

		private:
			static Logger l_;
	};

}	// namespace dynws

#endif