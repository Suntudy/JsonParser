#include "JsonString.hpp"
#include<sstream>

std::string JsonString::toString() const{
    std::ostringstream oss;
    //是C++中的一个字符串输出流对象，作用是像写文件一样写入字符串，最终组合成一个大字符串。
    oss<<"\"";
    // \ 是转义符的开头，必须跟着一个有效的转义字符。如\\,\",\',\n,\t.
    for(char ch:value_){
        if(ch == '"') oss<<"\\\"";
        else if(ch == '\\') oss<<"\\\\";
        else oss<<ch;
    }
    oss<<"\"";
    return oss.str();
    //oss.str()获取最终拼接出的string
}