#include"JsonObject.hpp"
#include"Json.hpp"
#include<sstream>

std::string JsonObject::toString() const {
    std::ostringstream oss;
    oss<<"{";
    auto it=value_.begin();
    while(it!=value_.end())
    {
        oss<<"\""<<it->first<<"\":"<<it->second.toString();
        if(++it!=value_.end()) {oss<<",";}
    }
    oss<<"}";
    return oss.str();
}