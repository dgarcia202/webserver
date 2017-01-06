#ifndef __DYNWS_CONTROLLER_H__
#define  __DYNWS_CONTROLLER_H__

namespace dynws
{
  class Controller
  {
  public:
    virtual void Action(HttpRequest&, HttpResponse&) = 0;
  }
} // namespace dynws

#endif
