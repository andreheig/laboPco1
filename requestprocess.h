#ifndef REQUESTPROCESS_H
#define REQUESTPROCESS_H
#include <QThread>
#include "request.h"
#include "response.h"
#include "requesthandler.h"
#include "abstractbuffer.h"
#include "runnable.h"

class RequestProcess : public Runnable
{
public:
    RequestProcess(Request request, AbstractBuffer<Response>* responses, bool hasDebug): request(request), responses(responses), hasDebug(hasDebug),
    reqHandler(request, hasDebug)
    {}
    ~RequestProcess(){}
    QString id(){

    }
protected:
    void run();

private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebug;
    RequestHandler reqHandler;
};
#endif // REQUESTPROCESS_H
