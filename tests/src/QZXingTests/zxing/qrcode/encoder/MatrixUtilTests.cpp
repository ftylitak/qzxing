#include "MatrixUtilTests.h"

#include <zxing/qrcode/encoder/MatrixUtil.h>
#include <zxing/qrcode/encoder/ByteMatrix.h>

namespace zxing{
namespace qrcode{
namespace tests{

MatrixUtilTests::MatrixUtilTests()
{

}

void MatrixUtilTests::execute()
{
    testClearMatrix();
    testEmbedBasicPatterns1();
    testEmbedBasicPatterns2();
    testEmbedTypeInfo();
    testEmbedVersionInfo();
    testEmbedDataBits();
    testBuildMatrix();
    testFindMSBSet();
    testCalculateBCHCode();
    testMakeVersionInfoBits();
    testMakeTypeInfoInfoBits();
}

void MatrixUtilTests::testClearMatrix() {
    ByteMatrix matrix ( 2, 2 );
    MatrixUtil::clearMatrix(matrix);
    assertEquals(255, (int)matrix.get(0, 0));
    assertEquals(255, (int)matrix.get(1, 0));
    assertEquals(255, (int)matrix.get(0, 1));
    assertEquals(255, (int)matrix.get(1, 1));
}

void MatrixUtilTests::testEmbedBasicPatterns1(){
    // Version 1.
    ByteMatrix matrix (21, 21);
    MatrixUtil::clearMatrix(matrix);
    MatrixUtil::embedBasicPatterns(*Version::getVersionForNumber(1), matrix);
    std::string expected =
            " 1 1 1 1 1 1 1 0           0 1 1 1 1 1 1 1\n"
            " 1 0 0 0 0 0 1 0           0 1 0 0 0 0 0 1\n"
            " 1 0 1 1 1 0 1 0           0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0           0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0           0 1 0 1 1 1 0 1\n"
            " 1 0 0 0 0 0 1 0           0 1 0 0 0 0 0 1\n"
            " 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 1 1 1 1 1 1\n"
            " 0 0 0 0 0 0 0 0           0 0 0 0 0 0 0 0\n"
            "             1                            \n"
            "             0                            \n"
            "             1                            \n"
            "             0                            \n"
            "             1                            \n"
            " 0 0 0 0 0 0 0 0 1                        \n"
            " 1 1 1 1 1 1 1 0                          \n"
            " 1 0 0 0 0 0 1 0                          \n"
            " 1 0 1 1 1 0 1 0                          \n"
            " 1 0 1 1 1 0 1 0                          \n"
            " 1 0 1 1 1 0 1 0                          \n"
            " 1 0 0 0 0 0 1 0                          \n"
            " 1 1 1 1 1 1 1 0                          \n";
    assertEquals(expected, matrix.toString());
}

void MatrixUtilTests::testEmbedBasicPatterns2(){
    // Version 2.  Position adjustment pattern should apppear at right
    // bottom corner.
    ByteMatrix matrix (25, 25);
    MatrixUtil::clearMatrix(matrix);
    MatrixUtil::embedBasicPatterns(*Version::getVersionForNumber(2), matrix);
    std::string expected =
            " 1 1 1 1 1 1 1 0                   0 1 1 1 1 1 1 1\n"
            " 1 0 0 0 0 0 1 0                   0 1 0 0 0 0 0 1\n"
            " 1 0 1 1 1 0 1 0                   0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0                   0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0                   0 1 0 1 1 1 0 1\n"
            " 1 0 0 0 0 0 1 0                   0 1 0 0 0 0 0 1\n"
            " 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 1 1 1 1\n"
            " 0 0 0 0 0 0 0 0                   0 0 0 0 0 0 0 0\n"
            "             1                                    \n"
            "             0                                    \n"
            "             1                                    \n"
            "             0                                    \n"
            "             1                                    \n"
            "             0                                    \n"
            "             1                                    \n"
            "             0                                    \n"
            "             1                   1 1 1 1 1        \n"
            " 0 0 0 0 0 0 0 0 1               1 0 0 0 1        \n"
            " 1 1 1 1 1 1 1 0                 1 0 1 0 1        \n"
            " 1 0 0 0 0 0 1 0                 1 0 0 0 1        \n"
            " 1 0 1 1 1 0 1 0                 1 1 1 1 1        \n"
            " 1 0 1 1 1 0 1 0                                  \n"
            " 1 0 1 1 1 0 1 0                                  \n"
            " 1 0 0 0 0 0 1 0                                  \n"
            " 1 1 1 1 1 1 1 0                                  \n";
    assertEquals(expected, matrix.toString());
}

void MatrixUtilTests::testEmbedTypeInfo() {
    // Type info bits = 100000011001110.
    ByteMatrix matrix (21, 21);
    MatrixUtil::clearMatrix(matrix);
    MatrixUtil::embedTypeInfo(ErrorCorrectionLevel::M, 5, matrix);
    std::string expected =
            "                 0                        \n"
            "                 1                        \n"
            "                 1                        \n"
            "                 1                        \n"
            "                 0                        \n"
            "                 0                        \n"
            "                                          \n"
            "                 1                        \n"
            " 1 0 0 0 0 0   0 1         1 1 0 0 1 1 1 0\n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            "                 0                        \n"
            "                 0                        \n"
            "                 0                        \n"
            "                 0                        \n"
            "                 0                        \n"
            "                 0                        \n"
            "                 1                        \n";
    assertEquals(expected, matrix.toString());
}

void MatrixUtilTests::testEmbedVersionInfo(){
    // Version info bits = 000111 110010 010100
    // Actually, version 7 QR Code has 45x45 matrix but we use 21x21 here
    // since 45x45 matrix is too big to depict.
    ByteMatrix matrix (21, 21);
    MatrixUtil::clearMatrix(matrix);
    MatrixUtil::maybeEmbedVersionInfo(*Version::getVersionForNumber(7), matrix);
    std::string expected =
            "                     0 0 1                \n"
            "                     0 1 0                \n"
            "                     0 1 0                \n"
            "                     0 1 1                \n"
            "                     1 1 1                \n"
            "                     0 0 0                \n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            " 0 0 0 0 1 0                              \n"
            " 0 1 1 1 1 0                              \n"
            " 1 0 0 1 1 0                              \n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            "                                          \n"
            "                                          \n";
    assertEquals(expected, matrix.toString());
}

void MatrixUtilTests::testEmbedDataBits() {
    // Cells other than basic patterns should be filled with zero.
    ByteMatrix matrix ( 21, 21);
    MatrixUtil::clearMatrix(matrix);
    MatrixUtil::embedBasicPatterns(*Version::getVersionForNumber(1), matrix);

    BitArray bits;
    MatrixUtil::embedDataBits(bits, -1, matrix);
    std::string expected =
            " 1 1 1 1 1 1 1 0 0 0 0 0 0 0 1 1 1 1 1 1 1\n"
            " 1 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 1\n"
            " 1 0 1 1 1 0 1 0 0 0 0 0 0 0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0 0 0 0 0 0 0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0 0 0 0 0 0 0 1 0 1 1 1 0 1\n"
            " 1 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 1\n"
            " 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 1 1 1 1 1 1\n"
            " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 1 0 1 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 1 0 1 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 1 0 1 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            " 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
    assertEquals(expected, matrix.toString());
}

void MatrixUtilTests::testBuildMatrix() {
    // From http://www.swetake.com/qr/qr7.html
    byte bytes []= {32, 65, 205, 69, 41, 220, 46, 128, 236,
                    42, 159, 74, 221, 244, 169, 239, 150, 138,
                    70, 237, 85, 224, 96, 74, 219 , 61};
    BitArray bits;
    for (byte c: bytes) {
        bits.appendBits(c, 8);
    }
    ByteMatrix matrix(21, 21);
    MatrixUtil::buildMatrix(bits,
                            ErrorCorrectionLevel::H,
                            *Version::getVersionForNumber(1),  // Version 1
                            3,  // Mask pattern 3
                            matrix);
    std::string expected =
            " 1 1 1 1 1 1 1 0 0 1 1 0 0 0 1 1 1 1 1 1 1\n"
            " 1 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 1\n"
            " 1 0 1 1 1 0 1 0 0 0 0 1 0 0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0 0 1 1 0 0 0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0 1 1 0 0 1 0 1 0 1 1 1 0 1\n"
            " 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 0 0 0 0 0 1\n"
            " 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 1 1 1 1 1 1\n"
            " 0 0 0 0 0 0 0 0 1 1 0 1 1 0 0 0 0 0 0 0 0\n"
            " 0 0 1 1 0 0 1 1 1 0 0 1 1 1 1 0 1 0 0 0 0\n"
            " 1 0 1 0 1 0 0 0 0 0 1 1 1 0 0 1 0 1 1 1 0\n"
            " 1 1 1 1 0 1 1 0 1 0 1 1 1 0 0 1 1 1 0 1 0\n"
            " 1 0 1 0 1 1 0 1 1 1 0 0 1 1 1 0 0 1 0 1 0\n"
            " 0 0 1 0 0 1 1 1 0 0 0 0 0 0 1 0 1 1 1 1 1\n"
            " 0 0 0 0 0 0 0 0 1 1 0 1 0 0 0 0 0 1 0 1 1\n"
            " 1 1 1 1 1 1 1 0 1 1 1 1 0 0 0 0 1 0 1 1 0\n"
            " 1 0 0 0 0 0 1 0 0 0 0 1 0 1 1 1 0 0 0 0 0\n"
            " 1 0 1 1 1 0 1 0 0 1 0 0 1 1 0 0 1 0 0 1 1\n"
            " 1 0 1 1 1 0 1 0 1 1 0 1 0 0 0 0 0 1 1 1 0\n"
            " 1 0 1 1 1 0 1 0 1 1 1 1 0 0 0 0 1 1 1 0 0\n"
            " 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 1 0 0\n"
            " 1 1 1 1 1 1 1 0 0 0 1 1 1 1 1 0 1 0 0 1 0\n";
    assertEquals(expected, matrix.toString());
}

void MatrixUtilTests::testFindMSBSet() {
    assertEquals(0, MatrixUtil::findMSBSet(0));
    assertEquals(1, MatrixUtil::findMSBSet(1));
    assertEquals(8, MatrixUtil::findMSBSet(0x80));
    assertEquals(8, MatrixUtil::findMSBSet(255));
    assertEquals(32, MatrixUtil::findMSBSet(0x80000000));
}

void MatrixUtilTests::testCalculateBCHCode() {
    // Encoding of type information.
    // From Appendix C in JISX0510:2004 (p 65)
    assertEquals(0xdc, MatrixUtil::calculateBCHCode(5, 0x537));
    // From http://www.swetake.com/qr/qr6.html
    assertEquals(0x1c2, MatrixUtil::calculateBCHCode(0x13, 0x537));
    // From http://www.swetake.com/qr/qr11.html
    assertEquals(0x214, MatrixUtil::calculateBCHCode(0x1b, 0x537));

    // Encofing of version information.
    // From Appendix D in JISX0510:2004 (p 68)
    assertEquals(0xc94, MatrixUtil::calculateBCHCode(7, 0x1f25));
    assertEquals(0x5bc, MatrixUtil::calculateBCHCode(8, 0x1f25));
    assertEquals(0xa99, MatrixUtil::calculateBCHCode(9, 0x1f25));
    assertEquals(0x4d3, MatrixUtil::calculateBCHCode(10, 0x1f25));
    assertEquals(0x9a6, MatrixUtil::calculateBCHCode(20, 0x1f25));
    assertEquals(0xd75, MatrixUtil::calculateBCHCode(30, 0x1f25));
    assertEquals(0xc69, MatrixUtil::calculateBCHCode(40, 0x1f25));
}

void MatrixUtilTests::testMakeVersionInfoBits() {
    // From Appendix D in JISX0510:2004 (p 68)
    BitArray bits;
    MatrixUtil::makeVersionInfoBits(*Version::getVersionForNumber(7), bits);
    assertEquals(" ...XXXXX ..X..X.X ..", bits.toString());
}

void MatrixUtilTests::testMakeTypeInfoInfoBits()  {
    // From Appendix C in JISX0510:2004 (p 65)
    BitArray bits;
    MatrixUtil::makeTypeInfoBits(ErrorCorrectionLevel::M, 5, bits);
    assertEquals(" X......X X..XXX.", bits.toString());
  }

}
}
}
