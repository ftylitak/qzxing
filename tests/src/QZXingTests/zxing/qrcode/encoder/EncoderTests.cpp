#include "EncoderTests.h"
#include <zxing/qrcode/encoder/Encoder.h>

namespace zxing{
namespace qrcode{
namespace tests{

EncoderTests::EncoderTests()
{

}

void EncoderTests::execute()
{
    testGetAlphanumericCode();
    testChooseMode();
}

void EncoderTests::testGetAlphanumericCode()
{
    // The first ten code points are numbers.
    for (int i = 0; i < 10; ++i) {
        assertEquals(i, Encoder::getAlphanumericCode('0' + i));
    }

    // The next 26 code points are capital alphabet letters.
    for (int i = 10; i < 36; ++i) {
        assertEquals(i, Encoder::getAlphanumericCode('A' + i - 10));
    }

    // Others are symbol letters
    assertEquals(36, Encoder::getAlphanumericCode(' '));
    assertEquals(37, Encoder::getAlphanumericCode('$'));
    assertEquals(38, Encoder::getAlphanumericCode('%'));
    assertEquals(39, Encoder::getAlphanumericCode('*'));
    assertEquals(40, Encoder::getAlphanumericCode('+'));
    assertEquals(41, Encoder::getAlphanumericCode('-'));
    assertEquals(42, Encoder::getAlphanumericCode('.'));
    assertEquals(43, Encoder::getAlphanumericCode('/'));
    assertEquals(44, Encoder::getAlphanumericCode(':'));

    // Should return -1 for other letters;
    assertEquals(-1, Encoder::getAlphanumericCode('a'));
    assertEquals(-1, Encoder::getAlphanumericCode('#'));
    assertEquals(-1, Encoder::getAlphanumericCode('\0'));
}

void EncoderTests::testChooseMode()
{
    // Numeric mode.
    Mode mode_(Encoder::chooseMode("0"));
    assertSame(Mode::NUMERIC, mode_);
    mode_ = Encoder::chooseMode("0123456789");
    assertSame(Mode::NUMERIC, mode_);
    // Alphanumeric mode.
    mode_ = Encoder::chooseMode("A");
    assertSame(Mode::ALPHANUMERIC, mode_);
    mode_ = Encoder::chooseMode("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:");
    assertSame(Mode::ALPHANUMERIC, mode_);
    // 8-bit byte mode.
    mode_ = Encoder::chooseMode("a");
    assertSame(Mode::BYTE, mode_);
    mode_ = Encoder::chooseMode("#");
    assertSame(Mode::BYTE, mode_);
    mode_ = Encoder::chooseMode("");
    assertSame(Mode::BYTE, mode_);
    // Kanji mode.  We used to use MODE_KANJI for these, but we stopped
    // doing that as we cannot distinguish Shift_JIS from other encodings
    // from data bytes alone.  See also comments in qrcode_encoder.h.

    // AIUE in Hiragana in Shift_JIS
//    mode_ = Encoder::chooseMode(shiftJISString(new byte[]{0x8, 0xa, 0x8, 0xa, 0x8, 0xa, 0x8, (byte) 0xa6}));
//    assertSame(Mode::BYTE,mode_);

//    // Nihon in Kanji in Shift_JIS.
//    mode_ = Encoder::chooseMode(shiftJISString(new byte[]{0x9, 0xf, 0x9, 0x7b}));
//    assertSame(Mode::BYTE, mode_);

//    // Sou-Utsu-Byou in Kanji in Shift_JIS.
//    mode_ = Encoder::chooseMode(shiftJISString(new byte[]{0xe, 0x4, 0x9, 0x5, 0x9, 0x61}));
//    assertSame(Mode::BYTE, mode_);
}


}
}
}


