#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include <thread>
#include <vector>
#include <functional>

using std::thread;
using std::vector;
using std::function;

using Task = function<void()>;

class ThreadPool
{
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    //线程的启动与停止
    void start();
    void stop();

    //添加任务与获取任务
    void addTask(Task &&taskcb);
private:
    Task getTask();

    //线程池交给工作线程thread执行的任务
    void doTask();


private:
    size_t _threadNum;//子线程的数目
    vector<thread> _threads;//存放thread的数据结构
    size_t _queSize;//任务队列的大小
    TaskQueue _taskQue;//任务队列
    bool _isExit;//标识线程池是否退出的标志位

};

#endif
