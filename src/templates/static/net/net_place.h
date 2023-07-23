#include "object.h"
#include <deque>
#include <memory>

namespace PN {

class MultiSetItem;

class MultiSetList{
    std::deque<MultiSetItem> values;

};  

class MultiSetItem {

};

class Place {
    std::deque<std::shared_ptr<Object>> values;

    virtual void update();
};

class PlaceTransaction {
    PlaceTransaction(Place &place);

    Place &p;
    std::deque<std::shared_ptr<Object>>::iterator it;
    bool passed = true;

    bool try_pop(const Object &value, unsigned int count = 1);
    bool try_pop(std::shared_ptr<Object> &bind, unsigned int count = 1);
    bool pop(const Object &value, unsigned int count = 1);
    bool pop(std::shared_ptr<Object> &bind, unsigned int count = 1);
    bool match(const Object &value, unsigned int count = 1);
    bool match(std::shared_ptr<Object> &bind, unsigned int count = 1);
    bool push(const Object &value, unsigned int count = 1);
    bool push(std::shared_ptr<Object> &bind, unsigned int count = 1);

};

} // namespace PN
