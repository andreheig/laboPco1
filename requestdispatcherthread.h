#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "request.h"


class RequestDispatcherThread: public QThread
{

public:
    RequestDispatcherThread(AbstractBuffer<Request>* request, bool hasDebugLog): requests(request), hasDebugLog(hasDebugLog) {
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
        qRegisterMetaType<Request>("Request");
    }

protected:
    void run();

private:
    AbstractBuffer<Request>* requests;
    bool hasDebugLog;

};

#endif // REQUESTDISPATCHERTHREAD_H
