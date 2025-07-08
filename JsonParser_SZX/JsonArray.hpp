#ifndef JSON_ARRAY_HPP
#define JSON_ARRAY_HPP

#include "JsonValue.hpp"
#include <vector>
#include <memory>

class Json;  // ✅ 前向声明即可

class JsonArray : public JsonValue {
public:
    JsonArray() = default;
    explicit JsonArray(std::vector<Json>val) : value_(std::move(val)) {}

    std::string toString() const override;
    bool isArray() const override {return true;}
    const std::vector<Json>& asArray() const override {return value_;}

private:
    std::vector<Json>value_;
};

#endif