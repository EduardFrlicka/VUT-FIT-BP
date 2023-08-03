#pragma once
#include "object_base.h"
#include <map>
#include <memory>

namespace PNtalk {

class Net {
  public:
    class Transition;
    class Place;

    typedef std::map<std::string, std::weak_ptr<Place>> Places;
    typedef std::deque<std::shared_ptr<Transition>> Transitions;
    Places _places;

    Net();
    Net(Places places);

    void distribute_self(std::weak_ptr<Object> this_obj);
    std::shared_ptr<Place> place(const std::string &name);

    void add_place(std::string name, std::shared_ptr<Place> place);
    void add_transition(std::shared_ptr<Transition> transition);
    void schedule();

  protected:
    std::deque<std::shared_ptr<Place>> _local_places;
    std::deque<std::shared_ptr<Transition>> transitions;
};

} // namespace PNtalk
