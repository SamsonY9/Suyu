#ifndef __PRODUCER_H__
#define __PRODUCER_H__

/* #include "TaskQueue.h" */

class TaskQueue;//前向声明

class Producer
{
public:
    Producer();
    ~Producer();

    void producer(TaskQueue &taskQue);

private:

};

#endif
