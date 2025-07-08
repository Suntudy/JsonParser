#ifndef JSON_HPP
#define JSON_HPP

#include"JsonValue.hpp"
#include"JsonNumber.hpp"
#include"JsonString.hpp"
#include"JsonNull.hpp"
#include"JsonBool.hpp"
#include"JsonArray.hpp"
#include"JsonObject.hpp"
#include <memory>
#include <string>

class Json{
public:
    Json() : ptr_(std::make_shared<JsonNull>()) {}  //构造null
    //make_shared<T>() 用来创建一个类型为T的对象，并返回一个指向它的 shared_ptr<T>
    Json(double number) : ptr_(std::make_shared<JsonNumber>(number)) {} //基类指针指向子类对象
    Json(const std::string& str) : ptr_(std::make_shared<JsonString>(str)) {} //拷贝构造
    Json(std::string&& str) : ptr_(std::make_shared<JsonString>(std::move(str))) {} //移动构造
    //它俩作用都是用字符串来构造一个Json字符串对象，但处理方式不同。
    //Json(const std::string& str) 拷贝构造函数。拷贝引用，拷贝一份字符串，稳定但略慢。
        //适用于传入已有变量的情况，如：std::string s="hello"; Json j(s);
        //s是一个左值（命名变量），会把s的内容复制一份，赋值给内部的JsonString
    //Json(std::string&& str) 移动构造函数。右值引用，直接偷走传进来的字符串资源，更快。
        //适用于传入临时值（右值）的情况，如：Json j("hello");
        //或 Json j(std::move(s)); move(s)是右值，调用的是移动构造。移动后s不会被销毁，依然存在，但内容被偷走了。变成了一个 合法但出于未定义内容的状态，不能再当作正常字符串使用。
        //不复制字符串内容，而是把临时对象的内部buffer偷过来，更快。
    Json(const char* s) : Json(std::string (s)) {}
    //防止字符串字面量发生 const char* -> bool的隐式转换
    //Json(std::string (s)) 委托构造函数：调用 Json(std::string) 构造函数，并把 std::string(s) 当作参数传进去。
    explicit Json(bool b) : ptr_(std::make_shared<JsonBool>(b)) {}
    //explicit: 防止隐式转换，如 Json j("hello") 编译器可以把"hello"转换成bool类型（非空指针->true）
    Json(const std::vector<Json>& array);
    Json(std::vector<Json>&& array);
    Json(const std::map<std::string,Json>& obj);
    Json(std::map<std::string,Json>&& obj);


    bool isNumber() const {return ptr_->isNumber();}
    bool isString() const {return ptr_->isString();}
    bool isNull() const {return ptr_->isNull();}
    bool isBool() const {return ptr_->isBool();}
    bool isArray() const {return ptr_->isArray();}
    bool isObject() const {return ptr_->isObject();}


    double asNumber() const {return ptr_->asNumber();}
    const std::string& asString() const {return ptr_->asString();}
    bool asBool() const {return ptr_->asBool();}
    const std::vector<Json>& asArray() const {return ptr_->asArray();}
    const std::map<std::string,Json>& asObject() const {return ptr_->asObject();}
 
    std::string toString() const {return ptr_->toString();}

private:
    std::shared_ptr<JsonValue> ptr_;
    //定义一个基类指针
};


#endif