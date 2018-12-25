#include "EncoderTests.h"

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
    testAppendModeInfo();
    testAppendBytes();
    testAppendLengthInfo();
    testGetNumDataBytesAndNumECBytesForBlockID();
    testTerminateBits();
    testInterleaveWithECBytes();
    testGenerateECBytes();
    testAppendNumericBytes();
    testAppendAlphanumericBytes();
    testAppend8BitBytes();
    testEncode();
}

void EncoderTests::testGetAlphanumericCode()
{
    // The first ten code points are numbers.
    for (int i = 0; i < 10; ++i) {
        assertEquals(i, EncoderHack::getAlphanumericCode('0' + i));
    }

    // The next 26 code points are capital alphabet letters.
    for (int i = 10; i < 36; ++i) {
        assertEquals(i, EncoderHack::getAlphanumericCode('A' + i - 10));
    }

    // Others are symbol letters
    assertEquals(36, EncoderHack::getAlphanumericCode(' '));
    assertEquals(37, EncoderHack::getAlphanumericCode('$'));
    assertEquals(38, EncoderHack::getAlphanumericCode('%'));
    assertEquals(39, EncoderHack::getAlphanumericCode('*'));
    assertEquals(40, EncoderHack::getAlphanumericCode('+'));
    assertEquals(41, EncoderHack::getAlphanumericCode('-'));
    assertEquals(42, EncoderHack::getAlphanumericCode('.'));
    assertEquals(43, EncoderHack::getAlphanumericCode('/'));
    assertEquals(44, EncoderHack::getAlphanumericCode(':'));

    // Should return -1 for other letters;
    assertEquals(-1, EncoderHack::getAlphanumericCode('a'));
    assertEquals(-1, EncoderHack::getAlphanumericCode('#'));
    assertEquals(-1, EncoderHack::getAlphanumericCode('\0'));
}

void EncoderTests::testChooseMode()
{
    // Numeric mode.
    Mode mode_(EncoderHack::chooseMode("0"));
    assertSame(Mode::NUMERIC, mode_);
    mode_ = EncoderHack::chooseMode("0123456789");
    assertSame(Mode::NUMERIC, mode_);
    // Alphanumeric mode.
    mode_ = EncoderHack::chooseMode("A");
    assertSame(Mode::ALPHANUMERIC, mode_);
    mode_ = EncoderHack::chooseMode("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:");
    assertSame(Mode::ALPHANUMERIC, mode_);
    // 8-bit byte mode.
    mode_ = EncoderHack::chooseMode("a");
    assertSame(Mode::BYTE, mode_);
    mode_ = EncoderHack::chooseMode("#");
    assertSame(Mode::BYTE, mode_);
    mode_ = EncoderHack::chooseMode("");
    assertSame(Mode::BYTE, mode_);
    // Kanji mode.  We used to use MODE_KANJI for these, but we stopped
    // doing that as we cannot distinguish Shift_JIS from other encodings
    // from data bytes alone.  See also comments in qrcode_encoder.h.

    // AIUE in Hiragana in Shift_JIS
    //    mode_ = EncoderHack::chooseMode(shiftJISString(new byte[]{0x8, 0xa, 0x8, 0xa, 0x8, 0xa, 0x8, (byte) 0xa6}));
    //    assertSame(Mode::BYTE,mode_);

    //    // Nihon in Kanji in Shift_JIS.
    //    mode_ = EncoderHack::chooseMode(shiftJISString(new byte[]{0x9, 0xf, 0x9, 0x7b}));
    //    assertSame(Mode::BYTE, mode_);

    //    // Sou-Utsu-Byou in Kanji in Shift_JIS.
    //    mode_ = EncoderHack::chooseMode(shiftJISString(new byte[]{0xe, 0x4, 0x9, 0x5, 0x9, 0x61}));
    //    assertSame(Mode::BYTE, mode_);
}

void EncoderTests::testEncode()
{
    Ref<QRCode> qrCode = Encoder::encode("ABCDEF", ErrorCorrectionLevel::H);
    const std::string expected =
            "<<\n"
            " mode: ALPHANUMERIC\n"
            " ecLevel: H\n"
            " version: 1\n"
            " maskPattern: 4\n"
            " matrix:\n"
            " 1 1 1 1 1 1 1 0 0 1 0 1 0 0 1 1 1 1 1 1 1\n"
            " 1 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 0 0 0 0 1\n"
            " 1 0 1 1 1 0 1 0 0 0 0 0 0 0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0 0 1 0 0 1 0 1 0 1 1 1 0 1\n"
            " 1 0 1 1 1 0 1 0 0 1 0 1 0 0 1 0 1 1 1 0 1\n"
            " 1 0 0 0 0 0 1 0 1 0 0 1 1 0 1 0 0 0 0 0 1\n"
            " 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 1 1 1 1 1 1\n"
            " 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0\n"
            " 0 0 0 0 1 1 1 1 0 1 1 0 1 0 1 1 0 0 0 1 0\n"
            " 0 0 0 0 1 1 0 1 1 1 0 0 1 1 1 1 0 1 1 0 1\n"
            " 1 0 0 0 0 1 1 0 0 1 0 1 0 0 0 1 1 1 0 1 1\n"
            " 1 0 0 1 1 1 0 0 1 1 1 1 0 0 0 0 1 0 0 0 0\n"
            " 0 1 1 1 1 1 1 0 1 0 1 0 1 1 1 0 0 1 1 0 0\n"
            " 0 0 0 0 0 0 0 0 1 1 0 0 0 1 1 0 0 0 1 0 1\n"
            " 1 1 1 1 1 1 1 0 1 1 1 1 0 0 0 0 0 1 1 0 0\n"
            " 1 0 0 0 0 0 1 0 1 1 0 1 0 0 0 1 0 1 1 1 1\n"
            " 1 0 1 1 1 0 1 0 1 0 0 1 0 0 0 1 1 0 0 1 1\n"
            " 1 0 1 1 1 0 1 0 0 0 1 1 0 1 0 0 0 0 1 1 1\n"
            " 1 0 1 1 1 0 1 0 0 1 0 1 0 0 0 1 1 0 0 0 0\n"
            " 1 0 0 0 0 0 1 0 0 1 0 0 1 0 0 1 1 0 0 0 1\n"
            " 1 1 1 1 1 1 1 0 0 0 1 0 0 1 0 0 0 0 1 1 1\n"
            ">>\n";
    assertEquals(expected, qrCode->toString());
}

void EncoderTests::testAppendModeInfo()
{
    BitArray bits;
    EncoderHack::appendModeInfo(Mode::NUMERIC, bits);
    assertEquals(" ...X", bits.toString());
}

void EncoderTests::testAppendLengthInfo()
{
    BitArray bits;
    EncoderHack::appendLengthInfo(1,  // 1 letter (1/1).
                                  *Version::getVersionForNumber(1),
                                  Mode::NUMERIC,
                                  bits);
    assertEquals(" ........ .X", bits.toString());  // 10 bits.
    bits = BitArray();
    EncoderHack::appendLengthInfo(2,  // 2 letters (2/1).
                                  *Version::getVersionForNumber(10),
                                  Mode::ALPHANUMERIC,
                                  bits);
    assertEquals(" ........ .X.", bits.toString());  // 11 bits.
    bits = BitArray();
    EncoderHack::appendLengthInfo(255,  // 255 letter (255/1).
                                  *Version::getVersionForNumber(27),
                                  Mode::BYTE,
                                  bits);
    assertEquals(" ........ XXXXXXXX", bits.toString());  // 16 bits.
    //    bits = BitArray();
    //    EncoderHack::appendLengthInfo(512,  // 512 letters (1024/2).
    //                             *Version::getVersionForNumber(40),
    //                             Mode::KANJI,
    //                             bits);
    //    assertEquals(" ..X..... ....", bits.toString());  // 12 bits.
}

void EncoderTests::testAppendBytes()
{
    // Should use appendNumericBytes.
    // 1 = 01 = 0001 in 4 bits.
    BitArray bits;
    EncoderHack::appendBytes("1", Mode::NUMERIC, bits, EncoderHack::DEFAULT_BYTE_MODE_ENCODING);
    assertEquals(" ...X" , bits.toString());
    // Should use appendAlphanumericBytes.
    // A = 10 = 0xa = 001010 in 6 bits
    bits = BitArray();
    EncoderHack::appendBytes("A", Mode::ALPHANUMERIC, bits, EncoderHack::DEFAULT_BYTE_MODE_ENCODING);
    assertEquals(" ..X.X." , bits.toString());
    // Lower letters such as 'a' cannot be encoded in MODE_ALPHANUMERIC.
    ASSERT_THROWS(
                EncoderHack::appendBytes("a", Mode::ALPHANUMERIC, bits, EncoderHack::DEFAULT_BYTE_MODE_ENCODING);
            )
            // Should use append8BitBytes.
            // 0x61, 0x62, 0x63
            bits = BitArray();
    EncoderHack::appendBytes("abc", Mode::BYTE, bits, EncoderHack::DEFAULT_BYTE_MODE_ENCODING);
    assertEquals(" .XX....X .XX...X. .XX...XX", bits.toString());
    // Anything can be encoded in QRCode.MODE_8BIT_BYTE.
    EncoderHack::appendBytes("\0", Mode::BYTE, bits, EncoderHack::DEFAULT_BYTE_MODE_ENCODING);
    // Should use appendKanjiBytes.
    // 0x93, 0x5f
    //    bits = new BitArray();
    //    Encoder.appendBytes(shiftJISString(new byte[] {(byte)0x93,0x5f}), Mode.KANJI, bits, Encoder.DEFAULT_BYTE_MODE_ENCODING);
    //    assertEquals(" .XX.XX.. XXXXX", bits.toString());
}

void EncoderTests::testTerminateBits()
{
    BitArray v;
    EncoderHack::terminateBits(0, v);
    assertEquals("", v.toString());
    v = BitArray();
    EncoderHack::terminateBits(1, v);
    assertEquals(" ........", v.toString());
    v = BitArray();
    v.appendBits(0, 3);  // Append 000
    EncoderHack::terminateBits(1, v);
    assertEquals(" ........", v.toString());
    v = BitArray();
    v.appendBits(0, 5);  // Append 00000
    EncoderHack::terminateBits(1, v);
    assertEquals(" ........", v.toString());
    v = BitArray();
    v.appendBits(0, 8);  // Append 00000000
    EncoderHack::terminateBits(1, v);
    assertEquals(" ........", v.toString());
    v = BitArray();
    EncoderHack::terminateBits(2, v);
    assertEquals(" ........ XXX.XX..", v.toString());
    v = BitArray();
    v.appendBits(0, 1);  // Append 0
    EncoderHack::terminateBits(3, v);
    assertEquals(" ........ XXX.XX.. ...X...X", v.toString());
}

void EncoderTests::testGetNumDataBytesAndNumECBytesForBlockID()
{
    std::vector<int> numDataBytes;
    std::vector<int> numEcBytes;
    // Version 1-H.
    EncoderHack::getNumDataBytesAndNumECBytesForBlockID(26, 9, 1, 0, numDataBytes, numEcBytes);
    assertEquals(9, numDataBytes[0]);
    assertEquals(17, numEcBytes[0]);

    numDataBytes.clear();
    numEcBytes.clear();

    // Version 3-H.  2 blocks.
    EncoderHack::getNumDataBytesAndNumECBytesForBlockID(70, 26, 2, 0, numDataBytes, numEcBytes);
    assertEquals(13, numDataBytes[0]);
    assertEquals(22, numEcBytes[0]);
    EncoderHack::getNumDataBytesAndNumECBytesForBlockID(70, 26, 2, 1, numDataBytes, numEcBytes);
    assertEquals(13, numDataBytes[0]);
    assertEquals(22, numEcBytes[0]);

    // Version 7-H. (4 + 1) blocks.
    EncoderHack::getNumDataBytesAndNumECBytesForBlockID(196, 66, 5, 0, numDataBytes, numEcBytes);
    assertEquals(13, numDataBytes[0]);
    assertEquals(26, numEcBytes[0]);
    EncoderHack::getNumDataBytesAndNumECBytesForBlockID(196, 66, 5, 4, numDataBytes, numEcBytes);
    assertEquals(14, numDataBytes[0]);
    assertEquals(26, numEcBytes[0]);

    // Version 40-H. (20 + 61) blocks.
    EncoderHack::getNumDataBytesAndNumECBytesForBlockID(3706, 1276, 81, 0, numDataBytes, numEcBytes);
    assertEquals(15, numDataBytes[0]);
    assertEquals(30, numEcBytes[0]);
    EncoderHack::getNumDataBytesAndNumECBytesForBlockID(3706, 1276, 81, 20, numDataBytes, numEcBytes);
    assertEquals(16, numDataBytes[0]);
    assertEquals(30, numEcBytes[0]);
    EncoderHack::getNumDataBytesAndNumECBytesForBlockID(3706, 1276, 81, 80, numDataBytes, numEcBytes);
    assertEquals(16, numDataBytes[0]);
    assertEquals(30, numEcBytes[0]);
}

void EncoderTests::testInterleaveWithECBytes()
{
    const byte arr[] = {32, 65, 205, 69, 41, 220, 46, 128, 236};
    std::vector<zxing::byte> dataBytes (arr, arr + getArrayLength(arr));

    BitArray in;
    for (byte dataByte: dataBytes) {
        in.appendBits(dataByte, 8);
    }

    BitArray* out = Encoder::interleaveWithECBytes(in, 26, 9, 1);
    const byte expected[] = {
        // Data bytes.
        32, 65, 205, 69, 41, 220, 46, 128, 236,
        // Error correction bytes.
        42, 159, 74, 221, 244, 169, 239, 150, 138, 70,
        237, 85, 224, 96, 74, 219, 61,
    };
    int expectedLength = getArrayLength(expected);
    assertEquals(expectedLength, out->getSizeInBytes());
    std::vector<zxing::byte> outArray;
    out->toBytes(0, outArray, 0, expectedLength);

    // Can't use Arrays.equals(), because outArray may be longer than out.sizeInBytes()
    for (int x = 0; x < expectedLength; x++) {
        assertEquals(expected[x], outArray[x]);  //throughs here => will be continued after all the tests
    }

    // Numbers are from http://www.swetake.com/qr/qr8.html
    const byte arr2[] = {
        67, 70, 22, 38, 54, 70, 86, 102, 118, 134, 150, 166, 182,
        198, 214, 230, 247, 7, 23, 39, 55, 71, 87, 103, 119, 135,
        151, 166, 22, 38, 54, 70, 86, 102, 118, 134, 150, 166,
        182, 198, 214, 230, 247, 7, 23, 39, 55, 71, 87, 103, 119,
        135, 151, 160, 236, 17, 236, 17, 236, 17, 236,
        17
    };
    dataBytes = std::vector<zxing::byte>(arr2, arr2 + getArrayLength(arr2));

    in = BitArray();
    foreach (byte dataByte, dataBytes) {
        in.appendBits(dataByte, 8);
    }

    out = Encoder::interleaveWithECBytes(in, 134, 62, 4);
    const byte expected2[] = {
        // Data bytes.
        67, 230, 54, 55, 70, 247, 70, 71, 22, 7, 86, 87, 38, 23, 102, 103, 54, 39,
        118, 119, 70, 55, 134, 135, 86, 71, 150, 151, 102, 87, 166,
        160, 118, 103, 182, 236, 134, 119, 198, 17, 150,
        135, 214, 236, 166, 151, 230, 17, 182,
        166, 247, 236, 198, 22, 7, 17, 214, 38, 23, 236, 39,
        17,
        // Error correction bytes.
        175, 155, 245, 236, 80, 146, 56, 74, 155, 165,
        133, 142, 64, 183, 132, 13, 178, 54, 132, 108, 45,
        113, 53, 50, 214, 98, 193, 152, 233, 147, 50, 71, 65,
        190, 82, 51, 209, 199, 171, 54, 12, 112, 57, 113, 155, 117,
        211, 164, 117, 30, 158, 225, 31, 190, 242, 38,
        140, 61, 179, 154, 214, 138, 147, 87, 27, 96, 77, 47,
        187, 49, 156, 214,
    };
    expectedLength = getArrayLength(expected2);
    assertEquals(expectedLength, out->getSizeInBytes());
    outArray.clear();
    out->toBytes(0, outArray, 0, expectedLength);
    for (int x = 0; x < expectedLength; x++) {
        assertEquals(expected2[x], outArray[x]);
    }
}

void EncoderTests::testAppendNumericBytes()
{
    // 1 = 01 = 0001 in 4 bits.
    BitArray bits;
    Encoder::appendNumericBytes("1", bits);
    assertEquals(" ...X" , bits.toString());
    // 12 = 0xc = 0001100 in 7 bits.
    bits = BitArray();
    Encoder::appendNumericBytes("12", bits);
    assertEquals(" ...XX.." , bits.toString());
    // 123 = 0x7b = 0001111011 in 10 bits.
    bits = BitArray();
    Encoder::appendNumericBytes("123", bits);
    assertEquals(" ...XXXX. XX" , bits.toString());
    // 1234 = "123" + "4" = 0001111011 + 0100
    bits = BitArray();
    Encoder::appendNumericBytes("1234", bits);
    assertEquals(" ...XXXX. XX.X.." , bits.toString());
    // Empty.
    bits = BitArray();
    Encoder::appendNumericBytes("", bits);
    assertEquals("" , bits.toString());
}

void EncoderTests::testAppendAlphanumericBytes()
{
    // A = 10 = 0xa = 001010 in 6 bits
    BitArray bits;
    Encoder::appendAlphanumericBytes("A", bits);
    assertEquals(" ..X.X." , bits.toString());
    // AB = 10 * 45 + 11 = 461 = 0x1cd = 00111001101 in 11 bits
    bits = BitArray();
    Encoder::appendAlphanumericBytes("AB", bits);
    assertEquals(" ..XXX..X X.X", bits.toString());
    // ABC = "AB" + "C" = 00111001101 + 001100
    bits = BitArray();
    Encoder::appendAlphanumericBytes("ABC", bits);
    assertEquals(" ..XXX..X X.X..XX. ." , bits.toString());
    // Empty.
    bits = BitArray();
    Encoder::appendAlphanumericBytes("", bits);
    assertEquals("" , bits.toString());
    // Invalid data.
    bits = BitArray();

    ASSERT_THROWS( Encoder::appendAlphanumericBytes("abc", bits); )
}

void EncoderTests::testAppend8BitBytes()
{
    BitArray bits;
    Encoder::append8BitBytes("abc", bits, Encoder::DEFAULT_BYTE_MODE_ENCODING);
    assertEquals(" .XX....X .XX...X. .XX...XX", bits.toString());
    // Empty.
    bits = BitArray();
    Encoder::append8BitBytes("", bits, Encoder::DEFAULT_BYTE_MODE_ENCODING);
    assertEquals("", bits.toString());
}

void EncoderTests::testGenerateECBytes()
{
    std::vector<zxing::byte> dataBytes = {32, 65, 205, 69, 41, 220, 46, 128, 236};

    ArrayRef<zxing::byte> ecBytes = Encoder::generateECBytes(dataBytes, 17);
    byte expected[] = {
        42, 159, 74, 221, 244, 169, 239, 150, 138, 70, 237, 85, 224, 96, 74, 219, 61
    };
    assertEquals( getArrayLength(expected), ecBytes->size());
    for (int x = 0; x < getArrayLength(expected); x++) {
        assertEquals(expected[x], ecBytes[x]);
    }

    /////////////////////////////////////////////////////////////////////////////

    dataBytes =  {67, 70, 22, 38, 54, 70, 86, 102, 118,
                  134, 150, 166, 182, 198, 214};
    ecBytes = Encoder::generateECBytes(dataBytes, 18);
    byte expected2[] = {
        175, 80, 155, 64, 178, 45, 214, 233, 65, 209, 12, 155, 117, 31, 140, 214, 27, 187
    };

    assertEquals(getArrayLength(expected2), ecBytes->size());
    for (int x = 0; x < getArrayLength(expected2); x++) {
        assertEquals(expected2[x], ecBytes[x] );
    }

    /////////////////////////////////////////////////////////////////////////////

    // High-order zero coefficient case.
    dataBytes = {32, 49, 205, 69, 42, 20, 0, 236, 17};
    ecBytes = Encoder::generateECBytes(dataBytes, 17);
    byte expected3[] = {
        0, 3, 130, 179, 194, 0, 55, 211, 110, 79, 98, 72, 170, 96, 211, 137, 213
    };
    assertEquals(getArrayLength(expected3), ecBytes->size());
    for (int x = 0; x < getArrayLength(expected3); x++) {
        assertEquals(expected3[x], ecBytes[x]);
    }
}




}
}
}


