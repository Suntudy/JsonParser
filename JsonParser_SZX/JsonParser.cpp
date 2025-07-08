#include"JsonParser.hpp"
#include<cctype>
#include<string>

//跳过空白字符
void JsonParser::skipWhitespace(){
    while(std::isspace(peek())) get();
}

//获取当前字符，但不移动指针
char JsonParser::peek()
{
    if(pos_<input_.size()) return input_[pos_];
    return '\0';
}

//获取当前字符，并移动指针
char JsonParser::get()
{
    if(pos_<input_.size()) return input_[pos_++];
    return '\0';
}

Json JsonParser::parser() {
    skipWhitespace();
    return parseValue();
}


Json JsonParser::parseValue()
{
    skipWhitespace();
    char ch=peek();
    switch(ch)
    {
        case '"':return parseString();
        case 'n':return parseNull();
        case 't':return parseTrue();
        case 'f':return parseFalse();
        case '[':return parseArray();
        case '{':return parseObject();
    }
    return parseNumber();
}

Json JsonParser::parseNull()
{
    if(input_.substr(pos_,4) != "null") {throw std::runtime_error("expected null");}

    pos_+=4;
    return Json();
}

Json JsonParser::parseFalse()
{
    if(input_.substr(pos_,5) != "false") {throw std::runtime_error("expected false");}

    pos_+=5;
    return Json(false);
}

Json JsonParser::parseTrue()
{
    if(input_.substr(pos_,4) != "true") {throw std::runtime_error("expected true");}

    pos_+=4;
    return Json(true);
}

//解析number
Json JsonParser::parseNumber()
{
    size_t start=pos_;
    if(peek()=='-') get();

    while(std::isdigit(peek())) {get();}
    if(peek()=='.')
    {
        get();
        while(std::isdigit(peek())) {get();}
    }
    double num = std::stod(input_.substr(start,pos_-start));
    //stod:将字符串转换为double类型的小数
    return Json(num);
}

Json JsonParser::parseString()
{
    if(get()!= '"') {throw std::runtime_error("expected \"");}

    std::string result;

    while(true)
    {
        char ch=get();
        if(ch=='"') break;

        if(ch=='\\')
        {
            char esc=get();
            if(esc=='"') result +='"';
            else if(esc=='\\') result+='\\';
            else if(esc=='/') result+='/';
            else if(esc=='n') result+='\n';
            else if(esc=='t') result+='\t';
            else throw std::runtime_error("invalid escape character");
        }
        else
        {
            result+=ch;
        }
    }
    return Json(result);
}

Json JsonParser::parseArray()
{
    if(get() != '[') throw std::runtime_error("expected [");

    skipWhitespace();
    std::vector<Json>result;
    if(peek()==']') {get();return Json(result);}

    while(true)
    {
        skipWhitespace();
        result.push_back(parseValue());
        skipWhitespace();
        if(peek()==']') {get();break;}
        if(get()!=',') throw std::runtime_error("expected , in array");
    }
    return Json(result);
}

Json JsonParser::parseObject()
{
    if(get()!='{') throw std::runtime_error("expected {");

    skipWhitespace();
    std::map<std::string,Json>result;
    if(peek()=='}') {get();return Json(result);}

    while(true)
    {
        skipWhitespace();
        Json key=parseString();
        skipWhitespace();
    
        if(get()!=':') throw std::runtime_error("expected : in object");
        skipWhitespace();
        Json value = parseValue();
        result[key.asString()]=value;
        skipWhitespace();

        if(peek()=='}') {get();break;}

        if(get()!=',') throw std::runtime_error("expected , in object");
    }
    return Json(result);
}