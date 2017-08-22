#include "QRCodeTests.h"
#include <zxing/qrcode/encoder/QRCode.h>

namespace zxing{
namespace qrcode{
namespace tests{

QRCodeTests::QRCodeTests()
{

}

void QRCodeTests::execute()
{
    test();
    testToString1();
    testToString2();
    testIsValidMaskPattern();
}

void QRCodeTests::test()
{
    QRCode qrCode;

    // First, test simple setters and getters.
    // We use numbers of version 7-H.
    qrCode.setMode(Mode::BYTE);
    qrCode.setECLevel(Ref<ErrorCorrectionLevel>(new ErrorCorrectionLevel(ErrorCorrectionLevel::H)));
    qrCode.setVersion(Version::getVersionForNumber(7));
    qrCode.setMaskPattern(3);

    assertEquals(7, qrCode.getVersion()->getVersionNumber());
    assertEquals(3, qrCode.getMaskPattern());

    // Prepare the matrix.
    Ref<ByteMatrix> matrix(new ByteMatrix(45, 45));
    // Just set bogus zero/one values.
    for (int y = 0; y < 45; ++y) {
        for (int x = 0; x < 45; ++x) {
            matrix->set(x, y, (byte)((y + x) % 2));
        }
    }

    // Set the matrix.
    qrCode.setMatrix(matrix);
    assertSame(matrix, qrCode.getMatrix());
}

void QRCodeTests::testToString1() {
    QRCode qrCode;
    std::string expected =
            "<<\n"
            " mode: null\n"
            " ecLevel: null\n"
            " version: null\n"
            " maskPattern: -1\n"
            " matrix: null\n"
            "\n>>";
    assertEquals(expected, qrCode.toString());
}

void QRCodeTests::testToString2()
{
    QRCode qrCode;
    qrCode.setMode(Mode::BYTE);
    qrCode.setECLevel(Ref<ErrorCorrectionLevel>(new ErrorCorrectionLevel(ErrorCorrectionLevel::H)));
    qrCode.setVersion(Version::getVersionForNumber(1));
    qrCode.setMaskPattern(3);
    Ref<ByteMatrix> matrix(new ByteMatrix(21, 21));
    for (int y = 0; y < 21; ++y) {
        for (int x = 0; x < 21; ++x) {
            matrix->set(x, y, (byte)((y + x) % 2));
        }
    }
    qrCode.setMatrix(matrix);
    std::string expected = "<<\n"
            " mode: BYTE\n"
            " ecLevel: H\n"
            " version: 1\n"
            " maskPattern: 3\n"
            " matrix:\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            " 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1\n"
            " 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0\n"
            "\n>>";

    assertEquals(expected, qrCode.toString());
}

void QRCodeTests::testIsValidMaskPattern()
{
    assertFalse(QRCode::isValidMaskPattern(-1));
    assertTrue(QRCode::isValidMaskPattern(0));
    assertTrue(QRCode::isValidMaskPattern(7));
    assertFalse(QRCode::isValidMaskPattern(8));
}

}
}
}
