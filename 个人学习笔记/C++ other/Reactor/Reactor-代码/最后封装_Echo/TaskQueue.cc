#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notFull()
, _notEmpty()
, _flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

//生产任务与消费任务
void TaskQueue::push(ElemType &&taskcb)
{
    //1、先上锁
    unique_lock<mutex> ul(_mutex);
    //2、判满
    while(full())
    {
        //上半部：先上锁、解锁、睡眠
        //下半部：被唤醒、抢到锁、函数返回
        //2.1、如果是满的，睡眠
        _notFull.wait(ul);

    }
    //3、生产数据
    _que.push(std::move(taskcb));
    //4、唤醒消费者
    _notEmpty.notify_one();
}

ElemType TaskQueue::pop()
{
    //1、先上锁
    unique_lock<mutex> ul(_mutex);
    //2、判空
    while(empty() &&_flag)
    {
        //上半部：先上锁、解锁、睡眠
        //下半部：被唤醒、抢到锁、函数返回
        //2.1、如果是满的，睡眠
        _notEmpty.wait(ul);

    }
    if(_flag)
    {
        //3、消费数据
        ElemType tmp = _que.front();
        _que.pop();
        //4、唤醒生产者
        _notFull.notify_one();
        //解锁

        return tmp;
    }
    else
    {
        return nullptr;
    }
}

//判断任务队列是不是空或者满
bool TaskQueue::full() const
{
    return _queSize == _que.size();
}

bool TaskQueue::empty() const
{
    return 0 == _que.size();
}

void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notify_all();
}
