#ifndef ENCODEVALIDATOR_H
#define ENCODEVALIDATOR_H

#include <QZXing.h>
#include <memory>
#include <vector>
#include <map>
#include <QMap>
#include <zxing/Exception.h>
#include <QtGlobal>
#include <TestCase.h>

namespace zxing {
namespace qrcode {
namespace tests{

class EncodeValidator : public TestCase
{
public:
    EncodeValidator();
    void execute();

private:
    void executeQrCodeEncodeTest();
    void testGetAlphanumericCode();

    void testChooseMode();
};

}
}
}

#endif // ENCODEVALIDATOR_H
