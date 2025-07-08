#ifndef JSON_STRING_HPP
#define JSON_STRING_HPP

#include "JsonValue.hpp"

class JsonString : public JsonValue{
public:
    JsonString(std::string val) : value_(std::move(val)) {}
    //不用value_(val)，move(val)可以避免一次不必要的拷贝，提高性能。
    //什么时候用move(val)：val是临时值（右值）或已经不再使用的对象。希望把val的内容搬进成员变量，而不是复制。

    bool isString() const override {return true;}
    const std::string& asString() const override {return value_;}
    //第一个const string&，表示返回的是对字符串的常引用（不修改原字符串）。
    //第二个asString() const，表示这个函数是一个常成员函数，不能修改成员变量。
    std::string toString() const override;

private:
    std::string value_;
};

#endif