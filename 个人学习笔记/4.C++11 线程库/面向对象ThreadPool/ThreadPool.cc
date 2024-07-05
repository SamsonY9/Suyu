#include "ThreadPool.h"
#include "Task.h"
#include <iostream>

using std::cout;
using std::endl;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(_queSize)
, _isExit(false)
{

}

ThreadPool::~ThreadPool()
{

}

//线程的启动与停止
void ThreadPool::start()
{
    //创建线程，并且存放在容器中
    for(size_t idx = 0; idx != _threadNum; ++idx)
    {
        /* thread th(&ThreadPool::doTask, this); */
        /* _threads.push_back(std::move(th)); */
        _threads.push_back(thread(&ThreadPool::doTask, this));
    }
}

void ThreadPool::stop()
{
    //只要任务没有执行完，就不能让主线程继续向下执行
    while(!_taskQue.empty())
    {
        /* sleep(1); */
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    //线程池要退出，那么标志位可以设置为true
    _isExit = true;
    //唤醒所有等待在_notEmpty上的线程
    _taskQue.wakeup();

    for(auto &th : _threads)
    {
        th.join();
    }
}

//添加任务与获取任务
void ThreadPool::addTask(Task *ptask)
{
    if(ptask)
    {
        _taskQue.push(ptask);
    }
}

Task *ThreadPool::getTask()
{
#if 0
    Task *ptask = _taskQue.pop();
    if(ptask)
    {
        return ptask;
    }
    else
    {
        return nullptr;
    }
#endif
    return _taskQue.pop();
}

//线程池交给工作线程thread执行的任务
void ThreadPool::doTask()
{
    //只要有任务，线程在执行完上一个任务之后，就需要
    //继续拿任务，并且执行任务
    //
    //如果子线程在执行doTask的时候，主线程在执行stop函数
    //如果子线程将任务获取完毕，也就是执行完getTask之后，
    //接下来子线程会继续执行process函数，而主线程会将
    //_isExit设置为true，加入此时子线程执行的速率比较快
    //有可能主线程还没有将标志位_isExit设置为true，子线程
    //又进入到while循环，再去执行getTask，发现没有任务
    //了，那么子线程就会处于睡眠状态;如果子线程指向getTask
    //将任务取完毕之后，主线程很快的将标志位_isExit设置为
    //true，然后子线程再执行process之后，再走while循环
    //的时候，发现_isExit为true，就不会阻塞
    while(!_isExit)
    {
        //线程池中的线程需要先获取任务，然后执行任务
        Task *ptask = getTask();
        if(ptask)
        {
            ptask->process();//会体现出多态
        /* std::this_thread::sleep_for(std::chrono::seconds(2)); */
        }
        else
        {
            cout << "ptask == nullptr" << endl;
        }
    }
}
