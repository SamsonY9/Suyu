#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <sys/eventfd.h>
#include <iostream>

using std::cout;
using std::endl;

EventLoop::EventLoop(Acceptor &acceptor)
: _epfd(createEpollFd())
, _evtList(1024)
, _isLooping(false)
, _acceptor(acceptor)
, _evtfd(createEventFd())
, _mutex()
{
    //获取listenfd（也就是socket返回的文件描述符）
    //并且将listenfd放在红黑树上进行监听
    int listenfd = _acceptor.fd();
    addEpollReadFd(listenfd);

    //需要监听用于通信的文件描述符_evtfd
    addEpollReadFd(_evtfd);
}

EventLoop::~EventLoop()
{
    close(_epfd);
    close(_evtfd);
}

//循环与非循环
void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping)
    {
        waitEpollFd();
    }
}

void EventLoop::unloop()
{
    _isLooping = false;
}

//封装epoll_wait的函数
void EventLoop::waitEpollFd()
{
    int nready = 0;
    do{
        nready = epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 3000);
    }while((-1 == nready && errno == EINTR));

    if(-1 == nready)
    {
        perror("-1 == nready");
        return;
    }
    else if(0 == nready)
    {
        cout << ">>epoll_wait timeout!!!" << endl;
    }
    else 
    {
        //考虑一个问题，vector有可能越界的问题，需要手动扩容
        //nready == -1(int--->size_t)
        //for(size_t idx = 99; idx > 0; idx -=2)
        //{
        //
        //}
        if((int)_evtList.size() == nready)
        {
            _evtList.resize(2 * nready);
        }

        for(int idx = 0; idx < nready; ++idx)
        {
            int fd = _evtList[idx].data.fd;
            int listenfd = _acceptor.fd();
            if(fd == listenfd)
            {
                //有新的连接请求上来
                handleNewConnection();
            }
            else if(fd == _evtfd)//用于通信的文件描述符就绪了
            {
                handleRead();
                //然后执行所有的任务
                doPengdingFunctors();
            }
            else
            {
                //处理老的连接
                handleMessage(fd);
            }
        }
    }
}

//处理新的连接
void EventLoop::handleNewConnection()
{
    //调用Acceptor的accept函数，如果该函数的返回值
    //connfd是正常值，就表明三次握手建立成功了
    int connfd = _acceptor.accept();
    if(connfd < 0)
    {
        perror("handleNewConnection");
        return;
    }
    //监听connfd
    addEpollReadFd(connfd);

    //创建出TcpConnection的对象
    /* TcpConnection con(connfd); */
    TcpConnectionPtr con(new TcpConnection(connfd, this));

    //当连接TcpConnection对象创建出来之后，需要将三个回调
    //从EventLoop中传递给TcpConnection的对象
    con->setNewConnectionCallback(_onNewConnectionCb);//连接建立
    con->setMessageCalback(_onMessageCb);//消息达到
    con->setCloseCallback(_onCloseCb);//连接断开

    //将connfd与TcpConnection的键值对存放在map中
    /* _conns.insert(std::make_pair(connfd, con)); */
    _conns[connfd] = con;

    //连接建立的事件的触发时机已经到达了，可以执行
    con->handleNewConnectionCallback();//连接建立的事件的执行
}

//处理老的连接上的数据的收发
void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    if(it != _conns.end())
    {
        //拿到这个连接之后，如何判断连接是不是断开的呢
        //如果连接断开就可以执行连接断开的事件
        //否则就执行消息到达的事件
        bool flag = it->second->isClosed();
        if(flag)
        {
            //连接断开
            it->second->handleCloseCallback();//连接断开的事件的触发时机
            //将fd从红黑树上删除
            delEpollReadFd(fd);
            //还需要将连接从map中删除
            _conns.erase(it);
        }
        else
        {
            //连接没有断开，可以正常收发数据
            it->second->handleMessageCallback();//消息到达
        }
    }
    else
    {
        cout << "该连接是不存在" << endl;
        return;
    }
}

//封装epoll_create函数
int EventLoop::createEpollFd()
{
    int fd = epoll_create(10);
    if(fd < 0)
    {
        perror("createEpollFd");
        return -1;
    }

    return fd;
}

//将文件描述符放在红黑树上进行监听
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if(ret < 0)
    {
        perror("addEpollReadFd");
        return;
    }
}

//将文件描述符从红黑树上取消监听
void EventLoop::delEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
    if(ret < 0)
    {
        perror("delEpollReadFd");
        return;
    }

}

void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb)
{
    _onNewConnectionCb = std::move(cb);
}

void EventLoop::setMessageCalback(TcpConnectionCallback &&cb)
{
    _onMessageCb = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback &&cb)
{
    _onCloseCb = std::move(cb);
}

//创建用于通信的文件描述符
int EventLoop::createEventFd()
{
    int fd = eventfd(10, 0);
    if(fd < 0)
    {
        perror("createEventFd");
        return -1;
    }

    return fd;
}

//封装read的函数
void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t ret = read(_evtfd, &one, sizeof(uint64_t));
    if(ret != sizeof(uint64_t))
    {
        perror("handleRead");
        return;
    }
}

//封装write的函数
void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t ret = write(_evtfd, &one, sizeof(uint64_t));
    if(ret != sizeof(uint64_t))
    {
        perror("wakeup");
        return;
    }
}

//执行所有的任务(先写在这里，然后再来看看有没有优化的可能性)
void EventLoop::doPengdingFunctors()
{
    vector<Functor> tmp;
    {
        //尽量的让锁的粒度要小一些（范围）
        lock_guard<mutex> lg(_mutex);
        tmp.swap(_pendings);
    }

    for(auto &cb : tmp)
    {
        //“任务”就是要发送的数据msg，以及发送数据的能力的send
        //以及发送的连接TcpConnection对象
        cb();//这就是执行所有存放在vector中的"任务"
    }
}

void EventLoop::runInLoop(Functor &&cb)
{
    //这里写什么东西?
    {
        lock_guard<mutex> lg(_mutex);
        _pendings.push_back(std::move(cb));
    }

    wakeup();//通知/唤醒Reactor去将数据发给客户端
}

