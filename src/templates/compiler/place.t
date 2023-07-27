//*!slot:dirname:__class_name__//*?__net_name__/*/__place_name__*/
//*!slot:type:__class_name__::/*?__net_name__::*/Place___place_name__*/

/*!file:__class_name__/header.h*/
/*!ignore*/
class Net {
    /*!ignore*/
    void init();
    class Place___place_name__;
    std::shared_ptr<Place___place_name__> place___place_name__;
    /*?__place__*/

    /*!ignore*/
};

//*!file:__class_name__//*?__net_name__/*/init.cpp*/
/*!ignore*/
void Net::init() {
    place___place_name__ = std::make_shared<Place___place_name__>();
    _places["__place_name__"] = place___place_name__.
    /*?__place__*/
    /*!ignore*/
}
/*!file:__dirname__/__place_name__.h*/
#include "__class_name__/*?/__net_name__*//header.h"
#include "net_place.h"

namespace PNtalk {
class __type__ : public PN::Place {
    Place___place_name__();
    void update();
};
} // namespace PNtalk

/*!file:object/object_variant.h*/
#include "__dirname__/__place_name__.h"
/*?__place__*/