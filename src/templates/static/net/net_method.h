#include "net_PN.h"
#include "net_net.h"
#include "object_base.h"
#include <memory>

namespace PNtalk {

class PN::Method : public Net {
  public:
    Method(Places places);
};

} // namespace PNtalk
