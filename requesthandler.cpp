#include <QDebug>
#include <iostream>

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
    cout << "response: " << response.getResponse().toStdString() << endl;
}
