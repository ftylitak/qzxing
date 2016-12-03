#ifndef REEDSOLOMONENCODERTESTS_H
#define REEDSOLOMONENCODERTESTS_H

#include "TestCase.h"
#include <zxing/common/reedsolomon/GenericGF.h>

namespace zxing{
namespace tests{

class ReedSolomonTests : public TestCase
{
private:
    static const int DECODER_RANDOM_TEST_ITERATIONS;
    static const int DECODER_TEST_ITERATIONS;

public:
    ReedSolomonTests();

    void execute();

protected:
    void testQRCode();

private:
    void corrupt(std::vector<int> &received, int howMany, int max);
    void testEncodeDecodeRandom(Ref<GenericGF> field, int dataSize, int ecSize);
    void testEncodeDecode(Ref<GenericGF> field,
                          const std::vector<int> &dataWords,
                          const std::vector<int> & ecWords);
    void testEncoder(Ref<GenericGF> field,
                     const std::vector<int> &dataWords,
                     const std::vector<int> & ecWords);
    void testDecoder(Ref<GenericGF> field,
                     const std::vector<int> &dataWords,
                     const std::vector<int> & ecWords);
};

}
}

#endif // REEDSOLOMONENCODERTESTS_H
