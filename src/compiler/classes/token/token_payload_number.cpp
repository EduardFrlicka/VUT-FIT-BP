#include "token.h"
#include <climits>
#include <iostream>
#include <math.h>
#include <sstream>

int hex2int(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    return -1;
}

void TokenPayload::numberInit() {
    number = TokenPayloadNumber();
    type = tokenPayloadNum;
}

bool TokenPayloadNumber::isdigit(int c) {
    if (!isalnum(c))
        return false;

    return hex2int(c) < radix;
}

void TokenPayloadNumber::append(int c) {
    data += c;
}

void TokenPayloadNumber::convertRadix() {
    radix = std::stoi(data);
    data = "";
}

void TokenPayloadNumber::convert() {
    std::string::size_type idx;
    std::string tmp = data;
    long decimal;

    integer = std::stol(tmp, &idx, radix);
    tmp = tmp.substr(idx);

    number = integer;

    if (*tmp.cbegin() == '.') {
        tmp = tmp.substr(1);
        decimal = std::stol(tmp, &idx, radix);
        number += pow(radix, -(long)idx) * decimal;
        tmp = tmp.substr(idx);
    }
    
    std::cout << tmp << std::endl;

    if (*tmp.cbegin() == 'e') {
        tmp = tmp.substr(1);
        exponent = std::stol(tmp, &idx, 10);
        number *= pow(radix, exponent);

        tmp = tmp.substr(idx);
    }
}

std::string TokenPayloadNumber::toString() {
    std::stringstream ss;
    ss << number;
    // if (decimal >= 0)
    //     ss << "." << decimal;
    // if (exponent >= 0)
    //     ss << "e" << exponent;

    return ss.str();
}