//*!slot:dirname:__class_name__/__method_name__*/
//*!slot:type:__class_name__::__name__*/
//*!slot:name:__method_name__*/

/*!file:__class_name__/header.h*/
/*!ignore*/
class Net {
    /*!ignore*/
    void init();
    class __name__;
    MessageResult message___method_name__(ThisObj this_obj, MessageArguments arguments);
    /*?__method__*/

    /*!ignore*/
};

/*!file:__dirname__/header.h*/
#include "__class_name__/header.h"
#include "net_method.h"
namespace PNtalk {
class __type__ : public Method {
  public:
    __name__(Places places);
    /*?__net__*/
};

} // namespace PNtalk

//*!file:__dirname__/init.cpp*/
#include "__dirname__/header.h"
using namespace PNtalk;

__type__::__name__(Places places) : Method(places) {
    /*?__net__*/
}

/*!file:__class_name__/init.cpp*/
/*!ignore*/
{
    message_translator["__method_name__"] = &__class_name__::message___method_name__;
    /*?__method__*/
    /*!ignore*/
}

/*!file:__class_name__/message___method_name__.cpp*/
#include "__class_name__/header.h"
#include "__dirname__/header.h"
#include "__dirname__/return/header.h"
#include "net_multiset.h"
#include "object.h"
#include <condition_variable>
#include <iostream>

using namespace PNtalk;

MessageResult __class_name__::message___method_name__(ThisObj this_obj, MessageArguments arguments) {
    MessageResult res = make_shared_obj();
    auto m = __type__(_places);
    m.distribute_self(this_obj);
    /*? auto it = arguments.begin(); __argument__*/
    auto return_place = m.place("return");

    m.schedule();
    {
        std::unique_lock<std::mutex> lk(return_place->m);
        return_place->cv.wait(lk, [&] { return return_place->_values.size() > 0; });
    }
    return_place->pop(std::weak_ptr<Net::Transition>(), MultiSet({MultiSetPair(res)}));

    return res;
}

/*!file:object/object_variant.h*/
#include "__dirname__/header.h"
/*?__place__*/
/*?__transition__*/
/*?__method__*/
