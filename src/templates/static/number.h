#include "object_base.h"

namespace PN {

class Number : public ObjectBase {
    
    virtual Object message(const std::string &, const std::deque<Object> &);

};

} // namespace PN
