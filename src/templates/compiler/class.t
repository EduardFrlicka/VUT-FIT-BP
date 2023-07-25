/*!file:__class_name__.h*/
#include "object.h"
/*!newline*/

namespace PNtalk {

class __class_name__ : public __base_class_name__ {
    /*? __object__ */
    __class_name__();
    /*? __method__*/
    /*? __constructor__*/
    /*? __syn_port__*/

    MessageTranslator<__class_name__> message_translator;
    virtual std::shared_ptr<Object> message(std::weak_ptr<Object> this_obj, const std::string &message_selector, const std::deque<Object> &arguments);
};
} // namespace PN


/*!file:__class_name___init.cpp*/
#include "__class_name__.h"
PNtalk::__class_name__::__class_name__(){
    /*?__object__*/
}

/*!file:__class_name___message.cpp*/
#include "__class_name__.h"

std::shared_ptr<Object> ObjectBase::message(std::weak_ptr<Object> this_obj, const std::string &message_selector, const std::deque<Object> &arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        std::cout << "FAILED " << message_selector << std::endl;
        exit(1);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

