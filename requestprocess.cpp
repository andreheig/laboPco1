#include "requestprocess.h"
#include <iostream>

using namespace std;

void RequestProcess::run()
{
    responses->put(reqHandler.handle());
    return;
}
