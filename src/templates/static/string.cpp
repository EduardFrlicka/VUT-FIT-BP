#include "string.h"
#include "object.h"

// PN::Object PN::String::message(const std::string &message_selector, const std::deque<PN::Object> &arguments) {
//     if (message_selector == "at")
//         return at(arguments);
//     return PN::Object();
// }

PN::Object PN::String::message(const std::string &message_selector, const std::deque<PN::Object> &arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(message_selector, arguments);
    }

    (this->*(message_translator[message_selector]))(arguments);

    return Object();
}

PN::Object PN::String::at(const std::deque<PN::Object> &) {
    std::cout << "at" << std::endl;
    return PN::Object();
}

PN::String::String() : super() {
    message_translator["at"] = &String::at;
};
