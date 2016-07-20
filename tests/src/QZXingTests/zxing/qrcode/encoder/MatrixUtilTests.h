#ifndef MATRIXUTILTESTS_H
#define MATRIXUTILTESTS_H

#include "TestCase.h"

namespace zxing{
namespace qrcode{
namespace tests{

class MatrixUtilTests : public TestCase
{
public:
    MatrixUtilTests();

    void execute();

private:
    void testClearMatrix();
    void testEmbedBasicPatterns1();
    void testEmbedBasicPatterns2();
    void testEmbedTypeInfo();
    void testEmbedVersionInfo();
    void testEmbedDataBits();
    void testBuildMatrix();
    void testFindMSBSet();
    void testCalculateBCHCode();
    void testMakeVersionInfoBits();
    void testMakeTypeInfoInfoBits();
};

}
}
}

#endif // MATRIXUTILTESTS_H
