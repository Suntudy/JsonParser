#include "JsonArray.hpp"
#include"Json.hpp"
#include<vector>
#include<sstream>

std::string JsonArray::toString() const {
    std::ostringstream oss;
    oss<<"[";
    for(size_t i=0;i<value_.size();i++)
    {
        oss << value_[i].toString();
        if(i+1<value_.size()) {oss<<",";}
    }
    oss<<"]";
    return oss.str();
}