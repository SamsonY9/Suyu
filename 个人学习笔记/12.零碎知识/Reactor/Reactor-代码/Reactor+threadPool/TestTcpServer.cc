#include "TcpConnection.h"
#include "TcpServer.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

ThreadPool *gPool = nullptr;

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con)
    : _msg(msg)
    , _con(con)
    {

    }
    void process()
    {
        //现在将msg接受过来之后，打包成了任务传递到了线程池中，
        //而线程池中处理的任务就是通过工作线程执行process进行的
        _msg;
        //....
        //....
        //数据_msg处理完成之后，需要将数据发出去
        //需要有连接的对象将线程池处理好之后的数据发送出去
        //能不能直接在此处创建出一个TcpConnection的对象
        //
        //线程池中的线程在处理好业务逻辑之后，可以立马通知
        //Reactor/EventLoop进行收数据，也就是表明线程池中
        //的子线程需要通知Reactor收数据
        //问题1：线程池中的线程如何通知Reactor呢？
        //解析1：涉及到线程之间的通信问题。如果学会了eventfd，在
        //进程或者线程之间通信的方式，就可以让线程池中的线程与Reactor
        //通信
        //
        //问题2：线程池中的线程如何将处理好之后的数据发给Reactor呢?
        //这个函数的作用就是通过连接_con将线程池处理好之后的数据发送
        //到EventLoop，让EventLoop再将处理好之后的数据发给客户端
        /* _con->send(_msg); */
        //要让TcpConnection将处理好之后的msg发给Reactor/EventLoop
        //那么TcpConnection的对象肯定需要指向Reactor/EventLoop
        //的存在,就需要将EventLoop类型的指针或者引用作为
        //TcpConnection的数据成员
        _con->sendInLoop(_msg);
    }
private:
    string _msg;
    TcpConnectionPtr _con;
};

//连接建立
void onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!!!" << endl;
}

//消息到达
void onMessage(const TcpConnectionPtr &con )
{
    string msg = con->receive();
    cout << ">>>>recv from client : " << msg << endl;
    //接收到数据之后，可以进行业务逻辑的处理
    //处理完成之后，将其发送给客户端
    //如果在此处处理业务逻辑，并且业务逻辑的处理非常耗时，所以本
    //模型（版本）就存在缺陷，所以需要将业务逻辑的处理交给线程池
    //将接受过来的数据msg打包成任务,交给线程池
    MyTask task(msg, con);
    gPool->addTask(std::bind(&MyTask::process, task));

    /* con->send(msg); */
}

//连接断开
void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!!" << endl;
}

void test()
{
    ThreadPool pool(4, 10);
    pool.start();
    gPool = &pool;

    TcpServer server("127.0.0.1", 8888);
    server.setAllCallback(std::move(onNewConnection)
                          , std::move(onMessage)
                          , std::move(onClose));
    server.start();
}

int main(int argc, char **argv)
{
    test();
    return 0;
}

