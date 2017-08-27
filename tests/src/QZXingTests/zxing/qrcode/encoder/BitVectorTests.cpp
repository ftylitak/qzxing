#include "BitVectorTests.h"

namespace zxing{
namespace qrcode{
namespace tests{

BitVectorTests::BitVectorTests()
{

}

void BitVectorTests::execute()
{
    testAppendBit();
    testAppendBits();
    testNumBytes();
}

unsigned long zxing::qrcode::tests::BitVectorTests::getUnsignedInt(BitArray &v, int index)
{
    long result = 0L;
    for (int i = 0, offset = index << 3; i < 32; i++) {
        if (v.get(offset + i)) {
            result |= 1L << (31 - i);
        }
    }
    return result;
}

void BitVectorTests::testAppendBit()
{
    BitArray v;
    assertEquals(0, v.getSizeInBytes());
    // 1
    v.appendBit(true);
    assertEquals(1, v.getSize());
    assertEquals(0x80000000ul, getUnsignedInt(v, 0));
    // 10
    v.appendBit(false);
    assertEquals(2, v.getSize());
    assertEquals(0x80000000ul, getUnsignedInt(v, 0));
    // 101
    v.appendBit(true);
    assertEquals(3, v.getSize());
    assertEquals(0xa0000000ul, getUnsignedInt(v, 0));
    // 1010
    v.appendBit(false);
    assertEquals(4, v.getSize());
    assertEquals(0xa0000000ul, getUnsignedInt(v, 0));
    // 10101
    v.appendBit(true);
    assertEquals(5, v.getSize());
    assertEquals(0xa8000000ul, getUnsignedInt(v, 0));
    // 101010
    v.appendBit(false);
    assertEquals(6, v.getSize());
    assertEquals(0xa8000000ul, getUnsignedInt(v, 0));
    // 1010101
    v.appendBit(true);
    assertEquals(7, v.getSize());
    assertEquals(0xaa000000ul, getUnsignedInt(v, 0));
    // 10101010
    v.appendBit(false);
    assertEquals(8, v.getSize());
    assertEquals(0xaa000000ul, getUnsignedInt(v, 0));
    // 10101010 1
    v.appendBit(true);
    assertEquals(9, v.getSize());
    assertEquals(0xaa800000ul, getUnsignedInt(v, 0));
    // 10101010 10
    v.appendBit(false);
    assertEquals(10, v.getSize());
    assertEquals(0xaa800000ul, getUnsignedInt(v, 0));
}

void BitVectorTests::testAppendBits()
{
    BitArray v;
    v.appendBits(0x1, 1);
    assertEquals(1, v.getSize());
    assertEquals(0x80000000ul, getUnsignedInt(v, 0));
    v = BitArray();
    v.appendBits(0xff, 8);
    assertEquals(8, v.getSize());
    assertEquals(0xff000000ul, getUnsignedInt(v, 0));
    v = BitArray();
    v.appendBits(0xff7, 12);
    assertEquals(12, v.getSize());
    assertEquals(0xff700000ul, getUnsignedInt(v, 0));
}

void BitVectorTests::testNumBytes()
{
    BitArray v;
    assertEquals(0, v.getSizeInBytes());
    v.appendBit(false);
    // 1 bit was added in the vector, so 1 byte should be consumed.
    assertEquals(1, v.getSizeInBytes());
    v.appendBits(0, 7);
    assertEquals(1, v.getSizeInBytes());
    v.appendBits(0, 8);
    assertEquals(2, v.getSizeInBytes());
    v.appendBits(0, 1);
    // We now have 17 bits, so 3 bytes should be consumed.
    assertEquals(3, v.getSizeInBytes());
}

void BitVectorTests::testAppendBitVector()
{
    BitArray v1;
    v1.appendBits(0xbe, 8);
    BitArray v2;
    v2.appendBits(0xef, 8);
    v1.appendBitArray(v2);
    // beef = 1011 1110 1110 1111
    assertEquals(std::string(" X.XXXXX. XXX.XXXX"), v1.toString());
}

void BitVectorTests::testXOR()
{
    BitArray v1;
    v1.appendBits(0x5555aaaa, 32);
    BitArray v2;
    v2.appendBits(0xaaaa5555, 32);
    v1.xor_(v2);
    assertEquals(0xfffffffful, getUnsignedInt(v1, 0));
}

void BitVectorTests::testXOR2()
{
    BitArray v1;
    v1.appendBits(0x2a, 7);  // 010 1010
    BitArray v2;
    v2.appendBits(0x55, 7);  // 101 0101
    v1.xor_(v2);
    assertEquals(0xfe000000ul, getUnsignedInt(v1, 0));  // 1111 1110
}

void BitVectorTests::testAt()
{
    BitArray v;
    v.appendBits(0xdead, 16);  // 1101 1110 1010 1101
    assertTrue(v.get(0));
    assertTrue(v.get(1));
    assertFalse(v.get(2));
    assertTrue(v.get(3));

    assertTrue(v.get(4));
    assertTrue(v.get(5));
    assertTrue(v.get(6));
    assertFalse(v.get(7));

    assertTrue(v.get(8));
    assertFalse(v.get(9));
    assertTrue(v.get(10));
    assertFalse(v.get(11));

    assertTrue(v.get(12));
    assertTrue(v.get(13));
    assertFalse(v.get(14));
    assertTrue(v.get(15));
}

void BitVectorTests::testToString()
{
    BitArray v;
    v.appendBits(0xdead, 16);  // 1101 1110 1010 1101
    assertEquals(" XX.XXXX. X.X.XX.X", v.toString());
}

}
}
}
