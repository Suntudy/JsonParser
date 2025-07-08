#ifndef JSON_BOOL_HPP
#define JSON_BOOL_HPP

#include "JsonValue.hpp"

class JsonBool : public JsonValue{
public:
    explicit JsonBool(bool val) : value_(val) {}
    //防止隐式转换，如 Json j("hello") 编译器可以把"hello"转换成bool类型（非空指针->true）

    std::string toString() const override {return value_?"true":"false";}

    bool isBool() const override {return true;}

    bool asBool() const override {return value_;}

private:
    bool value_;
};

#endif