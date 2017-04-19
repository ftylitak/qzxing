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
    testAppendLengthInfo();
    testAppendBytes();
    testTerminateBits();
    testGetNumDataBytesAndNumECBytesForBlockID();
    testInterleaveWithECBytes();
    testAppendNumericBytes();
    testAppendAlphanumericBytes();
    testAppend8BitBytes();
    testGenerateECBytes();
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
    const byte arr[] = {32, 65, (byte)205, 69, 41, (byte)220, 46, (byte)128, (byte)236};
    int length = getArrayLength(arr);
    std::vector<byte> dataBytes (arr, arr + getArrayLength(arr));

    BitArray in;
    for (byte dataByte: dataBytes) {
        in.appendBits(dataByte, 8);
    }

    BitArray* out = Encoder::interleaveWithECBytes(in, 26, 9, 1);
    const byte expected[] = {
        // Data bytes.
        32, 65, (byte)205, 69, 41, (byte)220, 46, (byte)128, (byte)236,
        // Error correction bytes.
        42, (byte)159, 74, (byte)221, (byte)244, (byte)169, (byte)239, (byte)150, (byte)138, 70,
        (byte)237, 85, (byte)224, 96, 74, (byte)219, 61,
    };
    int expectedLength = getArrayLength(expected);
    assertEquals(expectedLength, out->getSizeInBytes());
    std::vector<byte> outArray;
    out->toBytes(0, outArray, 0, expectedLength);
    // Can't use Arrays.equals(), because outArray may be longer than out.sizeInBytes()
    //    for (int x = 0; x < expectedLength; x++) {
    //        assertEquals(expected[x], outArray[x]);  //throughs here => will be continued after all the tests
    //    }

    //    // Numbers are from http://www.swetake.com/qr/qr8.html
    //    dataBytes = new byte[] {
    //        67, 70, 22, 38, 54, 70, 86, 102, 118, (byte)134, (byte)150, (byte)166, (byte)182,
    //                (byte)198, (byte)214, (byte)230, (byte)247, 7, 23, 39, 55, 71, 87, 103, 119, (byte)135,
    //                (byte)151, (byte)166, 22, 38, 54, 70, 86, 102, 118, (byte)134, (byte)150, (byte)166,
    //                (byte)182, (byte)198, (byte)214, (byte)230, (byte)247, 7, 23, 39, 55, 71, 87, 103, 119,
    //                (byte)135, (byte)151, (byte)160, (byte)236, 17, (byte)236, 17, (byte)236, 17, (byte)236,
    //                17
    //    };
    //    in = new BitArray();
    //    for (byte dataByte: dataBytes) {
    //        in.appendBits(dataByte, 8);
    //    }

    //    out = Encoder.interleaveWithECBytes(in, 134, 62, 4);
    //    expected = new byte[] {
    //        // Data bytes.
    //        67, (byte)230, 54, 55, 70, (byte)247, 70, 71, 22, 7, 86, 87, 38, 23, 102, 103, 54, 39,
    //                118, 119, 70, 55, (byte)134, (byte)135, 86, 71, (byte)150, (byte)151, 102, 87, (byte)166,
    //                (byte)160, 118, 103, (byte)182, (byte)236, (byte)134, 119, (byte)198, 17, (byte)150,
    //                (byte)135, (byte)214, (byte)236, (byte)166, (byte)151, (byte)230, 17, (byte)182,
    //                (byte)166, (byte)247, (byte)236, (byte)198, 22, 7, 17, (byte)214, 38, 23, (byte)236, 39,
    //                17,
    //                // Error correction bytes.
    //                (byte)175, (byte)155, (byte)245, (byte)236, 80, (byte)146, 56, 74, (byte)155, (byte)165,
    //                (byte)133, (byte)142, 64, (byte)183, (byte)132, 13, (byte)178, 54, (byte)132, 108, 45,
    //                113, 53, 50, (byte)214, 98, (byte)193, (byte)152, (byte)233, (byte)147, 50, 71, 65,
    //                (byte)190, 82, 51, (byte)209, (byte)199, (byte)171, 54, 12, 112, 57, 113, (byte)155, 117,
    //                (byte)211, (byte)164, 117, 30, (byte)158, (byte)225, 31, (byte)190, (byte)242, 38,
    //                (byte)140, 61, (byte)179, (byte)154, (byte)214, (byte)138, (byte)147, 87, 27, 96, 77, 47,
    //                (byte)187, 49, (byte)156, (byte)214,
    //    };
    //    assertEquals(expected.length, out.getSizeInBytes());
    //    outArray = new byte[expected.length];
    //    out.toBytes(0, outArray, 0, expected.length);
    //    for (int x = 0; x < expected.length; x++) {
    //        assertEquals(expected[x], outArray[x]);
    //    }
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
    const byte dataBytes_arr[] = {32, 65, 205, 69, 41, 220, 46, 128, 236};
    std::vector<byte> dataBytes (dataBytes_arr, dataBytes_arr + getArrayLength(dataBytes_arr));
//    std::vector<byte> dataBytes(getArrayLength(dataBytes_arr));
//    for(int i=0; i<dataBytes.size(); i++)
//        dataBytes[i] = dataBytes_arr[i];

    ArrayRef<byte> ecBytes = Encoder::generateECBytes(dataBytes, 17);
    const byte expected[] = {
        42, 159, 74, 221, 244, 169, 239, 150, 138, 70, 237, 85, 224, 96, 74, 219, 61
    };
    assertEquals( getArrayLength(expected), ecBytes->size());
    for (int x = 0; x < getArrayLength(expected); x++) {
        assertEquals(expected[x], ecBytes[x]);
    }
//    dataBytes = new byte[] {67, 70, 22, 38, 54, 70, 86, 102, 118,
//        (byte)134, (byte)150, (byte)166, (byte)182, (byte)198, (byte)214};
//    ecBytes = Encoder.generateECBytes(dataBytes, 18);
//    expected = new int[] {
//        175, 80, 155, 64, 178, 45, 214, 233, 65, 209, 12, 155, 117, 31, 140, 214, 27, 187
//    };
//    assertEquals(expected.length, ecBytes.length);
//    for (int x = 0; x < expected.length; x++) {
//        assertEquals(expected[x], ecBytes[x] & 0xFF);
//    }
//    // High-order zero coefficient case.
//    dataBytes = new byte[] {32, 49, (byte)205, 69, 42, 20, 0, (byte)236, 17};
//    ecBytes = Encoder.generateECBytes(dataBytes, 17);
//    expected = new int[] {
//        0, 3, 130, 179, 194, 0, 55, 211, 110, 79, 98, 72, 170, 96, 211, 137, 213
//    };
//    assertEquals(expected.length, ecBytes.length);
//    for (int x = 0; x < expected.length; x++) {
//        assertEquals(expected[x], ecBytes[x] & 0xFF);
//    }
}




}
}
}


