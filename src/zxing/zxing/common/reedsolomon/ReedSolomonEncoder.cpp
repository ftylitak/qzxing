#include "ReedSolomonEncoder.h"

#include <zxing/Exception.h>
#include <stdio.h>
#include <string.h>

namespace zxing {

ReedSolomonEncoder::ReedSolomonEncoder(QSharedPointer<GenericGF> field) :
    field_(field), cachedGenerators_()
{
    QSharedPointer<std::vector<int>> arrayRef(new std::vector<int>(1));
    (*arrayRef)[0] = 1;
    QSharedPointer< GenericGFPoly > tmpGeneratorRef(new GenericGFPoly(field.data(), arrayRef)); //TODO: recheck if .data? will work
    cachedGenerators_.push_back(tmpGeneratorRef);
}

QSharedPointer<GenericGFPoly> ReedSolomonEncoder::buildGenerator(int degree)
{
    if (degree >= int(cachedGenerators_.size())) {
        QSharedPointer<GenericGFPoly> lastGenerator = cachedGenerators_.at(cachedGenerators_.size() - 1);
        for (int d = int(cachedGenerators_.size()); d <= degree; d++)
        {
            QSharedPointer<std::vector<int>> arrayRef(new std::vector<int>(2));
            (*arrayRef)[0] = 1;
            (*arrayRef)[1] = field_->exp(d - 1 + field_->getGeneratorBase());
            QSharedPointer<GenericGFPoly> tmpGFRef(new GenericGFPoly(field_.data(), arrayRef)); //TODO: recheck if .data? will work
            QSharedPointer<GenericGFPoly> nextGenerator = (*lastGenerator).multiply(tmpGFRef);
            cachedGenerators_.push_back(nextGenerator);
            lastGenerator = nextGenerator;
        }
    }

    // ??? wont this through exception?
    // No the elements up to index degree are added above
    return cachedGenerators_.at(size_t(degree));
}

void ReedSolomonEncoder::encode(std::vector<zxing::byte> &toEncode, int ecBytes)
{
    if (ecBytes == 0) {
        throw Exception("No error correction bytes");
    }

    int dataBytes = int(toEncode.size());// - ecBytes;
    toEncode.resize(toEncode.size() + size_t(ecBytes));
    if (dataBytes <= 0) {
        throw Exception("No data bytes provided");
    }
    QSharedPointer<GenericGFPoly> generator = buildGenerator(ecBytes);
    QSharedPointer<std::vector<int>> infoCoefficients(new std::vector<int>(dataBytes));

    //to-do optimize the following loop
    for(int i=0; i< dataBytes; i++)
        (*infoCoefficients)[i] = toEncode[size_t(i)];

    QSharedPointer<GenericGFPoly> info(new GenericGFPoly(field_.data(), infoCoefficients)); //TODO: recheck if .data? will work
    info = info->multiplyByMonomial(ecBytes, 1);
    QSharedPointer<GenericGFPoly> remainder = info->divide(generator)[1];
    QSharedPointer<std::vector<int>> coefficients = remainder->getCoefficients();
    int numZeroCoefficients = ecBytes - coefficients->size();
    for (int i = 0; i < numZeroCoefficients; i++) {
        toEncode[size_t(dataBytes + i)] = 0;
    }

    for (int i = 0; i < coefficients->size(); i++)
      toEncode[size_t(dataBytes + numZeroCoefficients + i)] = zxing::byte((*coefficients)[i]);
}

}
