#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"
#include "runnable.h"
#include "abstractbuffer.h"
#include <QSemaphore>

class RequestHandler : public Runnable
{
private:
    Request request;
    bool hasDebugLog;
    Response response;
    QSemaphore reponseOK;
    bool finished;
    int identite;
    AbstractBuffer<Response>* responses;

signals:
    void requestDone();

public:
    ~RequestHandler(){

    }
    void run(){
        finished = false;
        handle();
        //emit requestDone();
        finished = true;
    }

    QString id(){
        return QString::number(identite);
    }

    Response getResponse(){
        //reponseOK.acquire();
        return response;
    }

    bool isFinished(){
        return finished;
    }

    RequestHandler(Request request, bool hasDebugLog, int identite, AbstractBuffer<Response>* responses): request(request), hasDebugLog(hasDebugLog), identite(identite), responses(responses) {}

    void handle();
};

#endif // REQUESTHANDLER_H
