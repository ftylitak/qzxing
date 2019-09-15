#include <QCoreApplication>
#include <QCommandLineParser>
#include <EncodeValidator.h>

#include "DecodeValidator.h"
#include "EncoderStressTest.h"

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);
    QCoreApplication::setApplicationName("QZXingTests");

    QCommandLineParser parser;
    parser.setApplicationDescription("Executes unit tests for QZXing library");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption encoderStressTestOption(QStringList() << "encoder-stress",
                                               QCoreApplication::translate("main", "Execute stress test for Qr Code encoding and decoding"));

    parser.addOption(encoderStressTestOption);

    parser.process(application);

    bool isEncoderStressTestEnabled = parser.isSet(encoderStressTestOption);

    if(isEncoderStressTestEnabled)
    {
        zxing::tests::EncoderStressTest encoderStressTest;
        encoderStressTest.execute();
    }
    else
    {
        DecodeValidator decodeValidator;
        decodeValidator.executeTests("../../resources/");

        zxing::tests::EncodeValidator encodeValidator;
        encodeValidator.execute();
    }
}

