#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <mutex>

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;
using std::mutex;
using std::lock_guard;


class Acceptor;//前向声明
class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
using Functor = function<void()>;

class EventLoop
{
public:
    EventLoop(Acceptor &acceptor);
    ~EventLoop();

    //循环与非循环
    void loop();
    void unloop();

    //封装epoll_wait的函数
    void waitEpollFd();

    //处理新的连接
    void handleNewConnection();

    //处理老的连接上的数据的收发
    void handleMessage(int fd);

    //封装epoll_create函数
    int createEpollFd();

    //将文件描述符放在红黑树上进行监听
    void addEpollReadFd(int fd);
    
    //将文件描述符从红黑树上取消监听
    void delEpollReadFd(int fd);

    //三个回调的注册
    void setNewConnectionCallback(TcpConnectionCallback &&cb);
    void setMessageCalback(TcpConnectionCallback &&cb);
    void setCloseCallback(TcpConnectionCallback &&cb);

public:
    //创建用于通信的文件描述符
    int createEventFd();

    //封装read的函数
    void handleRead();

    //封装write的函数
    void wakeup();

    //执行所有的任务
    void doPengdingFunctors();

    void runInLoop(Functor &&cb);

private:
    int _epfd;//是epoll_create创建出来的文件描述符
    vector<struct epoll_event> _evtList;//存放满足条件的文件描述符的数据结构
    bool _isLooping;//标识循环运行与否
    Acceptor &_acceptor;//连接器Acceptor的引用
    map<int, TcpConnectionPtr> _conns;//存放文件描述符与TcpConnection的键值对

    //添加三个数据成员，对应的就是三个事件
    TcpConnectionCallback _onNewConnectionCb;//连接建立
    TcpConnectionCallback _onMessageCb;//消息到达（文件描述符可读）
    TcpConnectionCallback _onCloseCb;//连接建立

    int _evtfd;//用于通信的文件描述符
    vector<Functor> _pendings;//待执行的任务（存放任务的容器）
    mutex _mutex;//互斥访问vector

};

#endif
