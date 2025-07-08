#ifndef JSON_NUMBER_HPP
#define JSON_NUMBER_HPP

#include "JsonValue.hpp"

class JsonNumber : public JsonValue{
public:
    JsonNumber(double val) : value_(val) {}
    
    bool isNumber() const override {return true;};
    double asNumber() const override {return value_;}
    std::string toString() const override;

private:
    double value_;
};

#endif