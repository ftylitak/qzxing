#include "BitArrayTests.h"

namespace zxing{
namespace tests{

BitArrayTests::BitArrayTests()
{

}

void BitArrayTests::execute()
{
    testGetSet();
    testGetNextSet1();
    testGetNextSet2();
    testGetNextSet3();
    testGetNextSet4();
    //testGetNextSet5();
    testSetBulk();
    testClear();
    testGetArray();
    testIsRange();
    //reverseAlgorithmTest();
}

void BitArrayTests::testGetSet()
{
    BitArray array(33);
    for (int i = 0; i < 33; i++) {
        assertFalse(array.get(i));
        array.set(i);
        assertTrue(array.get(i));
    }
}

void BitArrayTests::testGetNextSet1()
{
    BitArray array(32);
    for (int i = 0; i < array.getSize(); i++) {
        assertEquals(32, array.getNextSet(i));
    }
    array = BitArray(33);
    for (int i = 0; i < array.getSize(); i++) {
        assertEquals(33, array.getNextSet(i));
    }
}

void BitArrayTests::testGetNextSet2()
{
    BitArray array(33);
    array.set(31);
    for (int i = 0; i < array.getSize(); i++) {
        assertEquals(i <= 31 ? 31 : 33, array.getNextSet(i));
    }
    array = BitArray(33);
    array.set(32);
    for (int i = 0; i < array.getSize(); i++) {
        assertEquals(32, array.getNextSet(i));
    }
}

void BitArrayTests::testGetNextSet3()
{
    BitArray array(63);
    array.set(31);
    array.set(32);
    for (int i = 0; i < array.getSize(); i++) {
        int expected;
        if (i <= 31) {
            expected = 31;
        } else if (i == 32) {
            expected = 32;
        } else {
            expected = 63;
        }
        assertEquals(expected, array.getNextSet(i));
    }
}

void BitArrayTests::testGetNextSet4()
{
    BitArray array(63);
    array.set(33);
    array.set(40);
    for (int i = 0; i < array.getSize(); i++) {
        int expected;
        if (i <= 33) {
            expected = 33;
        } else if (i <= 40) {
            expected = 40;
        } else {
            expected = 63;
        }
        assertEquals(expected, array.getNextSet(i));
    }
}

//void BitArrayTests::testGetNextSet5()
//{
//    Random r = new SecureRandom(new byte[] {(byte) 0xDE, (byte) 0xAD, (byte) 0xBE, (byte) 0xEF});
//    for (int i = 0; i < 10; i++) {
//        BitArray array = new BitArray(1 + r.nextInt(100));
//        int numSet = r.nextInt(20);
//        for (int j = 0; j < numSet; j++) {
//            array.set(r.nextInt(array.getSize()));
//        }
//        int numQueries = r.nextInt(20);
//        for (int j = 0; j < numQueries; j++) {
//            int query = r.nextInt(array.getSize());
//            int expected = query;
//            while (expected < array.getSize() && !array.get(expected)) {
//                expected++;
//            }
//            int actual = array.getNextSet(query);
//            if (actual != expected) {
//                array.getNextSet(query);
//            }
//            assertEquals(expected, actual);
//        }
//    }
//}

void BitArrayTests::testSetBulk()
{
    BitArray array(64);
    array.setBulk(32, 0xFFFF0000);
    for (int i = 0; i < 48; i++) {
        assertFalse(array.get(i));
    }
    for (int i = 48; i < 64; i++) {
        assertTrue(array.get(i));
    }
}

void BitArrayTests::testClear()
{
    BitArray array(32);
    for (int i = 0; i < 32; i++) {
        array.set(i);
    }
    array.clear();
    for (int i = 0; i < 32; i++) {
        assertFalse(array.get(i));
    }
}

void BitArrayTests::testGetArray()
{
    BitArray array(64);
    array.set(0);
    array.set(63);
    std::vector<int>& ints = array.getBitArray();
    assertEquals(1, ints[0]);
    assertEquals(INT_MIN, ints[1]);
}

void BitArrayTests::testIsRange()
{
    BitArray array(64);
    assertTrue(array.isRange(0, 64, false));
    assertFalse(array.isRange(0, 64, true));
    array.set(32);
    assertTrue(array.isRange(32, 33, true));
    array.set(31);
    assertTrue(array.isRange(31, 33, true));
    array.set(34);
    assertFalse(array.isRange(31, 35, true));
    for (int i = 0; i < 31; i++) {
        array.set(i);
    }
    assertTrue(array.isRange(0, 33, true));
    for (int i = 33; i < 64; i++) {
        array.set(i);
    }
    assertTrue(array.isRange(0, 64, true));
    assertFalse(array.isRange(0, 64, false));
}

void BitArrayTests::reverseAlgorithmTest()
{
    std::vector<int> oldBits = {128, 256, 512, 6453324, 50934953};
    for (int size = 1; size < 160; size++) {
        std::vector<int> newBitsOriginal = reverseOriginal(oldBits, size);
        BitArray newBitArray(oldBits);
        newBitArray.reverse();
        std::vector<int> newBitsNew = newBitArray.getBitArray();
        assertTrue(arraysAreEqual(newBitsOriginal, newBitsNew, size / 32 + 1));
    }
}

std::vector<int> BitArrayTests::reverseOriginal(std::vector<int> &oldBits, int size)
{
    std::vector<int> newBits(oldBits.size());
    for (int i = 0; i < size; i++) {
        if (bitSet(oldBits, size - i - 1)) {
            newBits[i / 32] |= 1 << (i & 0x1F);
        }
    }
    return newBits;
}

bool BitArrayTests::bitSet(std::vector<int> &bits, int i)
{
    return (bits[i / 32] & (1 << (i & 0x1F))) != 0;
}

bool BitArrayTests::arraysAreEqual(std::vector<int> &left, std::vector<int> &right, int size)
{
    for (int i = 0; i < size; i++) {
        if (left[i] != right[i]) {
            return false;
        }
    }
    return true;
}

}
}
