#include "EncoderStressTest.h"
#include <iostream>
#include <QtConcurrent>

namespace zxing {
namespace tests{

QMutex EncoderStressTest::printLockMutex;

EncoderStressTest::EncoderStressTest(): TestCase(),
    sumOfSuccessfullTests_(0), totalExecutedTests_(0)
{
    /**
        N     A    B
    L  7089  4296  2953
    M  5596  3391  2331
    Q  3993  2420  1663
    H  3057  1852  1273
     */

    // 4 different error correction levels
    maxCharacterNumberMap_.resize(4);

    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_L][qrcode::Mode::NUMERIC.getName()] = 7089;
    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_M][qrcode::Mode::NUMERIC.getName()] = 5596;
    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_Q][qrcode::Mode::NUMERIC.getName()] = 3993;
    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_H][qrcode::Mode::NUMERIC.getName()] = 3057;

    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_L][qrcode::Mode::ALPHANUMERIC.getName()] = 4296;
    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_M][qrcode::Mode::ALPHANUMERIC.getName()] = 3391;
    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_Q][qrcode::Mode::ALPHANUMERIC.getName()] = 2420;
    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_H][qrcode::Mode::ALPHANUMERIC.getName()] = 1852;

    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_L][qrcode::Mode::BYTE.getName()] = 2953;
    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_M][qrcode::Mode::BYTE.getName()] = 2331;
    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_Q][qrcode::Mode::BYTE.getName()] = 1663;
    maxCharacterNumberMap_[QZXing::EncodeErrorCorrectionLevel_H][qrcode::Mode::BYTE.getName()] = 1273;
}

void zxing::tests::EncoderStressTest::execute()
{
    runTests(zxing::qrcode::Mode::NUMERIC);
    runTests(zxing::qrcode::Mode::ALPHANUMERIC);
    runTests(zxing::qrcode::Mode::BYTE);

    std::cout << "total: successful: " << sumOfSuccessfullTests_ << ", total: " << totalExecutedTests_ << std::endl;
}

int EncoderStressTest::getMaxCharacterNumber(QZXing::EncodeErrorCorrectionLevel errorCorrectionLevel, qrcode::Mode &mode)
{
    if(maxCharacterNumberMap_.size() > errorCorrectionLevel &&
            maxCharacterNumberMap_[errorCorrectionLevel].contains(mode.getName()))
        return maxCharacterNumberMap_[errorCorrectionLevel][mode.getName()];
    else
        return 0;
}

char EncoderStressTest::getCharacterForQrMode(qrcode::Mode &mode)
{
/*
 N
    0-9

 A
    0 - 9
    A - Z
    (space)
    $ % * + - . / :

 B
   A + a-z
*/
    if(mode == qrcode::Mode::NUMERIC)
        return '0';
    else if (mode == qrcode::Mode::ALPHANUMERIC)
        return 'A';
    else if (mode == qrcode::Mode::BYTE)
        return 'a';
    else
        return (rand() % 256);
}

void EncoderStressTest::runTests(qrcode::Mode &mode)
{
    runTests(QZXing::EncodeErrorCorrectionLevel_L, mode);
    runTests(QZXing::EncodeErrorCorrectionLevel_M, mode);
    runTests(QZXing::EncodeErrorCorrectionLevel_Q, mode);
    runTests(QZXing::EncodeErrorCorrectionLevel_H, mode);
}

void EncoderStressTest::runTests(QZXing::EncodeErrorCorrectionLevel errorCorrectionLevel, zxing::qrcode::Mode &mode)
{
    QString currentCharacters;
    int maxCharLength = getMaxCharacterNumber(errorCorrectionLevel, mode);

    QList<TestRunData> testRunDataSet;
    for(int i=1; i<=maxCharLength; ++i)
    {
        currentCharacters += getCharacterForQrMode(mode);

        TestRunData testData;
        testData.data = currentCharacters;
        testData.errorCorrectionLevel = errorCorrectionLevel;
        testData.mode = mode;
        testRunDataSet.append(testData);
    }

    QtConcurrent::blockingMap(testRunDataSet, EncoderStressTest::runTest);
}

void EncoderStressTest::runTest(TestRunData &testData)
{
    QImage generatedImage = QZXing::encodeData(testData.data,
                                               QZXing::EncoderFormat_QR_CODE,
                                               QSize(500, 500),
                                               testData.errorCorrectionLevel);

    QZXing decoder(QZXing::DecoderFormat_QR_CODE);
    QString decodedData = decoder.decodeImage(generatedImage);
    bool wasDecoded = decoder.getLastDecodeOperationSucceded();

    testData.successful = (testData.data == decodedData);

    printLockMutex.lock();
    std::cout << "M[" << testData.mode.getName() << "], E[" << testData.errorCorrectionLevel << "], L[" << testData.data.size() << "]: " <<
                 "decoded=" << wasDecoded <<
                 ", match=" << testData.successful << std::endl;
    printLockMutex.unlock();
}

}
}

