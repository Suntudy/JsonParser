#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

#include "JsonValue.hpp"
#include <map>
#include <string>
#include <memory>

class Json;  // ✅ 前向声明即可

class JsonObject : public JsonValue {
public:
    JsonObject()=default;
    explicit JsonObject(std::map<std::string,Json>val) : value_(std::move(val)) {}

    std::string toString() const override;

    bool isObject() const override {return true;}
    const std::map<std::string,Json>& asObject() const override {return value_;}

private:
    std::map<std::string,Json>value_;
};

#endif