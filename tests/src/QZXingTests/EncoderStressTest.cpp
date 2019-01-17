#include "EncoderStressTest.h"
#include <iostream>

namespace zxing {
namespace tests{

EncoderStressTest::EncoderStressTest(): TestCase(), decoder(QZXing::DecoderFormat_QR_CODE),
    sumOfSuccessfullTests(0), totalExecutedTests(0)
{
    /**
        N     A    B
    L  7089  4296  2953
    M  5596  3391  2331
    Q  3993  2420  1663
    H  3057  1852  1273
     */

    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::L.name()][qrcode::Mode::NUMERIC.getName()] = 7089;
    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::M.name()][qrcode::Mode::NUMERIC.getName()] = 5596;
    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::Q.name()][qrcode::Mode::NUMERIC.getName()] = 3993;
    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::H.name()][qrcode::Mode::NUMERIC.getName()] = 3057;

    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::L.name()][qrcode::Mode::ALPHANUMERIC.getName()] = 4296;
    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::M.name()][qrcode::Mode::ALPHANUMERIC.getName()] = 3391;
    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::Q.name()][qrcode::Mode::ALPHANUMERIC.getName()] = 2420;
    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::H.name()][qrcode::Mode::ALPHANUMERIC.getName()] = 1852;

    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::L.name()][qrcode::Mode::BYTE.getName()] = 2953;
    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::M.name()][qrcode::Mode::BYTE.getName()] = 2331;
    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::Q.name()][qrcode::Mode::BYTE.getName()] = 1663;
    maxCharacterNumberMap_[qrcode::ErrorCorrectionLevel::H.name()][qrcode::Mode::BYTE.getName()] = 1273;
}

void zxing::tests::EncoderStressTest::execute()
{
    runTests(zxing::qrcode::Mode::NUMERIC);
    runTests(zxing::qrcode::Mode::ALPHANUMERIC);
    runTests(zxing::qrcode::Mode::BYTE);

    std::cout << "total: successful: " << sumOfSuccessfullTests << ", total: " << totalExecutedTests << std::endl;
}

int EncoderStressTest::getMaxCharacterNumber(qrcode::ErrorCorrectionLevel &errorCorrectionLevel, qrcode::Mode &mode)
{
    if(maxCharacterNumberMap_.contains(errorCorrectionLevel.name()) &&
            maxCharacterNumberMap_[errorCorrectionLevel.name()].contains(mode.getName()))
        return maxCharacterNumberMap_[errorCorrectionLevel.name()][mode.getName()];
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
    runTests(zxing::qrcode::ErrorCorrectionLevel::L, mode);
    runTests(zxing::qrcode::ErrorCorrectionLevel::M, mode);
    runTests(zxing::qrcode::ErrorCorrectionLevel::Q, mode);
    runTests(zxing::qrcode::ErrorCorrectionLevel::H, mode);
}

void EncoderStressTest::runTests(zxing::qrcode::ErrorCorrectionLevel &errorCorrectionLevel, zxing::qrcode::Mode &mode)
{
    currentSetupExecutedTests = 0;
    currentSetupSuccessfullTests = 0;

    QString currentCharacters;
    int maxCharLength = getMaxCharacterNumber(errorCorrectionLevel, mode);

    for(int i=1; i<=maxCharLength; ++i)
    {
        currentCharacters += getCharacterForQrMode(mode);
        QImage generatedImage = QZXing::encodeData(currentCharacters);

        QString decodedData = decoder.decodeImage(generatedImage);

        std::cout << "M[" << mode.getName() << "], E[" << errorCorrectionLevel.name() << "], L[" << i << "]: " <<
                     "decoded=" << decoder.getLastDecodeOperationSucceded() <<
                     ", match=" << (currentCharacters == decodedData) << std::endl;

        if(decoder.getLastDecodeOperationSucceded() && (currentCharacters == decodedData))
        {
            ++sumOfSuccessfullTests;
            ++currentSetupSuccessfullTests;
        }
        ++totalExecutedTests;
        ++currentSetupExecutedTests;
    }

    std::cout << "subtotal: M[" << mode.getName() << "], E[" << errorCorrectionLevel.name() << "]: " <<
                 "successfull: " << currentSetupSuccessfullTests << ", total: " << currentSetupExecutedTests << std::endl;
}


}
}

