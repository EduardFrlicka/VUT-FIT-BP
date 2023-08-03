//*!slot:dirname:__class_name__/*?/__net_name__*//__place_name__*/
//*!slot:type:__class_name__::/*?__net_name__::*/__name__*/
//*!slot:name:Place___place_name__*/

//*!file:__class_name__/*?/__net_name__*//header.h*/
/*!ignore*/
class Net {
    /*!ignore*/
    void init();
    class __name__;
    /*?__place__*/

    /*!ignore*/
};

//*!file:__class_name__/*?/__net_name__*//init.cpp*/
#include "__dirname__/header.h"
#include "object.h"
/*!ignore*/
{
    add_place("__place_name__", std::make_shared<__type__>(__type__()));
    /*?__place__*/
    /*!ignore*/
}
/*!file:__dirname__/header.h*/
#include "__class_name__/*?/__net_name__*//header.h"
#include "net_place.h"

namespace PNtalk {
class __type__ : public Net::Place {
  public:
    __name__();
    /*?__init_action__*/
};
} // namespace PNtalk

/*!file:__dirname__/init.cpp*/
#include "__dirname__/header.h"
#include "object.h"

using namespace PNtalk;
__type__::__name__(){

    /*?__init_action__*/
    /*? _values = __init_state__.values;*/
};

/*!file:object/object_variant.h*/
#include "__dirname__/header.h"
/*?__place__*/