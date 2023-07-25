#include "object_base.h"

namespace PNtalk {
class Integer : public ObjectBase {
  public:
    int _value;

    MessageTranslator<Integer> message_translator;
    virtual std::shared_ptr<Object> message(std::weak_ptr<Object> this_obj, const std::string &message_selector, const std::deque<Object> &arguments);

    Integer();
    Integer(int value);
};

} // namespace PNtalk
