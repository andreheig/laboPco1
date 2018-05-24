#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "request.h"
#include "response.h"
#include "threadpool.h"

#define MAXTHREADPOOL 50

class RequestDispatcherThread: public QThread
{

public:
    RequestDispatcherThread(AbstractBuffer<Request>* request, AbstractBuffer<Response>* responses, bool hasDebugLog): requests(request), responses(responses), hasDebugLog(hasDebugLog) {
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
        qRegisterMetaType<Request>("Request");
        pool = new ThreadPool(MAXTHREADPOOL);
    }

protected:
    void run();

private:
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
    ThreadPool* pool;

};

#endif // REQUESTDISPATCHERTHREAD_H
