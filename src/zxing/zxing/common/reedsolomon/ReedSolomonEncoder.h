#ifndef REEDSOLOMONENCODER_H
#define REEDSOLOMONENCODER_H

#include <zxing/common/reedsolomon/GenericGFPoly.h>
#include <zxing/common/reedsolomon/GenericGF.h>
#include <zxing/common/Types.h>

namespace zxing {

class ReedSolomonEncoder
{
private:
    QSharedPointer<GenericGF> field_;
    std::vector< QSharedPointer< GenericGFPoly > >cachedGenerators_;

    QSharedPointer<GenericGFPoly> buildGenerator(int degree);

public:
    ReedSolomonEncoder(QSharedPointer<GenericGF> field);

    void encode(std::vector<zxing::byte> &toEncode, int ecBytes);
};

}

#endif // REEDSOLOMONENCODER_H
