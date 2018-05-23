#include "requestprocess.h"
#include <iostream>

using namespace std;

void RequestProcess::run()
{
    responses->put(reqHandler.handle());
<<<<<<< HEAD

=======
>>>>>>> a0baf63e6b559b5c233bb6a0fc003361b2034294
    return;
}
