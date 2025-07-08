#include"Json.hpp"
#include"JsonArray.hpp"
#include"JsonObject.hpp"

Json::Json(const std::vector<Json>& array) : ptr_(std::make_shared<JsonArray>(array)) {}
Json::Json(std::vector<Json>&& array) : ptr_(std::make_shared<JsonArray>(std::move(array))) {}
Json::Json(const std::map<std::string,Json>& obj) : ptr_(std::make_shared<JsonObject>(obj)) {}
Json::Json(std::map<std::string,Json>&& obj) : ptr_(std::make_shared<JsonObject>(std::move(obj))) {}