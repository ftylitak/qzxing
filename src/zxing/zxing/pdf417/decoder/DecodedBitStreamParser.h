// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
#ifndef ZXING_DECODED_BIT_STREAM_PARSER_PD_H
#define ZXING_DECODED_BIT_STREAM_PARSER_PD_H

/*
 * Copyright 2010 ZXing authors All rights reserved.
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

#include <bigint/BigInteger.hh>
#include <zxing/common/Str.h>
#include <zxing/common/DecoderResult.h>

namespace zxing {
namespace pdf417 {

class DecodedBitStreamParser {
 protected:
  enum Mode {
    ALPHA,
    LOWER,
    MIXED,
    PUNCT,
    ALPHA_SHIFT,
    PUNCT_SHIFT
  };

 private:
  
  static const int TEXT_COMPACTION_MODE_LATCH;
  static const int BYTE_COMPACTION_MODE_LATCH;
  static const int NUMERIC_COMPACTION_MODE_LATCH;
  static const int BYTE_COMPACTION_MODE_LATCH_6;
  static const int BEGIN_MACRO_PDF417_CONTROL_BLOCK;
  static const int BEGIN_MACRO_PDF417_OPTIONAL_FIELD;
  static const int MACRO_PDF417_TERMINATOR;
  static const int MODE_SHIFT_TO_BYTE_COMPACTION_MODE;
  static const int MAX_NUMERIC_CODEWORDS;

  static const int PL;
  static const int LL;
  static const int AS;
  static const int ML;
  static const int AL;
  static const int PS;
  static const int PAL;
  static const int EXP900_SIZE;

  static const char PUNCT_CHARS[];
  static const char MIXED_CHARS[];
 
  static QSharedPointer<std::vector<BigInteger>> EXP900;
  static QSharedPointer<std::vector<BigInteger>> initEXP900();
  
  static int textCompaction(QSharedPointer<std::vector<int>> codewords, int codeIndex, QSharedPointer<String> result);
  static void decodeTextCompaction(QSharedPointer<std::vector<int>> textCompactionData,
                                   QSharedPointer<std::vector<int>> byteCompactionData,
                                   int length,
                                   QSharedPointer<String> result);
  static int byteCompaction(int mode, QSharedPointer<std::vector<int>> codewords, int codeIndex, QSharedPointer<String> result);
  static int numericCompaction(QSharedPointer<std::vector<int>> codewords, int codeIndex, QSharedPointer<String> result);
  static QSharedPointer<String> decodeBase900toBase10(QSharedPointer<std::vector<int>> codewords, int count);

 public:
  DecodedBitStreamParser();
  static QSharedPointer<DecoderResult> decode(QSharedPointer<std::vector<int>> codewords);
};

} /* namespace pdf417 */
} /* namespace zxing */

#endif // ZXING_DECODED_BIT_STREAM_PARSER_PD_H
