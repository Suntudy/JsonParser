#include <iostream>
#include "Json.hpp"
#include "JsonParser.hpp"

int main() {

    std::vector<std::string> test_inputs = {
        R"("hello world")",
        R"(3.14)",
        R"(true)",
        R"(null)",
        R"(["a", 1, false, null])",
        R"({"name":"zhixian", "age":23, "student":true})",
        R"({"nested": {"a": [1, 2, 3], "b": "ok"}})"
    };

    for (const auto& input : test_inputs) {
        try {
            std::cout << "Input: " << input << std::endl;
            JsonParser parser(input);
            Json json = parser.parser();

            std::cout << "Parsed to: " << json.toString() << std::endl;
            std::cout << "------------------------\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
