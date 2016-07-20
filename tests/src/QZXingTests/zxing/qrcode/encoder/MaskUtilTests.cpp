#include "MaskUtilTests.h"
#include <zxing/qrcode/encoder/ByteMatrix.h>
#include <zxing/qrcode/encoder/MaskUtil.h>

namespace zxing{
namespace qrcode{
namespace tests{

MaskUtilTests::MaskUtilTests()
{

}

void MaskUtilTests::execute()
{
    testApplyMaskPenaltyRule1();
    testApplyMaskPenaltyRule2();
    testApplyMaskPenaltyRule3();
    testApplyMaskPenaltyRule4();
    testGetDataMaskBit();
}

void MaskUtilTests::testApplyMaskPenaltyRule1()
{
    ByteMatrix matrix(4, 1);
    matrix.set(0, 0,(byte) 0);
    matrix.set(1, 0,(byte) 0);
    matrix.set(2, 0,(byte) 0);
    matrix.set(3, 0,(byte) 0);
    assertEquals(0, MaskUtil::applyMaskPenaltyRule1(matrix));

    // Horizontal.
    matrix = ByteMatrix(6, 1);
    matrix.set(0, 0,(byte) 0);
    matrix.set(1, 0,(byte) 0);
    matrix.set(2, 0,(byte) 0);
    matrix.set(3, 0,(byte) 0);
    matrix.set(4, 0,(byte) 0);
    matrix.set(5, 0,(byte) 1);
    assertEquals(3, MaskUtil::applyMaskPenaltyRule1(matrix));
    matrix.set(5, 0, (byte)0);
    assertEquals(4, MaskUtil::applyMaskPenaltyRule1(matrix));
    // Vertical.
    matrix = ByteMatrix(1, 6);
    matrix.set(0, 0, (byte)0);
    matrix.set(0, 1, (byte)0);
    matrix.set(0, 2, (byte)0);
    matrix.set(0, 3, (byte)0);
    matrix.set(0, 4, (byte)0);
    matrix.set(0, 5, (byte)1);
    assertEquals(3, MaskUtil::applyMaskPenaltyRule1(matrix));
    matrix.set(0, 5, (byte)0);
    assertEquals(4, MaskUtil::applyMaskPenaltyRule1(matrix));
}

void MaskUtilTests::testApplyMaskPenaltyRule2()
{
    ByteMatrix matrix(1, 1);
    matrix.set(0, 0, (byte)0);
    assertEquals(0, MaskUtil::applyMaskPenaltyRule2(matrix));

    matrix = ByteMatrix(2, 2);
    matrix.set(0, 0, (byte)0);
    matrix.set(1, 0, (byte)0);
    matrix.set(0, 1, (byte)0);
    matrix.set(1, 1, (byte)1);
    assertEquals(0, MaskUtil::applyMaskPenaltyRule2(matrix));

    matrix = ByteMatrix(2, 2);
    matrix.set(0, 0, (byte)0);
    matrix.set(1, 0, (byte)0);
    matrix.set(0, 1, (byte)0);
    matrix.set(1, 1, (byte)0);
    assertEquals(3, MaskUtil::applyMaskPenaltyRule2(matrix));

    matrix = ByteMatrix(3, 3);
    matrix.set(0, 0, (byte)0);
    matrix.set(1, 0, (byte)0);
    matrix.set(2, 0, (byte)0);
    matrix.set(0, 1, (byte)0);
    matrix.set(1, 1, (byte)0);
    matrix.set(2, 1, (byte)0);
    matrix.set(0, 2, (byte)0);
    matrix.set(1, 2, (byte)0);
    matrix.set(2, 2, (byte)0);
    // Four instances of 2x2 blocks.
    assertEquals(3 * 4, MaskUtil::applyMaskPenaltyRule2(matrix));
}

void MaskUtilTests::testApplyMaskPenaltyRule3()
{
    // Horizontal 00001011101.
    ByteMatrix matrix = ByteMatrix(11, 1);
    matrix.set(0, 0, (byte)0);
    matrix.set(1, 0, (byte)0);
    matrix.set(2, 0, (byte)0);
    matrix.set(3, 0, (byte)0);
    matrix.set(4, 0, (byte)1);
    matrix.set(5, 0, (byte)0);
    matrix.set(6, 0, (byte)1);
    matrix.set(7, 0, (byte)1);
    matrix.set(8, 0, (byte)1);
    matrix.set(9, 0, (byte)0);
    matrix.set(10, 0, (byte)1);
    assertEquals(40, MaskUtil::applyMaskPenaltyRule3(matrix));

    // Horizontal 10111010000.
    matrix = ByteMatrix(11, 1);
    matrix.set(0, 0, (byte)1);
    matrix.set(1, 0, (byte)0);
    matrix.set(2, 0, (byte)1);
    matrix.set(3, 0, (byte)1);
    matrix.set(4, 0, (byte)1);
    matrix.set(5, 0, (byte)0);
    matrix.set(6, 0, (byte)1);
    matrix.set(7, 0, (byte)0);
    matrix.set(8, 0, (byte)0);
    matrix.set(9, 0, (byte)0);
    matrix.set(10, 0, (byte)0);
    assertEquals(40, MaskUtil::applyMaskPenaltyRule3(matrix));

    // Vertical 00001011101.
    matrix = ByteMatrix(1, 11);
    matrix.set(0, 0, (byte)0);
    matrix.set(0, 1, (byte)0);
    matrix.set(0, 2, (byte)0);
    matrix.set(0, 3, (byte)0);
    matrix.set(0, 4, (byte)1);
    matrix.set(0, 5, (byte)0);
    matrix.set(0, 6, (byte)1);
    matrix.set(0, 7, (byte)1);
    matrix.set(0, 8, (byte)1);
    matrix.set(0, 9, (byte)0);
    matrix.set(0, 10, (byte)1);
    assertEquals(40, MaskUtil::applyMaskPenaltyRule3(matrix));

    // Vertical 10111010000.
    matrix = ByteMatrix(1, 11);
    matrix.set(0, 0, (byte)1);
    matrix.set(0, 1, (byte)0);
    matrix.set(0, 2, (byte)1);
    matrix.set(0, 3, (byte)1);
    matrix.set(0, 4, (byte)1);
    matrix.set(0, 5, (byte)0);
    matrix.set(0, 6, (byte)1);
    matrix.set(0, 7, (byte)0);
    matrix.set(0, 8, (byte)0);
    matrix.set(0, 9, (byte)0);
    matrix.set(0, 10, (byte)0);
    assertEquals(40, MaskUtil::applyMaskPenaltyRule3(matrix));
}

void MaskUtilTests::testApplyMaskPenaltyRule4()
{
    // Dark cell ratio = 0%
    ByteMatrix matrix = ByteMatrix(1, 1);
    matrix.set(0, 0, (byte)0);
    assertEquals(100, MaskUtil::applyMaskPenaltyRule4(matrix));

    // Dark cell ratio = 5%
    matrix = ByteMatrix(2, 1);
    matrix.set(0, 0, (byte)0);
    matrix.set(0, 0, (byte)1);
    assertEquals(0, MaskUtil::applyMaskPenaltyRule4(matrix));

    // Dark cell ratio = 66.67%
    matrix = ByteMatrix(6, 1);
    matrix.set(0, 0, (byte)0);
    matrix.set(1, 0, (byte)1);
    matrix.set(2, 0, (byte)1);
    matrix.set(3, 0, (byte)1);
    matrix.set(4, 0, (byte)1);
    matrix.set(5, 0, (byte)0);
    assertEquals(30, MaskUtil::applyMaskPenaltyRule4(matrix));
}

void MaskUtilTests::testGetDataMaskBit()
{
    int mask0[6][6] = {
        {1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1},
    };
    assertTrue(TestGetDataMaskBitInternal(0,  mask0));
    int mask1[6][6] = {
        {1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0},
    };
    assertTrue(TestGetDataMaskBitInternal(1,  mask1));
    int mask2[6][6] = {
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0},
    };
    assertTrue(TestGetDataMaskBitInternal(2, mask2));
    int mask3[6][6] = {
        {1, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 0},
    };
    assertTrue(TestGetDataMaskBitInternal(3, mask3));
    int mask4[6][6] = {
        {1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 0},
    };
    assertTrue(TestGetDataMaskBitInternal(4, mask4));
    int mask5[6][6] = {
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0},
    };
    assertTrue(TestGetDataMaskBitInternal(5, mask5));
    int mask6[6][6] = {
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0},
        {1, 1, 0, 1, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 1},
    };
    assertTrue(TestGetDataMaskBitInternal(6, mask6));
    int mask7[6][6] = {
        {1, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 1},
        {1, 0, 0, 0, 1, 1},
        {0, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 0, 0},
        {0, 1, 1, 1, 0, 0},
    };
    assertTrue(TestGetDataMaskBitInternal(7, mask7));
}

bool MaskUtilTests::TestGetDataMaskBitInternal(int maskPattern, int expected[][6])
{
    for (int x = 0; x < 6; ++x) {
        for (int y = 0; y < 6; ++y) {
            if ((expected[y][x] == 1) != MaskUtil::getDataMaskBit(maskPattern, x, y)) {
                return false;
            }
        }
    }
    return true;

}

}
}
}
