#ifndef ENCODERTESTS_H
#define ENCODERTESTS_H

#include "TestCase.h"

namespace zxing{
namespace qrcode{
namespace tests{

class EncoderTests : public TestCase
{
public:
    EncoderTests();

    void execute();

private:
    void testGetAlphanumericCode();
    void testChooseMode();
    //void testEncode();
    //void testSimpleUTF8ECI();
    void testAppendModeInfo();
    void testAppendLengthInfo();
    void testAppendBytes();

    static std::string shiftJISString(byte bytes[]);
};

}
}
}

#endif // ENCODERTESTS_H
