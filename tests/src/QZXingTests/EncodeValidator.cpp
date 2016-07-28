#include "EncodeValidator.h"
#include <zxing/qrcode/encoder/QRCode.h>
#include <zxing/qrcode/encoder/ByteMatrix.h>
#include <zxing/qrcode/encoder/Encoder.h>
#include "TestCase.h"
#include "zxing/qrcode/encoder/MatrixUtilTests.h"
#include "zxing/qrcode/encoder/MaskUtilTests.h"
#include "zxing/qrcode/encoder/BitArrayTests.h"
#include "zxing/qrcode/encoder/QRCodeTests.h"
#include "zxing/qrcode/encoder/EncoderTests.h"

namespace zxing {
namespace qrcode {
namespace tests{

EncodeValidator::EncodeValidator()
{

}

void EncodeValidator::execute()
{
    try{
        MatrixUtilTests t;
        t.execute();

        MaskUtilTests t1;
        t1.execute();

        BitArrayTests t2;
        t2.execute();

        QRCodeTests t3;
        t3.execute();

        EncoderTests t4;
        t4.execute();
    } catch(zxing::Exception &e) {
        qDebug() << e.what();
    }
}

void EncodeValidator::executeQrCodeEncodeTest()
{
    //     zxing::qrcode::QRCode qrCode = new zxing::qrcode::QRCode();

    //    // First, test simple setters and getters.
    //    // We use numbers of version 7-H.
    //    qrCode.setMode(zxing::qrcode::Mode.BYTE);
    //    qrCode.setECLevel(zxing::qrcode::ErrorCorrectionLevel.H);
    //    qrCode.setVersion(zxing::qrcode::Version.getVersionForNumber(7));
    //    qrCode.setMaskPattern(3);

    //    bool modeEquals = Mode.BYTE == qrCode.getMode();
    //    bool errorCodeEquals = zxing::qrcode::ErrorCorrectionLevel.H == qrCode.getECLevel();
    //    bool versionEquals = 7 == qrCode.getVersion().getVersionNumber();
    //    bool maskPatternEquals = 3 = qrCode.getMaskPattern();

    //    // Prepare the matrix.
    //    zxing::qrcode::ByteMatrix matrix = new zxing::qrcode::ByteMatrix(45, 45);
    //    // Just set bogus zero/one values.
    //    for (int y = 0; y < 45; ++y) {
    //      for (int x = 0; x < 45; ++x) {
    //        matrix.set(x, y, (y + x) % 2);
    //      }
    //    }

    //    // Set the matrix.
    //    qrCode.setMatrix(matrix);
    //    assertSame(matrix, qrCode.getMatrix());
}

void EncodeValidator::testGetAlphanumericCode() {
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

void EncodeValidator::testChooseMode(){
    //    // Numeric mode.
    //    assertSame(Mode::NUMERIC, Mode::chooseMode("0"));
    //    assertSame(Mode::NUMERIC, Mode::chooseMode("0123456789"));
    //    // Alphanumeric mode.
    //    assertSame(Mode::ALPHANUMERIC, Mode::chooseMode("A"));
    //    assertSame(Mode::ALPHANUMERIC,
    //               Encoder.chooseMode("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:"));
    //    // 8-bit byte mode.
    //    assertSame(Mode::BYTE, Mode::chooseMode("a"));
    //    assertSame(Mode::BYTE, Mode::chooseMode("#"));
    //    assertSame(Mode::BYTE, Mode::chooseMode(""));
    //    // Kanji mode.  We used to use MODE_KANJI for these, but we stopped
    //    // doing that as we cannot distinguish Shift_JIS from other encodings
    //    // from data bytes alone.  See also comments in qrcode_encoder.h.

    //    // AIUE in Hiragana in Shift_JIS
    //    assertSame(Mode::BYTE,
    //               Encoder::chooseMode(shiftJISString(new byte[]{0x8, 0xa, 0x8, 0xa, 0x8, 0xa, 0x8, (byte) 0xa6})));

    //    // Nihon in Kanji in Shift_JIS.
    //    assertSame(Mode::BYTE, Encoder::chooseMode(shiftJISString(new byte[]{0x9, 0xf, 0x9, 0x7b})));

    //    // Sou-Utsu-Byou in Kanji in Shift_JIS.
    //    assertSame(Mode::BYTE, Encoder::chooseMode(shiftJISString(new byte[]{0xe, 0x4, 0x9, 0x5, 0x9, 0x61})));
}

}
}
}
