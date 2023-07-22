#include "basic_identifier.h"

BasicIdentifier::BasicIdentifier() : name() {
}

BasicIdentifier::BasicIdentifier(const std::string &_name) : name(_name) {
}

bool BasicIdentifier::is_upper() const {
    if (name.size() <= 0)
        return false;
    return isupper(*name.begin());
}

bool BasicIdentifier::is_lower() const {
    if (name.size() <= 0)
        return false;
    return islower(*name.begin());
}

const BasicIdentifier &BasicIdentifier::operator+=(const BasicIdentifier &other) {
    if (name != other.name)
        name += other.name;
    return *this;
}

// bool BasicIdentifier::operator==(const BasicIdentifier &other) {
//     return name == other.name;
// }

// const BasicIdentifier &BasicIdentifier::operator=(const BasicIdentifier &other) {
//     name = other.name;
//     return *this;
// }
// const BasicIdentifier &BasicIdentifier::operator+=(const BasicIdentifier &other) {
//     name += IDENTIFIER_DELIMITER + other.name;
//     return *this;
// }
// BasicIdentifier BasicIdentifier::operator+(const BasicIdentifier &other) {
//     return BasicIdentifier(name + IDENTIFIER_DELIMITER + other.name);
// }
