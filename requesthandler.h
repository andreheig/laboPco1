#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"
#include "runnable.h"

class RequestHandler : public Runnable
{
private:
    Request request;
    bool hasDebugLog;
    Response response;

public:
    ~RequestHandler(){

    }
    void run(){
        handle();
    }

    QString id(){

    }

    Response getResponse(){
        return response;
    }

    RequestHandler(Request request, bool hasDebugLog): request(request), hasDebugLog(hasDebugLog) {}

    void handle();
};

#endif // REQUESTHANDLER_H
