#pragma once

#include "net_PN.h"
#include "object_base.h"
#include <memory>

namespace PNtalk {
class PN::Transition : public std::__enable_shared_from_this<PN::Transition> {
  protected:
    typedef std::map<std::string, std::weak_ptr<PN::Place>> Places;

    Transition(Places places);

    bool match(const std::string &place, const MultiSet &multiset);
    bool pop(const std::string &place, const MultiSet &multiset);
    void push(const std::string &place, const MultiSet &multiset);
    virtual std::string name() = 0;
    virtual std::shared_ptr<Transition> copy() = 0;
    virtual bool check() = 0;
    virtual void execute() = 0;

  private:
    Places _places;
};

} // namespace PNtalk