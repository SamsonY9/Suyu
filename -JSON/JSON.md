<img src="C:\Users\11943\Desktop\-JSON\json\json图标.png" style="zoom: 80%;" />

​                                                                                      <span style=color:red;background:yellow>**---Created by Suyu**</span>

# 1. JSON介绍

古董版：https://www.json.org/json-zh.html

>  `JSON(JavaScrip Object Notation)`是一种轻量级的数据交换格式。它基于 ECMAScript (欧洲计算机协会制定的js规范)的一个子集，采用完全独立于编程语言的
>
>  文本格式来存储和表示数据。简洁和清晰的层次结构使得 JSON 成为理想的数据交换语言。 易于人阅读和编写，同时也易于机器解析和生成，并有效地提升网络传输效
>
>  率。
>
>  **JSON是一种文本数据格式**，来源于JavaScript的对象语法，但是却独立于JavaScript的,两者并没有强关联，简单来说JSON是一种文本规范，或者一种字符串规范。
>
>  关于上面的描述可以精简为一句话：<span style=color:red;background:yellow>**Json是一种数据格式，和语言无关，在什么语言中都可以使用Json。**</span>
>
>  -> 那么`JSON`有什么处呢？？
>
>  ​	                      <span style=color:red;background:yellow>**通过简单的一条字符串可以记录多层结构的数据**</span>
>
>  <img src="C:\Users\11943\Desktop\-JSON\json\Json树形结构.png" style="zoom: 50%;" />
>
>  **~当然可以记录不同类型的文本数据不只有JSON，XML也可以 √。**
>
>  ![](C:\Users\11943\Desktop\-JSON\json\xml-JSON.png)
>
>  不过当文本数据量大结构复杂XML在流式处理，易读性上更胜一筹，比如HTML，SVG实质上是建立在XML之上的。
>
>  `XML`: 可扩展标记语言，是一种用于标记电子文件使其具有结构性的标记语言。
>
>  `JSON`: JSON是一种轻量级的数据交换格式,
>
>  相同点: 它们都可以作为一种数据交换格式。
>
>  区别:
>  	XML是重量级的，JSON是轻量级的，XML在传输过程中比较占带宽，JSON占带宽少，易于压缩。
>
>  ​	XML和JSON都用在项目交互下，XML多用于做配置文件，JSON用于数据交互。

> **Json的文本实质是一条字符串**：可以存储在 `.json` `.txt` `程序中的字符串变量`等。<span style=color:red;background:yellow>**程序中使用JSON数据，需要特定的方法转换为对象变量才能使用**</span>
>
> 所以Json只是一种文本规范：程序中的Json对象、Json变量则根据不同编程语言、不同Json库会有（操作/表达）上的差异,并不是所有语言都支持JSON，一些编程语言
>
> 需要引入第三方JSON库才可以使用。
>
> 如:
>
>    JavaScript:  原生支持
>     Python:     原生支持，import json
>     JAVA:       原生不支持，需要引入Gson或FastJson等库
>     C++:        原生不支持，引入Jsoncpp等库

# 2. JSON的语法规范

> **Json支持的6种值类型：**
>
> ![](C:\Users\11943\Desktop\-JSON\json\JSON数据类型.png)
>
> **<常规值类型>**
>
> 1.字符串 
>
> 	- 需要包含在一对双引号内：`"test string"`
> 	- 字符串中包含双引号需要使用`\`转义：`"test \"string"`
>
> 2.数字
>
>  - 可以是整数、浮点数（小数）：0、-1、10、1.1、-1.21
>
> 3.布尔值
>
> - true 、false 
>
> 4.null
>
> - 空值
>
> <span style=color:red;background:yellow>**注意：这四种类型的值是不允许内嵌其他值的，一个JSON文本可以仅含有一个字符串或一个数字**</span>

>**Json中主要有两种数据格式：**
>
>`Json数组` 和 `Json对象`，并且这两种格式可以交叉嵌套使用，让JSON文本可以表示复杂的树形数据，为了提升JSON文本的扩展性，一般采用对象或数组作为最外层结构，JSON标准没有对数组/对象长度，内嵌层深度提出限制，下面依次介绍下这两种数据格式：

## 2.1 Json数组

> Json数组使用 `[]`表示，`[]`里边是元素，元素和元素之间使用逗号间隔，最后一个元素后边没有逗号。
>
> 一个Json数组中支持同时存在多种不同类型的成员：`整形` `浮点` `字符串` `布尔类型` `json数组` `json对象` `空值-null`
>
> 由此可见Json数组比起C/C++数组要灵活很多~~

- Json数组中的元素数据类型一致

  ```json
  // 整形
  [1,2,3,4,5]
  // 字符串
  ["luffy", "sanji", "zoro", "nami", "robin"]
  ```

- Json数组中的元素数据类型不一致

  ```json
  [12, 13.34, true, false, "hello,world", null]
  ```

- Json数组中的数组嵌套使用

  ```json
  [
      ["cat", "dog", "panda", "beer", "rabbit"],
      ["北京", "上海", "天津", "重庆"],
      ["luffy", "boy", 19]
  ]
  ```

- Json数组和对象嵌套使用

  ```json
  [
      {
          "luffy":{
              "age":19,
              "father":"Monkey·D·Dragon",
              "grandpa":"Monkey D Garp",
              "brother1":"Portgas D Ace",
              "brother2":"Sabo"
          }
      }
  ]
  ```

## 2.2 Json对象

> - 需要包含在一对`{}`之内，每个Json对象中可以存储若干个元素，每一个元素对应一个键值对<span style=color:red;background:yellow>**（key：value 结构）**</span> `{}` `{"key 1":"value 1"}`

> - 元素和元素之间使用逗号间隔，最后一个元素后边没有逗号。`{"key 1":"value 1","key 2":"value 2"}`

<span style=color:red;background:yellow>**对于每个元素中的键值对有以下细节需要注意：**</span>

> 键值（key）必须是字符串，位于同一层级的键值不要重复（因为是通过键值取出对应的value值）
>
> (value）值的类型是随便选的，可根据实际需求指定，可用类型包括：`整形` `浮点` `字符串` `布尔类型` `json数组` `json对象` `空值-null`
>
> ---> `{"key 1":"value 1" , "key 2":true , "key 3":{} ,"key 4":123 }`

Eg：来看个小例子吧~~

```json
// 使用Json对象描述一个人的信息:

/* 
	这个JSON对象可以被用于存储和传输这个人的信息，例如在Web服务中作为API的响应数据，或者在应用程序中作为配置数据。
*/

{
    "Name":"Suyu",           							// 表示这个人的名字是 --me-->  也就是我 Suyu
    "Sex":"man",										// 性别是男性
    "Age":22,											// 年龄是22岁
    "Family":{											// 一个嵌套的对象，描述了Suyu的家庭成员
        "Father":"Gol·D·Roger",
        "Mother":"Portgas·D·Rouge",
        "Brother":["Sabo", "Monkey D. Luffy"]
    },									 
    "Comment":"good!!!"									 // 对我的评价
}

/* 
注意：
	Json的结构虽然简单，但是进行嵌套之后就可以描述很复杂的事情，在项目开发过程中往往需要我们根据实际需求自己定义 Json 格式用来存储项目数据。
另外，如果需要将 Json 数据持久化到磁盘文件中，需要注意一个问题：在一个 Json 文件中只能有一个 Json数组 或者 Json对象 的根节点，不允许同时存储多个并列的根节点。
下面举例说明：
*/

// test.json
{
    "name":"luffy",
    "age":19
}
{
    "user":"ace",
    "passwd":"123456"
}
// error :在一个 Json 文件中有两个并列的 Json 根节点（并列包含 --> Json对象和Json对象、Json对象和Json数组、Json数组和Json数组）
// 根节点只能有一个 
```

>  <span style=color:red;background:yellow>**例如上面的第一个例子 通过Json对象以及Json数组的嵌套描述了一个人的身份信息，并且根节点只有一个就是Json对象，如果还需要使用Json数组或者Json对象描述其他信息，需要将这些信息写入到其他文件中，不要和这个Json对象并列写入到同一个文件里边，切记！！！**</span>

# 3. JSON的应用场景

> ### 1. Web API 数据交换
>
> 许多Web服务和API使用JSON作为数据交换格式。客户端（如浏览器或移动应用）可以通过HTTP请求从服务器获取JSON数据，或者将JSON数据发送到服务器。由于JSON是轻量级的，它非常适合在网络上传输数据。
>
> ### 2. 配置文件
>
> JSON被广泛用于存储应用程序配置数据。它的结构化和人类可读性使其成为配置文件的理想选择。例如，应用程序的数据库配置、日志配置、第三方服务的API密钥等都可以使用JSON格式保存。
>
> ### 3. 数据存储与传输
>
> 在无服务器架构中，JSON常用于存储在NoSQL数据库（如MongoDB、CouchDB）中，这些数据库本质上是基于JSON的存储系统。JSON格式的数据在数据库中作为文档存储，方便进行查询和操作。
>
> ### 4. 数据序列化和反序列化
>
> JSON用于对象的序列化和反序列化。许多编程语言都提供了将对象序列化为JSON字符串以及将JSON字符串反序列化为对象的方法，这使得在不同系统之间传递复杂数据结构变得简单和高效。
>
> ### 5. 前后端数据交换
>
> 在现代Web应用中，前端和后端通常通过JSON格式来交换数据。前端框架（如React、Angular、Vue等）从后端获取JSON数据并进行渲染，或者将用户输入的数据转换为JSON格式发送给后端进行处理。
>
> ### 6. 语言间数据传递
>
> JSON作为一种跨语言的数据交换格式，可以在不同编程语言之间传递数据。例如，一个Python程序可以生成JSON数据，然后一个Java程序可以解析这个JSON数据并使用其中的信息。这种跨语言的数据交换使得不同技术栈之间的集成变得更加容易。
>
> ### 7. 流媒体和实时数据传输
>
> JSON常用于流媒体和实时数据传输中。例如，在WebSocket协议中，消息可以被格式化为JSON进行传输。JSON的简洁性和易解析性使得它非常适合用于实时数据更新和推送。
>
> ### 8. 配置和插件数据
>
> 很多应用和工具使用JSON格式来保存配置数据和插件信息。例如，集成开发环境（IDE）和代码编辑器（如Visual Studio Code）使用JSON格式的配置文件来保存用户设置和扩展插件信息。JSON格式使得配置文件直观且易于编辑。
>
>   JSON以其简洁、易读、易解析的特点，成为了现代数据交换的主流格式之一，并广泛应用于各种场景中。通过学习和掌握JSON，可以提高数据处理和接口开发的效率，增强系统的互操作性。无论是在Web开发、配置管理、数据存储还是实时通信中，JSON都发挥着重要的作用。

# 4. jsoncpp库的使用

>   关于Json这种数据格式，在前面已经做了详细的介绍 Json的格式和用途，在项目开发过程中我们需要针对不同的语言使用不同的库对Json格式的数据进行解析，接下
>
> 来讲一下json在C++中的处理,`jsoncpp`是一个用C++编写的JSON解析和生成库。它可以帮助开发者方便地在C++项目中处理JSON数据。
>
> 下面将详细介绍如何安装和使用`jsoncpp`

## 4.1 在Unix/Linux环境下安装

> 1.下载`Jsoncpp`到`Linux`上
>
> **两种下载方法：**
>
> 方法一：**`git clone ...`** 到服务器上(或虚拟机上...)，有点慢，甚至会失败...！
>
> 方法二：下载**zip包**，通过第三方软件(winsp)上传到服务器上(虚拟机VM也可以直接拖) <span style=color:red;background:yellow>**记得解压压缩包 ！！！**</span>
>
> <img src="C:\Users\11943\Desktop\-JSON\json\github下载.png" style="zoom:50%;" />

```cmd
进入 --> https://github.com/open-source-parsers/jsoncpp/tree/update
命令行输入 --> git clone https://github.com/open-source-parsers/jsoncpp.git
```

> 2.生成静态库`libjsoncpp.a`

```c
mkdir -p build/debug                       //  用于创建目录 build/debug 

cd build/debug                             

cmake -DCMAKE_BUILD_TYPE=debug -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DARCHIVE_INSTALL_DIR=. -G "Unix Makefiles" ../..

// CMake以生成构建系统（Unix Makefiles），并指定构建类型和库类型等选项
/*
	 cmake：运行CMake工具
	-DCMAKE_BUILD_TYPE=debug：设置构建类型为 debug，启用调试信息和禁用优化
	-DBUILD_STATIC_LIBS=ON：启用静态库构建
	-DBUILD_SHARED_LIBS=OFF：禁用共享库构建
	-DARCHIVE_INSTALL_DIR=.：设置存档安装目录为当前目录
	-G "Unix Makefiles"：指定生成 Unix Makefiles
	../..：指定 CMakeLists.txt 文件的路径，位于当前目录的上两级目录
*/
    
make   // Make 工具读取 CMake 生成的 Makefile 并执行编译过程,调用 Make工具，根据 Makefile 执行编译和链接。

find -name *.a   // 再执行查找语句，就会发现静态库已经创建好了
```

![](C:\Users\11943\Desktop\-JSON\json\安装步骤1.png)

![](C:\Users\11943\Desktop\-JSON\json\安装步骤2.png)

![](C:\Users\11943\Desktop\-JSON\json\安装步骤3.png)

> 3.复制相关文件至`/usr/local`下**(方便编程)**

**(1) 复制头文件：**

相对路径：先进入到jsoncpp文件夹下的include文件夹中，再**`sudo cp -rf json /usr/local/include`**

绝对路径：**`sudo cp -rf /home/jsoncpp/include/json /usr/local/include`**

注：这里不复制的话，就把这里的json文件夹包含在自己项目中即可。

**(2) 复制静态库：**

**`sudo cp 【libjsoncpp.a所在路径】 /usr/local/lib`**

## 4.2 How to use JSONCPP

`jsoncpp`库中的类被定义到了一个`Json`命名空间中，在使用这个库的时候先声明这个命名空间：

```c++
using namespace Json;
```

> 使用`jsoncpp`库解析`json`格式的数据，只需要掌握三个类：
>
> - `Value`类：将json支持的数据类型进行了包装，最终得到一个Value类型
> - `FastWriter`类：将Value对象中的数据序列化为字符串
> - `Reader`类：反序列化, 将json字符串 解析成 Value 类型

### 4.2.1 Value类

这个类可以看做是一个包装器，它可以封装Json支持的所有类型，这样我们在处理数据的时候就方便多了。

> | 枚举类型     | 说明                                          | 翻译                       |
> | ------------ | --------------------------------------------- | -------------------------- |
> | nullValue    | NULL  value                                   | 不表示任何数据，空值       |
> | intValue     | signed integer value                          | 表示有符号整数             |
> | uintValue    | unsigned integer value                        | 表示无符号整数             |
> | realValue    | double value                                  | 表示浮点数                 |
> | stringValue  | UTF-8 string value                            | 表示utf8格式的字符串       |
> | booleanValue | bool value                                    | 表示布尔数                 |
> | arrayValue   | array value (ordered list)                    | 表示数组，即JSON串中的[]   |
> | objectValue  | object value (collection of name/value pairs) | 表示键值对，即JSON串中的{} |

#### 构造函数

Value类为我们提供了很多构造函数，通过构造函数来封装数据，最终得到一个统一的类型。

> ```c++
> // 因为Json::Value已经实现了各种数据类型的构造函数
> Value(ValueType type = nullValue);
> Value(Int value);
> Value(UInt value);
> Value(Int64 value);
> Value(UInt64 value);
> Value(double value);
> Value(const char* value);
> Value(const char* begin, const char* end);
> Value(bool value);
> Value(const Value& other);
> Value(Value&& other);
> ```

#### 检测保存的数据类型

>```c++
>// 检测保存的数据类型
>bool isNull() const;
>bool isBool() const;
>bool isInt() const;
>bool isInt64() const;
>bool isUInt() const;
>bool isUInt64() const;
>bool isIntegral() const;
>bool isDouble() const;
>bool isNumeric() const;
>bool isString() const;
>bool isArray() const;
>bool isObject() const;
>```

#### 将Value对象转换为实际类型

```c++
Int asInt() const;
UInt asUInt() const;
Int64 asInt64() const;
UInt64 asUInt64() const;
LargestInt asLargestInt() const;
LargestUInt asLargestUInt() const;
JSONCPP_STRING asString() const;
float asFloat() const;
double asDouble() const;
bool asBool() const;
const char* asCString() const;
```

#### 对json数组的操作

```c++
ArrayIndex size() const;
Value& operator[](ArrayIndex index);
Value& operator[](int index);
const Value& operator[](ArrayIndex index) const;
const Value& operator[](int index) const;
// 根据下标的index返回这个位置的value值
// 如果没找到这个index对应的value, 返回第二个参数defaultValue
Value get(ArrayIndex index, const Value& defaultValue) const;
Value& append(const Value& value);
const_iterator begin() const;
const_iterator end() const;
iterator begin();
iterator end();
```

#### 对json对象的操作

```c++
Value& operator[](const char* key);
const Value& operator[](const char* key) const;
Value& operator[](const JSONCPP_STRING& key);
const Value& operator[](const JSONCPP_STRING& key) const;
Value& operator[](const StaticString& key);

// 通过key, 得到value值
Value get(const char* key, const Value& defaultValue) const;
Value get(const JSONCPP_STRING& key, const Value& defaultValue) const;
Value get(const CppTL::ConstString& key, const Value& defaultValue) const;

// 得到对象中所有的键值
typedef std::vector<std::string> Members;
Members getMemberNames() const;
```

#### 将Value对象数据序列化为string

```c++
// 序列化得到的字符串有样式 -> 带换行 -> 方便阅读
// 写配置文件的时候
std::string toStyledString() const;
```

### 4.2.2 FastWriter 类

```c++
// 将数据序列化 -> 单行
// 进行数据的网络传输
std::string Json::FastWriter::write(const Value& root);
```

### 4.2.3 Reader 类

```c++
bool Json::Reader::parse(const std::string& document , Value& root , bool collectComments = true);
   
参数:
   - document: json格式字符串
   - root: 传出参数, 存储了json字符串中解析出的数据
   - collectComments: 是否保存json字符串中的注释信息

// 通过begindoc和enddoc指针定位一个json字符串
// 这个字符串可以是完成的json字符串, 也可以是部分json字符串
bool Json::Reader::parse(const char* beginDoc , const char* endDoc , Value& root , bool collectComments = true);
	
// write的文件流  -> ofstream
// read的文件流   -> ifstream
// 假设要解析的json数据在磁盘文件中
// is流对象指向一个磁盘文件, 读操作
bool Json::Reader::parse(std::istream& is, Value& root, bool collectComments = true);
```

# 5. 示例代码

> 比如：我们要将下面这个Json数组写入的一个文件中

```json
[
    12, 
    12.34, 
    true, 
    "tom", 
    ["jack", "ace", "robin"], 
    {"sex":"man", "girlfriend":"lucy"}
]
```

```c++ jsonTest.cc
// 引入头文件 #include <json/json.h>  
// 如何编译运行呢？ ---> g++ jsonTest.cc -ljsoncpp
#include <json/json.h>
#include <fstream>
using namespace Json;

int main()
{
    writeJson();
    readJson();
}
```

####  写json文件

```c++
void writeJson() {
    // 将最外层的数组看做一个Value
    // 最外层的Value对象创建
    Value root;
    // Value有一个参数为int 行的构造函数
    root.append(12);    // 参数进行隐式类型转换
    root.append(12.34);
    root.append(true);
    root.append("tom");


// 创建并初始化一个子数组
    Value subArray;
    subArray.append("jack");
    subArray.append("ace");
    subArray.append("robin");
    root.append(subArray);

// 创建并初始化子对象
    Value subObj;
    subObj["sex"] = "woman";  // 添加键值对
    subObj["girlfriend"] = "lucy";
    root.append(subObj);

// 序列化

#if 1
    // 有格式的字符串
    string str = root.toStyledString();
#else
    FastWriter f;
    string str = f.write(root);
#endif
    // 将序列化的字符串写磁盘文件
    ofstream ofs("test.json");
    ofs << str;
    ofs.close();
}
```

####  读json文件

```c++
void readJson() {
    // 1. 将磁盘文件中的json字符串读到磁盘文件
    ifstream ifs("test.json");
    // 2. 反序列化 -> value对象
    Value root;
    Reader r;
    r.parse(ifs, root);
    // 3. 从value对象中将数据依次读出
    if (root.isArray()) {
        // 数组, 遍历数组
        for (int i = 0; i < root.size(); ++i) {
            // 依次取出各个元素, 类型是value类型
            Value item = root[i];
            // 判断item中存储的数据的类型
            if (item.isString()) {
                cout << item.asString() << ", ";
            } else if (item.isInt()) {
                cout << item.asInt() << ", ";
            } else if (item.isBool()) {
                cout << item.asBool() << ", ";
            } else if (item.isDouble()) {
                cout << item.asFloat() << ", ";
            } else if (item.isArray()) {
                for (int j = 0; j < item.size(); ++j) {
                    cout << item[j].asString() << ", ";
                }
            } else if (item.isObject()) {
                // 对象
                // 得到所有的key
                Value::Members keys = item.getMemberNames();
                for (int k = 0; k < keys.size(); ++k) {
                    cout << keys.at(k) << ":" << item[keys[k]] << ", ";
                }
            }

        }
        cout << endl;
    }

}
```

> 在上面读Json文件的这段代码中，对读出的每个Value类型的节点进行了类型判断，<span style=color:red;background:yellow>**其实一般情况下是不需要做这样的判断的**</span>，因为我们在解析的时候是明确地知道该节点的类型的。虽然Json这种格式无外乎数组和对象两种，但是需求不同我们设计的Json文件的组织方式也不同，一般都是特定的文件对应特定的解析函数，一个解析函数可以解析任何的Json文件这种设计思路是坚决不推荐的。


​		
​		













