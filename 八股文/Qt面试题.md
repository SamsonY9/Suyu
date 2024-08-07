 

一、请描述Qt中内存管理机制的用法与原理
--------------------



有些面试官的问法是**在Qt中的代码看到了很多new，但是没有对应的delete，请问是否存在内存泄漏，为什么？**问题是一样的，本质上都是内存管理机制。

Qt中内存管理机制类似于C++的智能指针，它提供**给一个对象设置一个父对象，当父对象释放的时候，子对象会跟随父对象一起释放**，注意这里的父子对象与C++继承无关，是对象之间的关系。

**原理**很简单，**在设置父对象的时候，让父对象保存子对象的地址，然后在父对象的析构函数中释放子对象**。即可完成内存管理，**Qt中的内存管理规则为一个父对象可以管理多个子对象，而子对象最多只会有一个父对象**，并且由于父对象需要管理多个子对象，导致必须使用容器存储，且**所有子对象和父对象必须直接或间接继承同一个类**。

**用法**为**在子对象构造时传递父对象的指针即可，或者子对象调用setParent()函数设置或更换父对象**。Qt中基本所有带有Parent与Children单词的函数基本都与内存管理相关。

二、Qt窗口对象的父子关系如何指定？有什么作用与好处？
---------------------------



此题常出现在笔试题中，面试偶尔针对应届生也会问。**本题的本质也是内存管理机制，但是窗口的内存管理机制较为特殊一些**。

**窗口对象(QWidget)的父子关系可由子对象的构造函数中传递父对象的指针完成，或者子对象调用setParent()函数，传递父对象的指针**。

**作用为子窗口默认会成为父窗口的子窗口，会嵌套进父窗口中，在父窗口显示时同时显示，父窗口隐藏时同时隐藏**。如果不希望嵌套可以设置子窗口的属性为Window，注意设置完Window后就不会在随着父对象的显示而显示，隐藏而隐藏了。设置方法：

```cpp
setWindowFlag(Qt::Window);
```

**好处为在父窗口销毁时会带着子窗口一起销毁，子对象无需再调用delete。**

三、简述Qt中的事件机制
------------



在Qt中，事件机制是基于事件循环（Event Loop）的。Qt应用程序通过事件循环来处理各种事件，如鼠标点击、键盘输入、定时器事件等。事件循环会不断地从事件队列中取出事件并分发给对应的对象进行处理。

可以理解成**当开启事件循环时，会创建一个事件队列，并监听该队列**，**触发事件时**(如鼠标点击、键盘输入、定时器事件等)**会先经过过滤，筛选掉不需要处理的事件，将需要处理的事件发送到监听队列中，然后监听方会根据处理策略将需要处理的事件取出，调用对应的事件函数处理**。

不同的操作系统对事件循环的实现不同，**Windows系统的事件循环由WinAPI提供的消息循环机制来实现事件处理，将Windows的消息转换为Qt事件，而Linux系统由epoll多路复用机制完成**。注意不同操作系统不同版本的Qt具体实现方式可能不同。

四、Qt信号与槽机制的好处与原理
----------------



信号与槽（signal & slot）算是Qt中最常用的机制，**核心功能是实现对象与对象之间的通信**，目的是**代替回调**。当一个特定事件发生时，就会发出一个信号，可以通过连接到槽函数，那么在信号发送时，槽函数则会自动调用处理信号。Qt中的类有很多预定义的信号与槽函数，也可以自己定义信号与槽。

**好处是使对象之间的通信更为容易方便**，更好处理一些界面按键操作。

**信号与槽的实现主要由元对象系统实现，元对象编译器(moc)会帮你完成信号与槽的连接，要求信号与槽必须定义在头文件中，且该类必须继承QObject，类的私有段中添加Q\_OBJECT的宏**。

**单线程的信号与槽实现原理主要由观察者模式**（一种设计模式，这里不做过多赘述）**与函数指针的联合使用**，槽函数会订阅自己感兴趣的信号，当信号触发时，会通过一个队列获取到函数参数，完成功能的实现。这样实现便可以做到一个信号可以连接多个槽，多个信号也可以连接一个槽。

**多线程的信号与槽实现原理本质上是事件机制**，信号发送时会触发一个事件，发送到槽函数所在线程的事件队列中，槽函数会排队执行对应的事件函数，完成信号与槽的调用。



## 在 Qt 中，`Q_OBJECT` 宏是一个关键部分

用于启用 Qt 的元对象系统 (Meta-Object System) 以及信号和槽机制。它的主要作用如下：

>### 主要作用
>
>1. **启用元对象系统**：
>   - `Q_OBJECT` 宏用于定义一个类为 Qt 的元对象系统的一部分。这个系统提供了运行时类型信息、动态属性和信号槽机制。
>   - 它生成一些必要的代码，用于支持 Qt 的元对象系统，如元对象信息、信号、槽、属性等。
>
>2. **信号和槽机制**：
>   - `Q_OBJECT` 宏使类能够使用 Qt 的信号和槽机制。信号和槽是 Qt 特有的一种通信机制，允许对象之间进行松耦合的通信。
>   - 通过 `Q_OBJECT` 宏，类可以声明和定义信号和槽，Qt 的元对象编译器 (moc) 会为这些信号和槽生成必要的代码。
>
>3. **动态属性系统**：
>   - `Q_OBJECT` 宏使类能够使用 Qt 的属性系统。这个系统允许在运行时动态访问和修改对象的属性。
>   - 属性系统与 Qt 的设计师工具 (Qt Designer) 紧密集成，允许在设计时设置和调整属性。
>
>### 使用 Q_OBJECT 宏的类
>
>必须包含 `Q_OBJECT` 宏的类必须继承自 `QObject` 或其子类，如 `QWidget`。以下是一个简单的示例，展示了如何在一个类中使用 `Q_OBJECT` 宏：
>
>```cpp
>class MyClass : public QObject
>{
>    Q_OBJECT
>public:
>    MyClass(QObject *parent = nullptr);
>    ~MyClass();
>signals:
>    void mySignal(); // 声明一个信号
>public slots:
>    void mySlot(); // 声明一个槽
>};
>```
>
>### 生成的代码
>
>当你在类中使用 `Q_OBJECT` 宏时，Qt 的元对象编译器 (moc) 会为该类生成一些额外的代码。这些代码包括：
>
>- 一个静态的 `QMetaObject` 实例，它包含了类的元数据信息。
>- 信号和槽的实现代码，包括信号的发射 (emit) 和槽的调用 (invoke) 逻辑。
>- 支持属性系统的代码。
>
>### 结论
>
>`Q_OBJECT` 宏是 Qt 元对象系统的基础，它使类能够利用 Qt 强大的信号和槽机制、属性系统以及其他元对象功能。这个宏通过生成必要的元对象代码，极大地简化了开发者的工作，使他们能够专注于应用程序逻辑，而不是底层的实现细节。
>
>### 补充信息
>
>如果一个类不需要使用信号和槽机制，或者不需要使用 Qt 的属性系统，那么可以省略 `Q_OBJECT` 宏。但如果类需要这些功能，`Q_OBJECT` 宏是必不可少的。
>



五、编写一个信号连接匿名函数
--------------



 此题主要出现在笔试题中

假设存在类A继承QObject，其中存在sig\_hello()无参信号，在类A的成员函数中便可编写：

```cpp
connect(this, &A::sig_hello, []{    qDebug() << "hello world!";});
```

当触发sig\_hello()信号时，则会打印hello world! 

六、Qt如果一个信号的处理方法一直未被执行，有哪些可能？至少说出3种
----------------------------------



1、槽函数对象已经被销毁

2、存在长期处理的事件函数导致程序卡在事件中

3、连接信号与槽时参数错误或未进行连接，应用程序输出能看到错误

4、单线程的信号与槽中配置了阻塞排队属性（Qt::BlockingQueuedConnection）导致死锁，应用程序输出能看到错误

5、多线程信号与槽的通信中，槽函数所在线程未开启事件循环（参考第四题的原理）

七、Qt信号与槽如何同步异步？
---------------



**有些面试官会直接问connect函数中第五个参数的含义与配置，本质上差不多。**

Qt第五个参数为连接类型，**默认情况下为Qt::AutoConnection，单线程时会自动选择Qt::DirectConnection（直连方式），多线程时会自动选择Qt::QueuedConnection（排队方式）**

**Qt默认单线程的信号与槽的连接为同步的**，也就是直连方式，**只要信号触发，一定会优先执行槽函数，槽函数执行结束后则返回到信号调用的位置**。

**Qt默认多线程的信号与槽的连接为异步的**，也就是排队方式，**信号触发后不会等待槽函数结束，会直接往后执行，而槽函数在事件循环中排队，等待签名的事件执行完再开始执行**。

**多线程中若想同步需要将连接类型配置为Qt::BlockingQueuedConnection（阻塞排队方式）**，**信号发送完成后会等待槽函数执行完才会往后执行，而槽函数在事件循环中排队，等待签名的事件执行完再开始执行**。

**注意**：单线程中配置排队方式是没有意义的，配置为阻塞排队则会造成死锁，多线程中配置直连也没有任何意义。

八、Qt中多线程如何在创建子线程时传递参数，子线程在执行过程中如何向其它线程传递执行结果？
---------------------------------------------



### **如何传递参数：** 

在**继承QThread或QRunnable**的类中重写run()函数实现线程时，**可以在此类添加成员变量，在开启线程之前给成员变量赋值**，run()函数便可使用该成员变量。

在**使用moveToThread()方法**使用线程时，线程的启动是通过信号调用槽开启的，**直接通过信号与槽传参**。

### **如何传递执行结果：**

 直接通过信号与槽机制传递，不过要求槽函数所在的线程必须开启事件循环。

九、如果Qt中现有的窗口部件无法满足当前的需求，如何解决这种问题？
---------------------------------



1、若当前存在能实现大部分功能的部件，但少部分功能不满足需求，则可以直接创建一个继承该部件的类，实现自己所需要的方法，或重写部分功能函数。在ui文件中将原有部件提升为自己编写的类即可。s

2、若完全没有能复用的部件，则只能自己编写一个新的部件类，创建新部件工程方式如下图（具体如何创建不过多赘述），最后打成库添加进Qt环境中即可。注意使用自己写的部件程序需要将依赖库放置到对应环境中，打包时也需要注意拷贝到打包文件下。

![](https://img-blog.csdnimg.cn/direct/29211613006b4a2f91b55a28c19e5fd6.png)

十、Qt如何发送一个HTTP post请求并接收消息？
---------------------------



1.  在pro文件**添加network**模块（使用qmake时）
2.  使用**网络连接请求类(QNetworkRequest)**，添加URL网址，并设置HTTP的头部行
3.  使用**网络访问管理器类(QNetworkAccessManager)**发送post请求，同时需要添加HTTP附属体内容，返回得到**网络回复类(QNetworkReply)**对象
4.  当网络回复对象收到返回的消息时会触发相应的信号，可以通过连接槽函数，在槽函数中获取返回的数据

