#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QObject>
#include <iostream>

#include "runnable.h"

using namespace std;

class WorkerThread : public QThread
{
    //Q_OBJECT

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
        cout << "launching job" << endl;
        task->run();
    }

    QString id(){
        return "hello";

    }

};
#endif // WORKERTHREAD_H
