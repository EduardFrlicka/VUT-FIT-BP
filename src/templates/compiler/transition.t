//*!slot:dirname:__class_name__/*?/__net_name__*//__transition_name__*/
//*!slot:type:PNtalk::__class_name__::/*?__net_name__::*/__transition_name__*/7

/*!file:__class_name__/header.h*/
/*!ignore*/
class _ {
    class __transition_name__;
    /*? __transition__ */
    /*!ignore*/
};

/*!file:__dirname__/__transition_name__.h*/
#include "__class_name__/header.h"
#include "net_place.h"
#include "net_transition.h"
#include "object_base.h"
/*!ignore*/
using namespace PNtalk;

namespace PNtalk {
class __type__ : public PNtalk::PN::Transition {
    /*?__variable_declaration__*/
    __transition_name__(const Places &places);

    inline std::string name() {
        return "/*?__net_name__/*/__transition_name__";
    };
    std::shared_ptr<PNtalk::PN::Transition> copy();
    bool check();
    void execute();
};
} // namespace PNtalk

/*!file: __dirname__/init.cpp*/
#include "__dirname__/__transition_name__.h"

__type__::__transition_name__(const Places &places)
    : Transition(places){
          /*?__variable_declaration__*/
      };

/*!file: __dirname__/check.cpp */
#include "__dirname__/__transition_name__.h"

bool __type__::check() {
    /*?__pre_cond__*/
    /*?__cond__*/

    return true;
};

/*!file: __dirname__/execute.cpp */
#include "__dirname__/__transition_name__.h"

void __type__::execute(){
    /*?__pre_cond__*/
    /*?__cond__*/
    /*?__post_cond__*/

};

/*!file:object/object_variant.h*/
#include "__dirname__/__transition_name__.h"
/*?__transition__*/