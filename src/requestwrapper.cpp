#include <regex>

#include "webserver.h"
#include "requestwrapper.h"
#include "socket.h"
#include "logger.h"
#include "stringtools.h"

namespace dynws
{
	Logger RequestWrapper::l_ = Logger();

	void RequestWrapper::ParseRequestHeadLine(HttpRequest &request, const std::string line)
	{
		std::vector<std::string> pieces = strtools::strsplit(line, ' ');
		request.method = pieces[0];
		request.uri = pieces[1];
		request.http_version = pieces[2];

		size_t question_mark_pos = request.uri.find("?");
		if (question_mark_pos != std::string::npos)
		{
			request.query_string = request.uri.substr(question_mark_pos + 1);
			ParseQueryString(request, request.query_string);
		}
		request.path = request.uri.substr(0, question_mark_pos);
	}

	void RequestWrapper::ParseHeader(HttpRequest &request, std::string line)
	{
		size_t separator_pos = line.find(":");
		std::string key = strtools::trim_cp(line.substr(0, separator_pos));
		std::string value = strtools::trim_cp(line.substr(separator_pos + 1));
		if (strtools::toupper_cp(key) == "HOST")
		{
			request.host = value;
		}
		else
		{
			request.headers.insert(std::pair<std::string, std::string>(key, value));
		}
	}

	void RequestWrapper::ParseQueryString(HttpRequest &request, const std::string query_string)
	{/*
		std::smatch match;
		std::regex expr("([^&]*)=([^&]*)");
		std::regex_match(query_string, match, expr);*/
	}

	void RequestWrapper::TransmitResponse(Socket &s, const HttpResponse &response)
	{
		s.SendBytes("HTTP/1.1 ");
		s.SendLine(response.status);
		s.SendLine("");
		s.SendLine(response.body);
		s.Close();
	}

	void RequestWrapper::ExecuteControllerAction(HttpRequest &request, HttpResponse &response, Router &router)
	{
		Controller *ctrl = router.ResolveController(request.uri);
		ctrl->Action(request, response);
		delete ctrl;
	}

	void RequestWrapper::Process(Socket &s, Router &router)
	{
		HttpRequest request;
		HttpResponse response;

		int lines_count = 0;
		bool reading_body = false;
		while (true)
		{
			std::string line = reading_body ? s.ReceiveBytes() : s.ReceiveLine();
			lines_count++;

			if (reading_body && line.empty())
			{
				break;
			}

			if (line.find_first_of("\x0a\x0d") == 0)
			{
				reading_body = true;
				continue;
			}

			if (lines_count == 1)
			{
				ParseRequestHeadLine(request, line);
			}
			else if (!reading_body)
			{
				ParseHeader(request, line);
			}
			else
			{
				request.body += line;
			}

			l_.debugBytes(STR(line));
		}

		ExecuteControllerAction(request, response, router);
		TransmitResponse(s, response);
	}

}	// namespece dynws
