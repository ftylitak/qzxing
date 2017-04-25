#ifndef ENCODERTESTS_H
#define ENCODERTESTS_H

#include "TestCase.h"
#include <zxing/qrcode/encoder/Encoder.h>

namespace zxing{
namespace qrcode{
namespace tests{

class EncoderTests;
class EncoderHack : public Encoder {
    friend class zxing::qrcode::tests::EncoderTests;
};

class EncoderTests : public TestCase
{

public:
    EncoderTests();

    void execute();

private:
    void testGetAlphanumericCode();
    void testChooseMode();
    void testEncode();
    //void testSimpleUTF8ECI();
    void testAppendModeInfo();
    void testAppendLengthInfo();
    void testAppendBytes();
    void testTerminateBits();
    void testGetNumDataBytesAndNumECBytesForBlockID();
    void testInterleaveWithECBytes();
    void testAppendNumericBytes();
    void testAppendAlphanumericBytes();
    void testAppend8BitBytes();
    //void testAppendKanjiBytes(); not yet supported
    void testGenerateECBytes();

    static std::string shiftJISString(byte bytes[]);
};

}
}
}

#endif // ENCODERTESTS_H
