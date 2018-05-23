#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QThread>
#include <QSemaphore>
#include <QList>

#include "runnable.h"

class ThreadPool
{
public:
    ThreadPool(int maxThreadCount): poolSize(maxThreadCount){
        currentSize = runnerWorking = runnerWaiting = 0;
    }

    ~ThreadPool(){

    }

    /*
     * Start runnable, si un thread est dispo, si il n'y a pas de thread dispo,
     * et que l'on peut aggrandir, on augmente le nombre de thread, si il n'y a plus de
     * place dans la piscine, on
     */
    void start(Runnable* runnable){
        if(currentSize < poolSize){

        }
        runnable->start;
    }

protected:
    void run();

private:
    // Permet de savoir combien de worker existe, et ce qu'ils font
    unsigned int poolSize;
    unsigned int currentSize;
    unsigned int runnerWorking;
    unsigned int runnerWaiting;

    // Permet de garder une trace de leur états
    QList<Runnable> pool;
    QList<Runnable> working;
    QList<Runnable> waiting;

    // Permet d'avoir de l'exclusion mutuel
    QSemaphore mutex;
};
#endif // THREADPOOL_H
