#ifndef BLOCKPAIR_H
#define BLOCKPAIR_H

#include <vector>
#include <zxing/common/Array.h>

using namespace std;

namespace zxing {
namespace qrcode {

class BlockPair
{
private:
    ArrayRef<char> data_;
    ArrayRef<char> errorCorrection_;

public:
    BlockPair(ArrayRef<char> data, ArrayRef<char> errorCorrection) :
      data_(data), errorCorrection_(errorCorrection)  {}

    BlockPair(const BlockPair& other) : data_(other.data_), errorCorrection_(other.errorCorrection_) {}

    ArrayRef<char> getDataBytes() { return data_; }

    ArrayRef<char> getErrorCorrectionBytes() { return errorCorrection_; }
};

}
}

#endif //BLOCKPAIR_H
