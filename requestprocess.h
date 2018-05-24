#ifndef REQUESTPROCESS_H
#define REQUESTPROCESS_H
#include <QThread>
#include "request.h"
#include "response.h"
#include "requesthandler.h"
#include "abstractbuffer.h"

/**
 * @brief The RequestProcess class
 * Classe permettant de traiter une requête et de fournir la réponse approprié
 */
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
    // Requête à laquel on doit fournir une réponse
    Request request;

    // Pointeur vers le buffer de réponse pour y insérer la réponse de notre requête
    AbstractBuffer<Response>* responses;

    // Booléen indiquant s'il on est en mode débug
    bool hasDebug;

    // Classe permettant de traiter notre requête
    RequestHandler reqHandler;
};
#endif // REQUESTPROCESS_H
