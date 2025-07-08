#include "JsonNumber.hpp"
#include<string>

std::string JsonNumber::toString() const {
    return std::to_string(value_);
}
