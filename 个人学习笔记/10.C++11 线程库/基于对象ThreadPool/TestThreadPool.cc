#include "ThreadPool.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::bind;

class MyTask
{
public:
    void process() 
    {
        //MyTask到底要执行什么任务呢？
        ::srand(::clock());
        int number = ::rand() % 100;
        cout << ">>BO_ThreadPool.MyTask number = " << number << endl;
    }
};

void test()
{
    unique_ptr<MyTask> ptask(new MyTask());
    ThreadPool pool(4, 10);

    //线程池启动，代表子线程创建出来了，并且已经运行起来了
    pool.start();

    int cnt = 20;
    while(cnt--)
    {
        pool.addTask(bind(&MyTask::process, ptask.get()));
        cout << "cnt = " << cnt << endl;
    }
    pool.stop();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

