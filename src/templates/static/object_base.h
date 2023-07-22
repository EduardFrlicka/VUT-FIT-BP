#pragma once
#include <atomic>
#include <deque>
#include <map>
#include <string>

namespace PN {

class Object;

extern std::atomic<long> id_counter;

class ObjectBase {
  protected:
    long id;
    std::map<std::string, Object (ObjectBase::*)(const std::deque<Object> &)> message_translator;

  public:
    ObjectBase();
    virtual Object message(const std::string &, const std::deque<Object> &);

    virtual Object _eq_identity_(const std::deque<Object> &);
    virtual Object _neq_identity_(const std::deque<Object> &);

    virtual ~ObjectBase(){};
};

} // namespace PN
