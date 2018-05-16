#include "requestdispatcherthread.h"

void RequestDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request req = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request '" << req.getFilePath();

    }
}
