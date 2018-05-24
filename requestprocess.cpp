#include "requestprocess.h"
#include <iostream>

using namespace std;

void RequestProcess::run()
{
    responses->put(reqHandler.getResponse());
    exit(EXIT_SUCCESS);
}
