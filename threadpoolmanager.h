#ifndef THREADPOOLMANAGER_H
#define THREADPOOLMANAGER_H

#include "threadpool.h"

class ThreadPoolManager{
public:
    ThreadPoolManager(){}
    ThreadPoolManager(int size){
        pool = new ThreadPool(size);
        pool->start();
    }
    ~ThreadPoolManager(){}

    void start(Runnable* task){
        pool->giveTask(task);
    }

    bool workerEnd(){
        return pool->workerEnd();
    }

private:
    ThreadPool* pool;

};
#endif // THREADPOOLMANAGER_H
