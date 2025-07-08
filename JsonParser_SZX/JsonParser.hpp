
#include "Json.hpp"
#include <string>

class JsonParser {
public:

    JsonParser(const std::string& input) : input_(input), pos_(0) {}
    
    Json parser();
private:
    const std::string& input_;//不拷贝，直接引用调用者传进来的原始字符串，提升性能
    size_t pos_;
    
    void skipWhitespace();//跳过空白字符
    char peek();//获取当前字符，但不移动指针
    char get();//获取当前字符，并移动指针

    Json parseValue();
    Json parseNumber();
    Json parseString();
    Json parseNull();
    Json parseFalse();
    Json parseTrue();
    Json parseArray();
    Json parseObject();
};