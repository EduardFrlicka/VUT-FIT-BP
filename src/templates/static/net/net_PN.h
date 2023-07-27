#pragma once
#include "object_base.h"

namespace PNtalk {
class PN : public ObjectBase {
  public:
    class Transition;
    class Place;

    std::map<std::string, std::weak_ptr<PN::Place>> _places;
};
} // namespace PNtalk
