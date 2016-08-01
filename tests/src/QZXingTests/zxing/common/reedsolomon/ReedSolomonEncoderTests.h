#ifndef REEDSOLOMONENCODERTESTS_H
#define REEDSOLOMONENCODERTESTS_H

#include "TestCase.h"
#include "zxing/common/reedsolomon/ReedSolomonEncoder.h"

namespace zxing{
namespace tests{

class ReedSolomonEncoderTests : public TestCase
{
public:
    ReedSolomonEncoderTests();

    void execute();

protected:

//    const std::vector<byte>& dataBytes
//    void testEncoder(Ref<GenericGF> field, int[] dataWords, int[] ecWords);
};

}
}

#endif // REEDSOLOMONENCODERTESTS_H
