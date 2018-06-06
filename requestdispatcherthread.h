#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "request.h"
#include "response.h"
#include "threadpoolmanager.h"
#include "requesthandler.h"

#define MAXTHREADPOOL 50

class RequestDispatcherThread: public QThread
{

public:
    RequestDispatcherThread(AbstractBuffer<Request>* request, AbstractBuffer<Response>* responses, bool hasDebugLog): requests(request), responses(responses), hasDebugLog(hasDebugLog) {
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
        qRegisterMetaType<Request>("Request");
        poolManager = ThreadPoolManager(MAXTHREADPOOL);
        handling = QList<RequestHandler*>();
    }

    ~RequestDispatcherThread(){}
protected:
    void run();

private:
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;
    QList<RequestHandler*> handling;
    bool hasDebugLog;
    ThreadPoolManager poolManager;
    unsigned int count = 0;

};

#endif // REQUESTDISPATCHERTHREAD_H
