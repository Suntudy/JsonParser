# C++多态
多态是c++面向对象编程OOP的最核心特性之一。它允许相同的接口在不同的对象上表现出不同的行为。
## 静态多态（编译期多态）
通过函数重载、运算符重载实现，编译时就能确定调用哪个函数。
```C++
void print(int x) {cout<<"int";}
void print(double x){cout<<"double";}
```
## 动态多态（运行期多态）
本项目用到的。
通过**继承+虚函数（virtual function）**实现，运行时才根据对象的真实类型调用对应的方法。

必须通过**基类指针或引用**来调用虚函数，才能实现运行时多态。
```C++
class Base{
public:
	virtual void parse(){cout<<"base parse";}
};

class JsonNumber:public Base{
public:
	void parse() override{cout<<"parsing number";}
};

void run(Base* obj)
{
	obj->parse();//根据传入对象的真实类型调用不同版本
}
```
```C++
class Animal{
public:
	virtual void speak(){cout<<"animal makes a sound"<<endl;}
	//virtual加在基类函数前，告诉编译器请允许子类重写这个函数。
};

class Dog: public Animal{
public:
	void speak() override{
		cout<<"dog says woof!"<<endl;
	}
	//override加在子类函数里，防止拼错名字、确保真的是重写。
};

class Cat:public Animal{
public:
	void speak() override{
		cout<<"cat says meow!"<<endl;
	}
};

// 指针/引用：必须通过基类指针或引用来访问子类对象，才能出发多态。
void makesound(Animal* a)
{
	a->speak();
}

int main()
{
	Dog d;
	Cat c;
	makesound(&d);
	makesound(&c);
}
```
# Json解析器
JSON是一种**用文本来表示结构化数据**的格式。
```C++
//JSON数据
{
	"name":"zhixian",
	"age":24,
	"isstudent":true,
	"skills":["C++","python"]
}
```
JSON解析器的作用是：把JSON格式的字符串，变成程序可以操作的数据结构（如类、对象、变量）
因为不能直接拿JSON字符串来操作，比如不能直接访问字符串里的skills的值，必须先解析它，转化为程序对象，才能写代码去用。
```C++
std::string input = R"({"x":123, "y":true, "z":"hello"})";
//原始字符串字面量（raw string literal），从C++11开始支持，可以省去很多转义，适合JSON、正则表达式等复杂字符串。
//R"(...)"中的内容会完全按照原样保留，不需要写'\'。
```
# 项目
目标：设计一个支持多态、递归下降解析、智能指针管理、零内存泄漏的JSON解析器。
基类：JsonValue
子类：JsonObject, JsonArray, JsonString, JsonNumber, JsonBool/JsonNull
## 设计模块
JsonValue : 抽象基类，定义虚函数如 toString()
JsonString,JsonNumber等 : 每种JSON类型对应一个子类
JsonObject : 存储map<string,shared_ptr<JsonValue>>
JsonArray : 存储vector<shared_ptr<JsonValue>>
JsonParser : 字符串解析器，负责从字符串构建JsonValue
main.cpp : 测试代码或CLI接口

# 项目步骤
## 基础框架&核心类设计（多态+封装）
搭建基本类结构，支持构造简单的JSON值和多态访问。
1. 定义抽象基类JsonValue，声明虚函数接口（如tostring()）
2. 定义封装类Json，内部持有std::shared_ptr<JsonValue>
3. 实现子类：JsonNull,JsonBool,JsonNumber,JsonString
4. 测试多态行为，如构造不同类型，调用tostring()输出

## 复合结构支持（array和object）
支持Json的嵌套结构（[]和{}）
1. 实现JsonArray，内部用std::vector<Json>
2. 实现JsonObject，内部用std::map<std::string,Json>
3. 在Json中添加构造函数、访问接口：isArray(),asArray(),operator[]
4. 测试嵌套结构，如[1,"hi",{"key":false}]的构造与输出

## 递归下降解析器实现
1. 解析字符串为内部结构。如：从R"({"x":123})"解析出JsonObject
2. 编写parseValue()，根据首字符判断类型并分发
3. 编写parseNull(), parseBool(), parseNumber(), parseString()
4. 编写parseArray(), parseObject(), 递归解析嵌套结构。
5. 实现基本容错机制：非法输入时抛出异常

## 接口完善&优化
1. 使用右值引用支持移动构造，加快构造效率。
2. 添加操作符重载，如operator[]，支持json["key"]的写法
3. 完善toString(),支持漂亮格式输出。
4. 编写测试集（包含各种合法和非法JSON测试）
5. 写README

# 项目构成
Json.hpp, Json.cpp
JsonValue.hpp
JsonNumber.hpp, JsonNumber.cpp
JsonString.hpp, JsonString.cpp
JsonNull.hpp
JsonBool.hpp
JsonArray.hpp, JsonArray.cpp
JsonObject.hpp, JsonObject.cpp
main.cpp

JsonParser.hpp, JsonParser.cpp

#实现Json字符串解析器（递归下降法）
递归下降法 recursive descent
根据不同的开头符号判断数据类型，如：
“ 字符串
{ 对象
[ 数组
数字或- number
n null
t/f bool
用到了：辅助类 JsonParser(解析类)

# （待办）优化
## 加一个fromFile/fromStdin 接口
Stdin: 标准输入，即平时在终端里运行程序时手动输入的数据。
## 增强toString 格式化输出（支持缩进）




# TIPS
1. 很多.cpp文件，怎么编译？
> 使用 Makefile 或 CMake
> （简单）vscode里的task.json（不支持跨平台）

2. 智能指针
> unique_ptr
> shared_ptr
> weak_ptr

3. Json.hpp: class Json里只声明构造函数，具体实现（函数体）写在Json.cpp里
> .hpp文件变小，可读性好
> 编译依赖更少
> 减少重复编译，提高编译速度

# C++编译流程
1. 预处理（preprocessing）：把所有#include文件展开成一个大文件
2. 编译（compiling）：每个.cpp文件分别编译成.o（目标文件）
3. 链接（linking）：把所有.o文件链接成一个最终的可执行文件

## 多个.cpp文件include一个.hpp文件
如果多个.cpp文件都include一个定义了**函数体**的.hpp文件，错误会发生在链接阶段。
预处理后，a.cpp 和 b.cpp 都拥有了Json::Json(double)的定义副本。
编译器能正常编译它们分别生成a.o和b.o
但链接器在合并它们时，会报错：duplicate symbol Json::Json(double) in a.o and b.o
**C++不允许一个函数在最终链接时出现多个定义，这叫 One Definition Rule(ODR)**
解决方法：
1. 把函数体移到.cpp文件
2. 如果坚持写在.hpp里，要加inline（表示允许多定义）inline Json(double number) { ... } 

## 声明了函数但没实现，undefined symbol
如果.hpp里只声明了函数但没有实现，在main.cpp里用了这个函数，编译通过，但链接时会报错：Undefined symbols for architecture arm64
因为链接器找不到 Json::Json(double) 的定义。

# Json 和 JsonArray/JsonObject
JsonArray/JsonObject用到了Json，而Json又包含了JsonValue的职能指针。
如果把Json的构造函数的函数题直接定义在Json.hpp文件里，会发生**相互包含（循环依赖）+incomplete type**
通俗地说，在.hpp文件中实现成员函数会要求**立刻知道Json的全部定义**，但此时Json还没被完全定义，所以会报错。
函数写在.hpp里，要求类型完整，最好用于简单逻辑。
正确做法：函数写在.cpp文件里，类型先include进来即可，可以解决循环依赖。