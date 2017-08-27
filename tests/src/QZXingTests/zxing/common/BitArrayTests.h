#ifndef BITARRAYTESTS_H
#define BITARRAYTESTS_H

#include "TestCase.h"
#include <zxing/common/BitArray.h>
#include <zxing/common/Types.h>
#include <vector>

namespace zxing{
namespace tests{

class BitArrayTests : public TestCase
{
public:
    BitArrayTests();

    void execute();

private:

    void testGetSet();
    void testGetNextSet1();
    void testGetNextSet2();
    void testGetNextSet3();
    void testGetNextSet4();
    //void testGetNextSet5();
    void testSetBulk();
    void testClear();
    void testGetArray();
    void testIsRange();
    void reverseAlgorithmTest();

private:
    static std::vector<int> reverseOriginal(std::vector<int> &oldBits, int size);
    static bool bitSet(std::vector<int> &bits, int i);
    static bool arraysAreEqual(std::vector<int> &left, std::vector<int> &right, int size);
};

}
}

#endif // BITARRAYTESTS_H
