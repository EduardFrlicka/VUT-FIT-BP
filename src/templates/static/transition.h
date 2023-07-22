#pragma once
namespace PN {

class Transition {
    virtual bool check_conditions();
    virtual bool execute();
};
} // namespace PN
