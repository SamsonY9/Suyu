#include "Producer.h"
#include "TaskQueue.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

Producer::Producer()
{

}

Producer::~Producer()
{

}

void Producer::producer(TaskQueue &taskQue)
{
    //里面就只需要去生产任务即可
    //种随机种子
    ::srand(::clock());
    int cnt = 20;
    while(cnt--)
    {
        int number = ::rand()%100;
        taskQue.push(number);
        cout << ">>Producer produce number = " << number << endl;
        sleep(1);
    }
}
