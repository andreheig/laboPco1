#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QThread>
#include <QSemaphore>
#include <QList>

#include "runnable.h"
#include "workerthread.h"

class ThreadPool : public QThread
{
public:
    ThreadPool(int maxThreadCount): poolSize(maxThreadCount){
        currentSize = 0;
        mutex.release();
    }

    ~ThreadPool(){

    }

    /*
     * Start runnable, si un thread est dispo, si il n'y a pas de thread dispo,
     * et que l'on peut aggrandir, on augmente le nombre de thread, si il n'y a plus de
     * place dans la piscine, on
     */
    void start(Runnable* runnable){
        //while(true){
            mutex.acquire();
            WorkerThread* pointer = nullptr;
            if(currentSize == 0){
                waiting.append(new WorkerThread);
                currentSize++;
            }

            if(waiting.size() == 0 && currentSize < poolSize){
                waiting.append(new WorkerThread);
                currentSize++;
            }

            if(waiting.size() >0){
                pointer = waiting.back();
                waiting.pop_back();
                pointer->setTask(runnable);
                working.push_back(pointer);
                pointer->run();
            }
            for(int i = 0; i < working.size(); ++i){
                if(working.at(i)->isFinished()){
                    pointer = working.at(i);
                    finish.push_back(pointer);
                }
            }
            mutex.release();
        //}
    }

    bool workerEnd(){
        return (finish.size());
    }


private:
    // Permet de savoir combien de worker existe, et ce qu'ils font
    unsigned int poolSize;
    unsigned int currentSize;

    // Permet de garder une trace de leur états
    //QList<QThread*> pool;
    QList<WorkerThread*> working;
    QList<WorkerThread*> waiting;
    QList<WorkerThread*> finish;

    // Permet d'avoir de l'exclusion mutuel
    QSemaphore mutex;
};
#endif // THREADPOOL_H
