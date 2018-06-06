#ifndef THREADPOOLMANAGER_H
#define THREADPOOLMANAGER_H

#include <iostream>

#include "threadpool.h"

using namespace std;

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

    QString getFinishID(){
        cout << "finish ID" << endl;
        if (!pool->finish.isEmpty()){
            cout << "finish contient au moins un element" << endl;
            QString ret = pool->finish.front();
            cout << "numero fini: [" << ret.toStdString() << "]" << endl;
            pool->finish.pop_front();
            return ret;
        }
        else
            return "";
    }

private:
    ThreadPool* pool;

};
#endif // THREADPOOLMANAGER_H
