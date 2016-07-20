#ifndef MASKUTILTESTS_H
#define MASKUTILTESTS_H

#include "TestCase.h"

namespace zxing{
namespace qrcode{
namespace tests{

class MaskUtilTests : public TestCase
{  
public:
    MaskUtilTests();

    void execute();

private:
    void testApplyMaskPenaltyRule1();
    void testApplyMaskPenaltyRule2();
    void testApplyMaskPenaltyRule3();
    void testApplyMaskPenaltyRule4();
    void testGetDataMaskBit();

    static bool TestGetDataMaskBitInternal(int maskPattern, int expected[][6]);
};

}
}
}

#endif // MASKUTILTESTS_H
