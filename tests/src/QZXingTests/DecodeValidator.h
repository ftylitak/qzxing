#ifndef DECODEVALIDATOR_H
#define DECODEVALIDATOR_H

#include "ValidationStats.h"
#include <QZXing.h>
#include <memory>

class DecodeValidator
{
private:
    QZXing decoder;

public:
    DecodeValidator();

    std::shared_ptr<ValidationStats> testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder,
                                                 const QImage &imageToDecode,
                                                 const QString &expectedOutput);
};

#endif // DECODEVALIDATOR_H
