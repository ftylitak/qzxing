#include "BitArrayTests.h"

namespace zxing{
namespace qrcode{
namespace tests{

BitArrayTests::BitArrayTests()
{

}

void BitArrayTests::execute()
{

}

long zxing::qrcode::tests::BitArrayTests::getUnsignedInt(BitArray &v, int index)
{
    long result = 0L;
    for (int i = 0, offset = index << 3; i < 32; i++) {
        if (v.get(offset + i)) {
            result |= 1L << (31 - i);
        }
    }
    return result;
}

}
}
}
