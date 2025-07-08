//JsonValue:所有JSON类型的抽象基类（含虚函数）
#ifndef JSON_VALUE_HPP
#define JSON_VALUE_HPP
//c++中常见的头文件防卫式宏(include guard),它的作用是：
//防止头文件被多次包含，从而避免编译时出现重复定义错误。

#include<string>
#include<vector>
#include<map>

class Json;  // ✅ 前向声明即可

class JsonValue{
public:
    virtual ~JsonValue()=default;
    //虚析构函数，多态类必须有的。
    //保证通过基类指针std::shared_ptr<JsonValue>删除子类对象时，能调用正确的析构函数。
    //当通过基类指针删除派生类对象时，会正确调用派生类的析构函数，防止资源泄漏。
    //如果没有，可能会造成资源泄漏或未定义行为。

    virtual std::string toString() const=0;
    //把当前JSON值转成JSON字符串格式。
    //是一个纯虚函数，必须被子类发现。

    virtual bool isNumber() const {return false;}
    //提供一个类型判断接口。如果当前值是JsonNumber，它会重写这个函数返回true，否则默认都是false。
    //所有子类默认返回false，只有JsonNumber重写返回true。
    virtual bool isString() const {return false;}
    //const作用：表示isString()是一个常量成员函数，它承诺不修改该对象的任何非mutable成员变量。
    //因为isString()函数是一个查询函数，不应该修改对象的内容，所以应该加const，确保查询操作不意外地修改数据。
    virtual bool isNull() const {return false;}
    virtual bool isBool() const {return false;}
    virtual bool isArray() const {return false;}
    virtual bool isObject() const {return false;}

    virtual double asNumber() const {throw std::runtime_error("not a number");}
    //获取JSON数值（如果当前是数字）。
    //默认实现是抛出异常，子类JsonNumber会重写。
    virtual const std::string& asString() const {throw std::runtime_error("not a string");}
    virtual bool asBool() const {throw std::runtime_error("not a null");}
    virtual const std::vector<Json>& asArray() const {throw std::runtime_error("not a null");throw std::runtime_error("not a array");}
    virtual const std::map<std::string,Json>& asObject() const {throw std::runtime_error("not a object");}
};

#endif
