#include <string>
#include <map>
#include <regex>

#include "router.h"
#include "controller.h"
#include "logger.h"

namespace dynws
{
  Logger Router::l_;

  void Router::RegisterRoute(std::string pattern, ControllerFactory *ctrl_fatory_ptr)
  {
    route_table_.insert(std::pair<std::string, ControllerFactory *>(pattern, ctrl_fatory_ptr));
  }

  Controller *Router::ResolveController(std::string uri)
  {
    l_.debug("Router resolving URI " + uri);

    for (auto it = route_table_.cbegin(); it != route_table_.cend(); ++it)
    {
      std::regex expr(it->first);
      std::smatch match;

      std::regex_match(uri, match, expr);
      if (!match.empty())
      {
        ControllerFactory *factory = route_table_[it->first];
        return factory->CreateIntance();
      }
    }

    return nullptr;
  }
} // namespace dynws
