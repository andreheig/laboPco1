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
    bool finished = false;

public:
    WorkerThread(){}

    ~WorkerThread(){

    }

    void setTask(Runnable* task){
        finished = false;
        this->task = task;
        //this->run();
    }

    void run(){
        //cout << "launching job" << endl;
        task->run();
        finished = true;
    }

    QString id(){
        return task->id();

    }

    bool haveFinish(){
        return finished;
    }

};
#endif // WORKERTHREAD_H
