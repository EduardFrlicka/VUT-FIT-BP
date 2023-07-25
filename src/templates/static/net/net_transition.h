#pragma once

#include "net_PN.h"
#include "object_base.h"

namespace PNtalk {
class PN::Transition {
    virtual bool check();
    virtual void execute();
};

} // namespace PNtalk