#ifndef BLOCKPAIR_H
#define BLOCKPAIR_H

#include <vector>
#include <zxing/common/Types.h>

using namespace std;

namespace zxing {
namespace qrcode {

class BlockPair
{
private:
    QSharedPointer<std::vector<zxing::byte>> data_;
    QSharedPointer<std::vector<zxing::byte>> errorCorrection_;

public:
    BlockPair(QSharedPointer<std::vector<zxing::byte>> data, QSharedPointer<std::vector<zxing::byte>> errorCorrection) :
      data_(data), errorCorrection_(errorCorrection)  {}

    BlockPair(const BlockPair& other) : data_(other.data_), errorCorrection_(other.errorCorrection_) {}

    QSharedPointer<std::vector<zxing::byte>> getDataBytes() { return data_; }

    QSharedPointer<std::vector<zxing::byte>> getErrorCorrectionBytes() { return errorCorrection_; }

    BlockPair& operator=(const BlockPair &other) {
        data_->clear();
        errorCorrection_->clear();

        data_ = other.data_;
        errorCorrection_ = other.errorCorrection_;

        return *this;
    }
};

}
}

#endif //BLOCKPAIR_H
