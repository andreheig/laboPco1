#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "request.h"
#include "response.h"


/**
 * @brief The RequestDispatcherThread class
 * Classe permettant de gérer les différentes requêtes qui arrivent et
 * d'assigner une requête avec un Thread.
 */
class RequestDispatcherThread: public QThread
{

public:
    RequestDispatcherThread(AbstractBuffer<Request>* request, AbstractBuffer<Response>* responses, bool hasDebugLog): requests(request), responses(responses), hasDebugLog(hasDebugLog) {
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
        qRegisterMetaType<Request>("Request");
    }

protected:
    void run();

private:
    // Pointeur sur le tempon de requêtes afin de pouvoir se "servir"
    AbstractBuffer<Request>* requests;

    // Pointeur sur le tempon des réponses afin de pouvoir répondre à la requête associé
    AbstractBuffer<Response>* responses;

    // Booléen afin de savoir si le mode débug est activé.
    bool hasDebugLog;

};

#endif // REQUESTDISPATCHERTHREAD_H
