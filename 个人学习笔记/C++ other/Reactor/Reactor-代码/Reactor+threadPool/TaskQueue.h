#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using std::queue;
using std::mutex;
using std::unique_lock;
using std::condition_variable;
using std::function;


using ElemType = function<void()>;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    //生产任务与消费任务
    void push(ElemType &&taskcb);
    ElemType pop();

    //判断任务队列是不是空或者满
    bool full() const;
    bool empty() const;

    //唤醒所有等待在_notEmpty条件变量上的线程
    void wakeup();

private:
    size_t _queSize;//任务队列的大小
    queue<ElemType> _que;//存放数据的数据结构
    mutex _mutex;//C++11中的互斥锁
    condition_variable _notFull;//非满条件变量
    condition_variable _notEmpty;//非空条件变量
    bool _flag;//标志位

};

#endif
