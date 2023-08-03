#include "object.h"
#include <chrono>
#include <thread>
using namespace PNtalk;

MessageResult PNtalk::Object::message(const MessageSelector &message_selector, MessageArguments arguments) {
    if (is_type<PNtalk::String>())
        return get<PNtalk::String>().message(shared_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Bool>())
        return get<PNtalk::Bool>().message(shared_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Integer>())
        return get<PNtalk::Integer>().message(shared_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Character>())
        return get<PNtalk::Character>().message(shared_from_this(), message_selector, arguments);
    if (is_type<PNtalk::String>())
        return get<PNtalk::String>().message(shared_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Symbol>())
        return get<PNtalk::Symbol>().message(shared_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Array>())
        return get<PNtalk::Array>().message(shared_from_this(), message_selector, arguments);
    if (is_type<PNtalk::CodeBlock>())
        return get<PNtalk::CodeBlock>().message(shared_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Transcript>())
        return get<PNtalk::Transcript>().message(shared_from_this(), message_selector, arguments);
    /*?__generated__*/

    std::cout << "Object failed to match class" << std::endl;
    std::cout << "Message: " << message_selector << std::endl;
    if (!_value)
        std::cout << "Empty " << std::endl;

    throw std::invalid_argument("Object failed to match class. Messga: " + message_selector);
}