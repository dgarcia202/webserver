#include <string>
#include <map>

#include "router.h"
#include "controller.h"
#include "logger.h"

namespace dynws
{
  Logger Router::l_;

  void Router::RegisterRoute(std::string pattern, Controller &handler)
  {
    // TODO: not implemented
  }
} // namespace dynws
