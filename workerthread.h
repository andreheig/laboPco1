#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include "runnable.h"

class WorkerThread : QThread
{
    Q_OBJECT

private:
    Runnable* task;
public:
    WorkerThread(){}

    ~WorkerThread(){

    }

    void setTask(Runnable* task){
        this->task = task;
        this->run();
    }

    void run(){
        task->run();
    }

    QString id(){
        return "hello";

    }

};
#endif // WORKERTHREAD_H
