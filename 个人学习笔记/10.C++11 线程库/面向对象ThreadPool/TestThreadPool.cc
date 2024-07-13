#include "Task.h"
#include "ThreadPool.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
: public Task
{
public:
    void process() override
    {
        //MyTask到底要执行什么任务呢？
        ::srand(::clock());
        int number = ::rand() % 100;
        cout << ">>MyTask number = " << number << endl;
    }
};

//线程池的代码存在两个问题？
//Q1、任务添加了20次，但是没有全部执行完，然后程序就退出来了?
//主线程在添加完20次任务之后，会执行stop函数，而子线程在doTask
//中循环获取任务与执行任务，但是循环条件是_isExit，如果主线程
//提前将_isExit设置为true，那么子线程有可能在任务没有执行完的
//前提下就已经退出来了
//可以在stop函数中添加一行代码，只要任务队列中有任务，就可以
//让主线程不向下执行（主线程睡眠，让出CPU的控制权）
//
//Q2、任务执行完了，但是线程池无法退出？
void test()
{
    unique_ptr<Task> ptask(new MyTask());
    ThreadPool pool(4, 10);

    //线程池启动，代表子线程创建出来了，并且已经运行起来了
    pool.start();

    int cnt = 20;
    while(cnt--)
    {
        pool.addTask(ptask.get());
        cout << "cnt = " << cnt << endl;
    }
    pool.stop();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

