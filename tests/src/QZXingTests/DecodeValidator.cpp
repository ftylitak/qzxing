#include "DecodeValidator.h"

DecodeValidator::DecodeValidator() : decoder()
{
}

std::shared_ptr<ValidationStats> DecodeValidator::testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder, const QImage &imageToDecode, const QString &expectedOutput)
{
    std::shared_ptr<ValidationStats> stats_ = std::make_shared<ValidationStats>();

    decoder.setDecoder(enabledDecoder);

    QString result = decoder.decodeImage(imageToDecode, 999, 999, true);

    stats_->setElaspedTime(decoder.getProcessTimeOfLastDecoding());
    stats_->setOperationSuccess(result != "");
    stats_->setResultMatch(result == expectedOutput);

    return stats_;
}

