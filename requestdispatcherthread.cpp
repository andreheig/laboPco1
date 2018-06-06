#include "requestdispatcherthread.h"
#include "requestprocess.h"

void RequestDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request req = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request '" << req.getFilePath();
        RequestHandler* task = new RequestHandler(req, hasDebugLog, count, responses);
        poolManager.start(task);
        handling.push_back(task);
        count++;
        /*
        if(poolManager.workerEnd()){
            QString index = poolManager.getFinishID();

                for (int i = 0; i < handling.size(); ++i){
                    if (hasDebugLog)
                        qDebug() << "index: {" << index << "} id handling : (" << handling.at(i)->id() << ")" << endl;
                    if (index == handling.at(i)->id()){
                        if (hasDebugLog)
                            qDebug() << "tache finie trouve  " ;
                        responses->put(handling.at(i)->getResponse());
                        handling.removeAt(i);
                    }
                }

        }*/
    }
}
