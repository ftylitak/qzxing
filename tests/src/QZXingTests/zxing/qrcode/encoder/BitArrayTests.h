#ifndef BITARRAYTESTS_H
#define BITARRAYTESTS_H

#include "TestCase.h"
#include "zxing/common/BitArray.h"

namespace zxing{
namespace qrcode{
namespace tests{

class BitArrayTests : public TestCase
{
public:
    BitArrayTests();

    void execute();

private:
    static long unsigned int getUnsignedInt(BitArray &v, int index);

    void testAppendBit();
    void testAppendBits();
    void testNumBytes();
    void testAppendBitVector();
    void testXOR();
    void testXOR2();
    void testAt();
    void testToString();
};

}
}
}

#endif // BITARRAYTESTS_H
