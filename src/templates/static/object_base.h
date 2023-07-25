#pragma once
#include <atomic>
#include <deque>
#include <map>
#include <memory>
#include <string>

namespace PNtalk {

class Object;

// extern std::atomic<long> id_counter;

class ObjectBase {
  protected:
    // long id;
    typedef const std::deque<std::shared_ptr<Object>> &MessageArguments;
    template <class T> using MessageTranslator = std::map<std::string, std::shared_ptr<Object> (T::*)(std::weak_ptr<Object>, MessageArguments)>;

    MessageTranslator<ObjectBase> message_translator;

  public:
    ObjectBase();
    virtual std::shared_ptr<Object> message(std::weak_ptr<Object> this_obj, const std::string &message_selector, MessageArguments arguments);

    virtual std::shared_ptr<Object> _eq_identity_(std::weak_ptr<Object> this_obj, MessageArguments arguments);
    virtual std::shared_ptr<Object> _neq_identity_(std::weak_ptr<Object> this_obj, MessageArguments arguments);

    virtual ~ObjectBase(){};
};

} // namespace PNtalk
