#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void test()
{
    TaskQueue taskQue(10);
    Producer pro1;
    Consumer con1;

    thread pro(&Producer::producer, &pro1, std::ref(taskQue));
    thread con(&Consumer::consume, &con1, std::ref(taskQue));

    pro.join();
    con.join();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

