#ifndef BITVECTORTESTS_H
#define BITVECTORTESTS_H

#include "TestCase.h"
#include "zxing/common/BitArray.h"

namespace zxing{
namespace qrcode{
namespace tests{

class BitVectorTests : public TestCase
{
public:
    BitVectorTests();

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

#endif // BITVECTORTESTS_H
