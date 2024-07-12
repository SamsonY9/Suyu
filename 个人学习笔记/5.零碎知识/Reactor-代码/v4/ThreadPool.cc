#include "ThreadPool.h"
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
        _threads.push_back(thread(&ThreadPool::doTask, this));
    }
}

void ThreadPool::stop()
{
    //只要任务没有执行完，就不能让主线程继续向下执行
    while(!_taskQue.empty())
    {
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
void ThreadPool::addTask(Task &&taskcb)
{
    if(taskcb)
    {
        _taskQue.push(std::move(taskcb));
    }
}

Task ThreadPool::getTask()
{
    return _taskQue.pop();
}

//线程池交给工作线程thread执行的任务
void ThreadPool::doTask()
{
    while(!_isExit)
    {
        //线程池中的线程需要先获取任务，然后执行任务
        Task taskcb = getTask();
        if(taskcb)
        {
            /* ptask->process();//会体现出多态 */
            taskcb();//回调
        }
        else
        {
            cout << "taskcb == nullptr" << endl;
        }
    }
}
