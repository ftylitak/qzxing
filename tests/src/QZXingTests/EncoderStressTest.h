#ifndef ENCODERSTRESSTEST_H
#define ENCODERSTRESSTEST_H

#include "QZXing.h"
#include <memory>
#include <vector>
#include <map>
#include <QMap>
#include <zxing/Exception.h>
#include <QtGlobal>
#include <TestCase.h>
#include <zxing/qrcode/decoder/Mode.h>
#include <QWaitCondition>
#include <QMutex>
#include <QVector>
#include <QThreadPool>
#include <QFuture>
#include <QMutex>

namespace zxing {
namespace tests{

struct TestRunData {
    QString data;
    QZXing::EncodeErrorCorrectionLevel errorCorrectionLevel;
    qrcode::Mode mode;

    bool successful;

public:
    TestRunData(): data(""), errorCorrectionLevel(QZXing::EncodeErrorCorrectionLevel_L),
        mode(qrcode::Mode::BYTE), successful(false) {}
};

class EncoderStressTest : public TestCase
{
public:
    EncoderStressTest();
    void execute() override;

protected:
    int getMaxCharacterNumber(QZXing::EncodeErrorCorrectionLevel errorCorrectionLevel, zxing::qrcode::Mode &mode);
    char getCharacterForQrMode(zxing::qrcode::Mode &mode);

    void runTests(zxing::qrcode::Mode &mode);
    void runTests(QZXing::EncodeErrorCorrectionLevel errorCorrectionLevel, zxing::qrcode::Mode &mode);

    static void runTest(TestRunData &testData);

private:
    QVector<QMap<std::string, int>> maxCharacterNumberMap_;
    size_t sumOfSuccessfullTests_;
    size_t totalExecutedTests_;

    static QMutex printLockMutex;
};

}
}

#endif // ENCODERSTRESSTEST_H
