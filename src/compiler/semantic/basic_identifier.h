#pragma once
#include <string>

class BasicIdentifier {
  public:
    std::string name;

    BasicIdentifier();
    BasicIdentifier(const std::string &);

    bool is_upper() const;
    bool is_lower() const;

    // bool operator==(const BasicIdentifier &);
    const BasicIdentifier &operator+=(const BasicIdentifier &);
};