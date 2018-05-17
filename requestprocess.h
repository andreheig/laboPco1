#ifndef REQUESTPROCESS_H
#define REQUESTPROCESS_H
#include <QThread>
#include "request.h"
#include "response.h"
#include "requesthandler.h"
#include "abstractbuffer.h"

class RequestProcess : public QThread
{
public:
    RequestProcess(Request request, AbstractBuffer<Response>* responses, bool hasDebug): request(request), responses(responses), hasDebug(hasDebug),
    reqHandler(request, hasDebug)
    {}
    ~RequestProcess(){}
protected:
    void run();

private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebug;
    RequestHandler reqHandler;
};
#endif // REQUESTPROCESS_H
