#include <QDebug>
#include <iostream>
#include <string>

#include "requesthandler.h"
#include "filereader.h"

using namespace std;

void RequestHandler::handle()
{
    if (hasDebugLog)
        qDebug() << "Handling request '" << this->request.getFilePath() << "'...";
    FileReader reader(this->request.getFilePath(), this->hasDebugLog);
    if (reader.fileExists()) {
        response = Response(request, reader.readAll());
    } else {
        response = Response(request, "File not found!");
    }
    responses->put(response);
    /*reponseOK.release();
    string test = response.getResponse().toStdString().substr(0,30);
    cout << "id: " << QString::number(identite).toStdString() << endl;
    cout << "response: " << test << endl;*/
}
