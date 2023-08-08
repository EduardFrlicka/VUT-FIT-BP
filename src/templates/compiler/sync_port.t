//*!slot:dirname:__class_name__/__sync_port_name__*/
//*!slot:type:PNtalk::__class_name__::__sync_port_name__*/

//*!file:__class_name__/header.h*/
/*!ignore*/
class _ {
    class __sync_port_name__;
    class std::shared_ptr<__sync_port_name__> sync___sync_port_name__;
    MessageResult message___sync_port_name__(ThisObj this_obj, MessageArguments arguments);
    /*? __syn_port__ */
    /*!ignore*/
};

/*!file:__dirname__/header.h*/
#include "__class_name__/header.h"
#include "net_place.h"
#include "net_sync_port.h"
#include "net_transition.h"
#include "object_base.h"
/*!ignore*/
using namespace PNtalk;

namespace PNtalk {
class __type__ : public PNtalk::PN::SyncPort {
  public:
    /*?__variable_declaration__*/
    __sync_port_name__(const Places &places);
    __sync_port_name__(const std::set<std::weak_ptr<Net::Transition>, transitions_compare> &update_transitions, std::weak_ptr<Net::Transition> parent);

    std::shared_ptr<Net::Transition> copy();
    void load_arguments(MessageArguments arguments);
    bool check();
    bool execute();
};
} // namespace PNtalk

/*!file: __dirname__/init.cpp*/
#include "__dirname__/header.h"

__type__::__sync_port_name__(const Places &places) : SyncPort(places) {
    name = "__class_name__/__sync_port_name__";
    /*?__variable_declaration__*/
};
__type__::__sync_port_name__(const std::set<std::weak_ptr<Net::Transition>, transitions_compare> &update_transitions, std::weak_ptr<Net::Transition> parent) : SyncPort(update_transitions, parent) {
    name = "__class_name__/__sync_port_name__";
};

/*!file:__class_name__/init.cpp*/
#include "__dirname__/header.h"
/*!ignore*/
{
    message_translator["__sync_port_name__"] = &__class_name__::message___sync_port_name__;
    sync___sync_port_name__ = std::make_shared<__sync_port_name__>(__sync_port_name__(_places));
    /*? __syn_port__*/
    /*!ignore*/
}
/*!file:__class_name__/message___sync_port_name__.cpp*/
#include "__class_name__/header.h"
#include "__dirname__/header.h"
#include "net_multiset.h"
#include "object.h"
#include <mutex>

using namespace PNtalk;

MessageResult __class_name__::message___sync_port_name__(ThisObj this_obj, MessageArguments arguments) {
    std::lock_guard<std::mutex>(sync___sync_port_name__->m);
    // if (arguments.back()->is_type<std::weak_ptr<Net::Transition>>())
    //     link_to_transition(arguments.back()->get<std::weak_ptr<Net::Transition>>());

    sync___sync_port_name__->load_arguments(arguments);

    if (!sync___sync_port_name__->check())
        return make_shared_obj(Bool(false));

    return make_shared_obj(Bool(sync___sync_port_name__->execute()));
}

/*!file:__dirname__/load_arguments.cpp*/
#include "__dirname__/header.h"
#include "object.h"

using namespace PNtalk;
void __type__::load_arguments(MessageArguments arguments) {
    auto it = arguments.begin();
    /*?__sync_port_argument__*/
    if (it == arguments.end())
        return;
    link_to_transition((*it)->get<std::weak_ptr<Net::Transition>>());
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
    auto res = std::make_shared<__type__>(__type__(_update_transitions, top_parent()));

    return res;
};

/*!file: __dirname__/execute.cpp */
#include "__dirname__/header.h"

using namespace PNtalk;
bool __type__::execute() {
    /*?__pre_cond__*/
    /*?__cond__*/
    /*?__action__*/
    /*?__post_cond__*/
    return true;
};

/*!file:object/object_variant.h*/
#include "__dirname__/header.h"
/*?__syn_port__*/