#pragma once
#include <atomic>
#include <deque>
#include <map>
#include <memory>
#include <string>

#define make_shared_obj(object) std::make_shared<PNtalk::Object>(PNtalk::Object(object))
namespace PNtalk {

class Object;
typedef const std::deque<std::shared_ptr<Object>> &MessageArguments;
typedef std::string MessageSelector;
typedef std::shared_ptr<Object> MessageResult;
typedef std::shared_ptr<Object> Variable;
typedef const std::shared_ptr<Object> &ThisObj;

class ObjectBase {
  public:
  protected:
    template <class T> using MessageTranslator = std::map<std::string, MessageResult (T::*)(ThisObj, MessageArguments)>;

    MessageTranslator<ObjectBase> message_translator;

  public:
    ObjectBase();
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);

    MessageResult _eqi_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _neqi_(ThisObj this_obj, MessageArguments arguments);

    virtual MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
        return MessageResult();
    };
    MessageResult doesNotUnderstand_default(ThisObj this_obj, MessageArguments arguments);

    ~ObjectBase(){};
};

} // namespace PNtalk
