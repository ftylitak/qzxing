#include "TestCase.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void zxing::TestCase::initializeRandom()
{
    srand(time(NULL));
}

int zxing::TestCase::generateRandomNumber(int range)
{
    return rand() % range;
}
