#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QThread>
#include <QList>

class ThreadPool
{
public:
    ThreadPool(int maxThreadCount){

    }

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
    unsigned int size;
    QList<QThread> pool;
};
#endif // THREADPOOL_H
