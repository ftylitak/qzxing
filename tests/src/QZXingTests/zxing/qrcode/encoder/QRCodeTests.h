#ifndef QRCODETESTS_H
#define QRCODETESTS_H

#include "TestCase.h"

namespace zxing{
namespace qrcode{
namespace tests{

class QRCodeTests : public TestCase
{
public:
    QRCodeTests();

    void execute();
private:
    void test();
    void testToString1();
    void testToString2();
    void testIsValidMaskPattern();
};

}
}
}

#endif // QRCODETESTS_H
