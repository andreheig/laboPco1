#include "requestprocess.h"
#include <iostream>

using namespace std;

void RequestProcess::run()
{
    responses->put(reqHandler.handle());
    exit(EXIT_SUCCESS);
}
