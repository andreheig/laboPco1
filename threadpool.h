#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QList>
#include <iostream>

#include "runnable.h"
#include "workerthread.h"

using namespace std;

class ThreadPool : public QThread
{
public:
    ThreadPool(int maxThreadCount): poolSize(maxThreadCount){
        currentSize = taskSize = 0;
        working = QList<WorkerThread*>();
        waiting = QList<WorkerThread*>();
        finish = QList<QString>();
        runnables = QList<Runnable*>();
    }

    ~ThreadPool(){

    }
protected:

    /*
     * Start runnable, si un thread est dispo, si il n'y a pas de thread dispo,
     * et que l'on peut aggrandir, on augmente le nombre de thread, si il n'y a plus de
     * place dans la piscine, on
     */
    void run(){
        while(true){
            mutex.lock();
            WorkerThread* pointer = nullptr;

            // Permet de cheker s'il y a un Thread qui a fini
            for(int i = 0; i < working.size(); ++i){
                if(working.at(i)->haveFinish()){
                    pointer = working.at(i);
                    working.removeAt(i);
                    finish.push_back(pointer->id());
                    waiting.push_back(pointer);
                }
                pointer = nullptr;
            }

            // Cas ou la piscine est vide => 1er Thread créé
            if(currentSize == 0){
                waiting.append(new WorkerThread);
                currentSize++;
            }

            // Permet de mettre en attente si la piscine est à capacité pleine
            while(working.size() == poolSize){
                isEmpty.wait(&mutex);
            }

            // Permet de faire grandir la pool
            if(waiting.size() == 0 && currentSize < poolSize){
                waiting.append(new WorkerThread);
                currentSize++;
            }

            // Permet de donner du travail à un Thread
            if(waiting.size() >0 && runnables.size() > 0){
                pointer = waiting.back();
                waiting.pop_back();
                while(taskSize == 0){
                    isTask.wait(&mutex);
                }
                pointer->setTask(runnables.back());
                runnables.pop_back();
                working.push_back(pointer);
                pointer->run();
            }

            mutex.unlock();
        }

    }
public:
    void giveTask(Runnable* runnable){
        mutex.lock();
        runnables.push_front(runnable);
        taskSize++;
        isTask.notify_all();
        mutex.unlock();
    }

    bool workerEnd(){
        mutex.lock();
        bool ret = !finish.isEmpty();
        isEmpty.notify_all();
        mutex.unlock();
        return ret;
    }


private:
    // Permet de savoir combien de worker existe, et ce qu'ils font
    int poolSize;
    int currentSize;
    unsigned int taskSize;

    // Permet de garder une trace de leur états
    QList<WorkerThread*> working;
    QList<WorkerThread*> waiting;
public:
    QList<QString> finish;

    // Permet d'avoir de l'exclusion mutuel
    QMutex mutex;

    QList<Runnable*> runnables;

    // Permet d'avoir les conditions
    QWaitCondition isEmpty;
    QWaitCondition isFull;
    QWaitCondition isTask;
};
#endif // THREADPOOL_H
