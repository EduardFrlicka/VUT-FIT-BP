#include "object.h"
#include <deque>
#include <memory>

namespace PN {

class Place {
    std::deque<PN::Object> values;

    virtual void update();
};

class PlaceTransaction {
    PlaceTransaction();

    std::deque<PN::Object>::iterator it;
    bool pop(const Object &value, unsigned int count = 1);
    bool pop(std::shared_ptr<Object> &bind, unsigned int count = 1);
};

} // namespace PN
