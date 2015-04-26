#ifndef BLOCKPAIR_H
#define BLOCKPAIR_H

#include <vector>

using namespace std;

namespace zxing {
namespace qrcode {

class BlockPair
{
private:
    vector<char> data_;
    vector<char> errorCorrection_;

public:
    BlockPair(const vector<char> &data, const vector<char> &errorCorrection) :
      data_(data), errorCorrection_(errorCorrection)  {}

    vector<char> getDataBytes() {
        return data_;
    }

    vector<char> getErrorCorrectionBytes() {
        return errorCorrection_;
    }
};

}
}

#endif //BLOCKPAIR_H
