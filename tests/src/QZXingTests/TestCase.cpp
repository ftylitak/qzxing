#include "TestCase.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

namespace zxing{

void TestCase::initializeRandom()
{
    srand(time(NULL));
}

int TestCase::generateRandomNumber(int range)
{
    return rand() % range;
}

}
