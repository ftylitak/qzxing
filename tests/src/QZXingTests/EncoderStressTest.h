#ifndef ENCODERSTRESSTEST_H
#define ENCODERSTRESSTEST_H

#include <QZXing.h>
#include <memory>
#include <vector>
#include <map>
#include <QMap>
#include <zxing/Exception.h>
#include <QtGlobal>
#include <TestCase.h>
#include <zxing/qrcode/decoder/Mode.h>

namespace zxing {
namespace tests{

class EncoderStressTest : public TestCase
{
public:
    EncoderStressTest();
    void execute() override;

protected:
    int getMaxCharacterNumber(zxing::qrcode::ErrorCorrectionLevel &errorCorrectionLevel, zxing::qrcode::Mode &mode);
    char getCharacterForQrMode(zxing::qrcode::Mode &mode);

    void runTests(zxing::qrcode::Mode &mode);
    void runTests(zxing::qrcode::ErrorCorrectionLevel &errorCorrectionLevel, zxing::qrcode::Mode &mode);

private:
    QZXing decoder;
    QMap<std::string, QMap<std::string, int>> maxCharacterNumberMap_;

    int sumOfSuccessfullTests;
    int totalExecutedTests;

    int currentSetupSuccessfullTests;
    int currentSetupExecutedTests;
};

}
}

#endif // ENCODERSTRESSTEST_H
