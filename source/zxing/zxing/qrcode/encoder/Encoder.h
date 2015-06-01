//#ifndef ENCODER_H
//#define ENCODER_H
////package com.google.zxing.qrcode.encoder;

////import com.google.zxing.EncodeHintType;
////import com.google.zxing.WriterException;
////import com.google.zxing.common.BitArray;
////import com.google.zxing.common.CharacterSetECI;
////import com.google.zxing.common.reedsolomon.GenericGF;
////import com.google.zxing.common.reedsolomon.ReedSolomonEncoder;
////import com.google.zxing.qrcode.decoder.ErrorCorrectionLevel;
////import com.google.zxing.qrcode.decoder.Mode;
////import com.google.zxing.qrcode.decoder.Version;

////import java.io.UnsupportedEncodingException;
////import java.util.ArrayList;
////import java.util.Collection;
////import java.util.Map;

//#include <string>
//#include <vector>
//#include <zxing/common/CharacterSetECI.h>
//#include <zxing/qrcode/ErrorCorrectionLevel.h>
//#include <zxing/qrcode/encoder/QRCode.h>

//namespace zxing {
//namespace qrcode {

//class Encoder {

//private:
//    static const int ALPHANUMERIC_TABLE[];
//    static const std::string DEFAULT_BYTE_MODE_ENCODING;

//    Encoder() {}

//  /**
//   * The mask penalty calculation is complicated.  See Table 21 of JISX0510:2004 (p.45) for details.
//   * Basically it applies four rules and summate all penalties.
//   */
//  static int calculateMaskPenalty(ByteMatrix matrix);

//  /**
//   *  Encode "bytes" with the error correction level "ecLevel". The encoding mode will be chosen
//   * internally by chooseMode(). On success, store the result in "qrCode".
//   *
//   * We recommend you to use QRCode.EC_LEVEL_L (the lowest level) for
//   * "getECLevel" since our primary use is to show QR code on desktop screens. We don't need very
//   * strong error correction for this purpose.
//   *
//   * Note that there is no way to encode bytes in MODE_KANJI. We might want to add EncodeWithMode()
//   * with which clients can specify the encoding mode. For now, we don't need the functionality.
//   */
//public:
//  static QRCode encode(std::string content, ErrorCorrectionLevel ecLevel);

//  static QRCode encode(String content, ErrorCorrectionLevel ecLevel/*,
//                              Map<EncodeHintType,?> hints*/);

//  /**
//   * @return the code point of the table used in alphanumeric mode or
//   *  -1 if there is no corresponding code in the table.
//   */
//  static int getAlphanumericCode(int code);

//  static Mode chooseMode(String content);

//  /**
//   * Choose the best mode by examining the content. Note that 'encoding' is used as a hint;
//   * if it is Shift_JIS, and the input is only double-byte Kanji, then we return {@link Mode#KANJI}.
//   */
//private:
//  static Mode chooseMode(std::string content, std::string encoding);

//  static boolean isOnlyDoubleByteKanji(std::string content);

//  static int chooseMaskPattern(BitArray bits,
//                                       ErrorCorrectionLevel ecLevel,
//                                       Version version,
//                                       ByteMatrix matrix);

//  static Version chooseVersion(int numInputBits, ErrorCorrectionLevel ecLevel) ;

//  /**
//   * Terminate bits as described in 8.4.8 and 8.4.9 of JISX0510:2004 (p.24).
//   */
//protected:
//  static void terminateBits(int numDataBytes, BitArray bits);

//  /**
//   * Get number of data bytes and number of error correction bytes for block id "blockID". Store
//   * the result in "numDataBytesInBlock", and "numECBytesInBlock". See table 12 in 8.5.1 of
//   * JISX0510:2004 (p.30)
//   */
//  static void getNumDataBytesAndNumECBytesForBlockID(int numTotalBytes,
//                                                     int numDataBytes,
//                                                     int numRSBlocks,
//                                                     int blockID,
//                                                     int numDataBytesInBlock[],
//                                                     int numECBytesInBlock[]);

//  /**
//   * Interleave "bits" with corresponding error correction bytes. On success, store the result in
//   * "result". The interleave rule is complicated. See 8.6 of JISX0510:2004 (p.37) for details.
//   */
//  static BitArray interleaveWithECBytes(BitArray bits,
//                                        int numTotalBytes,
//                                        int numDataBytes,
//                                        int numRSBlocks);

//  static std::vector<char> generateECBytes(const std::vector<char>& dataBytes[], int numEcBytesInBlock);

//  /**
//   * Append mode info. On success, store the result in "bits".
//   */
//  static void appendModeInfo(Mode mode, BitArray bits);


//  /**
//   * Append length info. On success, store the result in "bits".
//   */
//  static void appendLengthInfo(int numLetters, Version version, Mode mode, BitArray bits);

//  /**
//   * Append "bytes" in "mode" mode (encoding) into "bits". On success, store the result in "bits".
//   */
//  static void appendBytes(std::string content,
//                          Mode mode,
//                          BitArray bits,
//                          std::string encoding);

//  static void appendNumericBytes( const std::vector<char>& content, BitArray bits);

//  static void appendAlphanumericBytes(const std::vector<char>& content, BitArray bits);

//  static void append8BitBytes(std::string content, BitArray bits, std::string encoding);

//  static void appendKanjiBytes(std::string content, BitArray bits);

//private:
//  static void appendECI(zxing::common::CharacterSetECI eci, BitArray bits);

//}

//}
//}

//#endif // ENCODER_H
