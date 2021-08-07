// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-

#ifndef ZXING_DECODED_BIT_STREAM_PARSER_H
#define ZXING_DECODED_BIT_STREAM_PARSER_H

/*
 *  DecodedBitStreamParser.h
 *  zxing
 *
 *  Copyright 2010 ZXing authors All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>
#include <sstream>
#include <map>
#include <zxing/qrcode/decoder/Mode.h>
#include <zxing/common/BitSource.h>
#include <QSharedPointer>
#include <zxing/common/DecoderResult.h>
#include <zxing/common/CharacterSetECI.h>
#include <zxing/DecodeHints.h>

namespace zxing {
namespace qrcode {

class DecodedBitStreamParser {
public:
  typedef std::map<DecodeHintType, std::string> Hashtable;

private:
  static char const ALPHANUMERIC_CHARS[];
  static char toAlphaNumericChar(size_t value);

  static void decodeHanziSegment(QSharedPointer<BitSource> bits, std::string &result, int count);
  static void decodeKanjiSegment(QSharedPointer<BitSource> bits, std::string &result, int count);
  static void decodeByteSegment(QSharedPointer<BitSource> bits, std::string &result, int count);
  static std::string decodeByteSegment(QSharedPointer<BitSource> bits_,
                                std::string& result,
                                int count,
                                common::CharacterSetECI const *currentCharacterSetECI,
                                QSharedPointer<std::vector<QSharedPointer<std::vector<zxing::byte>> >> byteSegments,
                                Hashtable const& hints);
  static void decodeAlphanumericSegment(QSharedPointer<BitSource> bits, std::string &result, int count, bool fc1InEffect);
  static void decodeNumericSegment(QSharedPointer<BitSource> bits, std::string &result, int count);

  static void append(std::string &ost, const zxing::byte *bufIn, size_t nIn, const char *src);
  static void append(std::string &ost, std::string const& in, const char *src);

public:
  static QSharedPointer<DecoderResult> decode(QSharedPointer<std::vector<zxing::byte>> bytes,
                                   QSharedPointer<Version>version,
                                   ErrorCorrectionLevel const& ecLevel,
                                   Hashtable const& hints);
};

}
}

#endif // ZXING_DECODED_BIT_STREAM_PARSER_H
