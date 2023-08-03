#pragma once

#include "net_net.h"
#include "net_place.h"
#include "object_base.h"
#include <iostream>
#include <memory>

namespace PNtalk {
class Net::Transition : public std::enable_shared_from_this<Transition> {
  public:
    std::string name = "Transition";
    std::weak_ptr<Object> this_obj;
    Transition(Places places);
    Transition(Places places, std::weak_ptr<Transition> parent);
    virtual std::shared_ptr<Transition> copy() = 0;
    //  {
    //     std::cout << name << std::endl;
    //     return std::shared_ptr<Transition>();
    // };

    virtual bool scheduler_check();
    virtual bool scheduler_execute();
    std::shared_ptr<Transition> top_parent();

  protected:
    virtual bool check() = 0;
    virtual bool execute() = 0;
    bool match(const std::string &place, const MultiSet &multiset);
    bool pop(const std::string &place, const MultiSet &multiset);
    void push(const std::string &place, const MultiSet &multiset);

    std::weak_ptr<Transition> _parent;
    Places _places;
};

} // namespace PNtalk