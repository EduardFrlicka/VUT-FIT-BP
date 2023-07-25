#include "string.h"
#include "object.h"

// PNtalk::Object PNtalk::String::message(const std::string &message_selector, const std::deque<PNtalk::Object> &arguments) {
//     if (message_selector == "at")
//         return at(arguments);
//     return PNtalk::Object();
// }

using namespace PNtalk;

PNtalk::String::String() : super() {
    message_translator["at"] = &String::at;
}
PNtalk::String::String(std::string value) : String() {
    _value = value;
}

std::shared_ptr<Object> PNtalk::String::message(std::weak_ptr<Object> this_obj, const std::string &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

std::shared_ptr<Object> PNtalk::String::at(std::weak_ptr<Object> this_obj, MessageArguments arguments) {
    std::cout << "string" << std::endl;
    return std::shared_ptr<Object>();
}
