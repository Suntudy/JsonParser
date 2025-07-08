#ifndef JSON_NULL_HPP
#define JSON_NULL_HPP

#include "JsonValue.hpp"

class JsonNull : public JsonValue {
public:
    std::string toString() const override{return "null";}

    bool isNull() const override {return true;}
};

#endif