#pragma once
#include "object_base.h"

namespace PNtalk {
class Array : public ObjectBase {
  public:
    typedef ObjectBase super;
    std::deque<std::shared_ptr<Object>> _values;

    Array();
    Array(const std::deque<std::shared_ptr<Object>> &values);

    MessageTranslator<Array> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);

    /* Initialization */
    MessageResult new_(ThisObj this_obj, MessageArguments arguments);
    MessageResult with_(ThisObj this_obj, MessageArguments arguments);
    MessageResult with_with_(ThisObj this_obj, MessageArguments arguments);
    MessageResult with_with_with_(ThisObj this_obj, MessageArguments arguments);
    MessageResult with_with_with_with_(ThisObj this_obj, MessageArguments arguments);
    MessageResult with_with_with_with_with_(ThisObj this_obj, MessageArguments arguments);
    MessageResult with_with_with_with_with_with_(ThisObj this_obj, MessageArguments arguments);
    MessageResult withAll_(ThisObj this_obj, MessageArguments arguments);

    /* Accessing, Editing */
    MessageResult isEmpty(ThisObj this_obj, MessageArguments arguments);
    MessageResult size(ThisObj this_obj, MessageArguments arguments);
    MessageResult at_(ThisObj this_obj, MessageArguments arguments);
    MessageResult at_put_(ThisObj this_obj, MessageArguments arguments);
    MessageResult add_(ThisObj this_obj, MessageArguments arguments);
    MessageResult addAll_(ThisObj this_obj, MessageArguments arguments);
    MessageResult remove_(ThisObj this_obj, MessageArguments arguments);
    MessageResult removeAll_(ThisObj this_obj, MessageArguments arguments);

    /* Enumerating */
    MessageResult do_(ThisObj this_obj, MessageArguments arguments);
    // MessageResult collect_(ThisObj this_obj, MessageArguments arguments);
    // MessageResult select_(ThisObj this_obj, MessageArguments arguments);
    // MessageResult reject_(ThisObj this_obj, MessageArguments arguments);
    // MessageResult detect_(ThisObj this_obj, MessageArguments arguments);

    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};

} // namespace PNtalk
