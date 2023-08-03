//*!slot:dirname:__class_name__/*?/__net_name__*//__transition_name__*/
//*!slot:type:PNtalk::__class_name__::/*?__net_name__::*/__transition_name__*/7

//*!file:__class_name__/*?/__net_name__*//header.h*/
/*!ignore*/
class _ {
    class __transition_name__;
    /*? __transition__ */
    /*!ignore*/
};

/*!file:__dirname__/header.h*/
#include "__class_name__/*?/__net_name__*//header.h"
#include "net_place.h"
#include "net_transition.h"
#include "object_base.h"
/*!ignore*/
using namespace PNtalk;

namespace PNtalk {
class __type__ : public PNtalk::Net::Transition {
  public:
    /*?__variable_declaration__*/
    /*?__action__*/
    __transition_name__(const Places &places);
    __transition_name__(const Places &places, std::weak_ptr<Transition> parent);

    std::shared_ptr<Net::Transition> copy();
    bool check();
    bool execute();
};
} // namespace PNtalk

/*!file: __dirname__/init.cpp*/
#include "__dirname__/header.h"

__type__::__transition_name__(const Places &places) : Transition(places) {
    name = "__dirname__";
    /*?__variable_declaration__*/
};

__type__::__transition_name__(const Places &places, std::weak_ptr<Transition> parent) : Transition(places, parent) {
    name = "__dirname__";
    /*?__variable_declaration__*/
};

//*!file:__class_name__/*?/__net_name__*//init.cpp*/
#include "__dirname__/header.h"
/*!ignore*/
{
    add_transition(std::make_shared<__type__>(__type__(_places)));
    /*?__transition__*/
    /*!ignore*/
}

/*!file: __dirname__/check.cpp */
#include "__dirname__/header.h"

using namespace PNtalk;
bool __type__::check() {
    /*?__pre_cond__*/
    /*?__cond__*/
    /*?__guard__*/

    return true;
};

/*!file: __dirname__/copy.cpp */
#include "__dirname__/header.h"

using namespace PNtalk;
std::shared_ptr<Net::Transition> __type__::copy() {
    return std::make_shared<__type__>(__type__(_places, top_parent()));
};

/*!file:__dirname__/link.cpp*/

/*!file: __dirname__/execute.cpp */
#include "__dirname__/header.h"

using namespace PNtalk;
bool __type__::execute() {
    /*?__pre_cond__*/
    /*?__cond__*/
    /*?__guard__*/
    /*?__action__*/
    /*?__post_cond__*/
    return true;
};

/*!file:object/object_variant.h*/
#include "__dirname__/header.h"
/*?__transition__*/