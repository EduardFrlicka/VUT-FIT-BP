//*!file:__class_name__/*?/__net_name__*//header.h*/
#include "net_PN.h"
namespace PNtalk {

class __class_name__ : public __base_class_name__ {
  public:
    typedef __base_class_name__ super;
    /*? __object__ */
    __class_name__();
    /*? __method__*/
    /*? __constructor__*/
    /*? __syn_port__*/

    MessageTranslator<__class_name__> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);
    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _eq_(ThisObj this_obj, MessageArguments arguments);
};
} // namespace PNtalk

/*!file:__class_name__/init.cpp*/
#include "header.h"

PNtalk::__class_name__::__class_name__() : PN() {
    message_translator["doesNotUnderstand_"] = &__class_name__::doesNotUnderstand_;
    message_translator["_eq_"] = &__class_name__::_eq_;
    /*?__object__*/
    /*?__method__*/
    /*?__constructor__*/
    /*? __syn_port__*/
}

/*!file:__class_name__/message.cpp*/
#include "header.h"
#include "object.h"
using namespace PNtalk;

MessageResult __class_name__::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PNtalk::__class_name__::_eq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(arguments[0]->is_type<__class_name__>()));
}

/*!file:__class_name__/doesNotUnderstand_.cpp*/
#include "header.h"
#include "object.h"
#include <iostream>
using namespace PNtalk;

MessageResult PNtalk::__class_name__::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    std::cout << "__class_name__ does not understand message with selector: " << std::endl;
    return MessageResult();
}

/*!file:object/object.h*/
/*!ignore*/
{
    Object(__class_name__ && value);
    /*?__class__*/
    /*!ignore*/
}

/*!file:object/object.cpp*/
PNtalk::Object::Object(__class_name__ &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};
/*?__class__*/

/*!file:object/object_message.cpp*/
/*!ignore*/
{
    if (is_type<PNtalk::__class_name__>())
        return get<PNtalk::__class_name__>().message(shared_from_this(), message_selector, arguments);
    /*?__class__*/

    /*!ignore*/
}

/*!file:object/object_variant.h*/
#include "header.h"

/*?__object__*/
/*?__method__*/

/*!inline*/
, __class_name__ /*?__class__*/
