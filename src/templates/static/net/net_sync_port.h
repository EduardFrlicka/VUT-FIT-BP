#include "boolean.h"
#include "net_PN.h"
#include "net_place.h"
#include "net_transition.h"

namespace PNtalk {

class PN::SyncPort : public PN::Transition, public PN::Place {
  public:
    SyncPort(Places places);
    SyncPort(const std::set<std::weak_ptr<Net::Transition>, transitions_compare> &update_transitions, std::weak_ptr<Net::Transition> parent);

    bool match(const std::string &place_name, const MultiSet &edge_expr);
    bool pop(const std::string &place_name, const MultiSet &edge_expr);
    void push(const std::string &place_name, const MultiSet &edge_expr);

    virtual void load_arguments(MessageArguments arguments){};
    bool scheduler_check();
    bool scheduler_execute();
};

} // namespace PNtalk
