#ifndef BITARRAYTESTS_H
#define BITARRAYTESTS_H

#include "TestCase.h"
#include "zxing/common/BitArray.h"

namespace zxing{
namespace qrcode{
namespace tests{

class BitArrayTests : public TestCase
{
private:
    static long getUnsignedInt(BitArray &v, int index);

public:
    BitArrayTests();

    void execute();
};

}
}
}

#endif // BITARRAYTESTS_H
