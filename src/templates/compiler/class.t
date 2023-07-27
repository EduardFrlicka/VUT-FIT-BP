/*!file:__class_name__/header.h*/
#include "net_PN.h"
namespace PNtalk {

class __class_name__ : public __base_class_name__ {
    /*? __object__ */
    __class_name__();
    /*? __method__*/
    /*? __constructor__*/
    /*? __syn_port__*/

    MessageTranslator<__class_name__> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);
    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};
} // namespace PNtalk

/*!file:__class_name__/init.cpp*/
#include "header.h"
PNtalk::__class_name__::__class_name__() {
    /*?__object__*/
}

/*!file:__class_name__/message.cpp*/
#include "header.h"
#include "object.h"
using namespace PNtalk;

MessageResult Symbol::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

/*!file:__class_name__/doesNotUnderstand_.cpp*/
#include "header.h"
#include "object.h"
using namespace PNtalk;

MessageResult PNtalk::__class_name__::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    std::cout << "Symbol does not understand message with selector: " << std::endl;
    return MessageResult();
}

/*!file:object/object_variant.h*/
#include "header.h"

/*?__object__*/

/*!inline*/
, __class_name__ /*?__class__*/
