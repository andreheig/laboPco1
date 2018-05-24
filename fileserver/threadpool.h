#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QThread>
#include <QList>
#include <QtTest/QtTest>

#include "runnable.h"

class ThreadPool : public Runnable
{
public:
    /*
     * Constructeur
     */
    ThreadPool(int maxThreadCount): poolSize(maxThreadCount) {

    }

    /*
     * Destructor
     */
    virtual ~ThreadPool() {}

    /*
     * Start runnable, si un thread est dispo, si il n'y a pas de thread dispo,
     * et que l'on peut aggrandir, on augmente le nombre de thread, si il n'y a plus de
     * place dans la piscine, on
     */
    void start(Runnable* runnable){

    }

protected:
    void run();

private:
    unsigned int poolSize;
    QList<QThread> pool;
};
#endif // THREADPOOL_H
