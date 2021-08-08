// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  Decoder.h
 *  zxing
 *
 *  Created by Lukas Stabe on 08/02/2012.
 *  Copyright 2012 ZXing authors All rights reserved.
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

#ifndef ZXING_AZTEC_DECODER_DECODER_H
#define ZXING_AZTEC_DECODER_DECODER_H

#include <zxing/common/BitMatrix.h>
#include <zxing/common/Str.h>
#include <zxing/aztec/AztecDetectorResult.h>

namespace zxing {

class DecoderResult;
        
namespace aztec {

class Decoder  {
 private:
  enum Table {
    UPPER,
    LOWER,
    MIXED,
    DIGIT,
    PUNCT,
    BINARY
  };
            
  static Table getTable(char t);
  static const char* getCharacter(Table table, int code);
            
  int numCodewords_;
  int codewordSize_;
  QSharedPointer<AztecDetectorResult> ddata_;
  int invertedBitCount_;
            
  QSharedPointer<String> getEncodedData(QSharedPointer<BitArray> correctedBits);
  QSharedPointer<BitArray> correctBits(QSharedPointer<BitArray> rawbits);
  QSharedPointer<BitArray> extractBits(QSharedPointer<BitMatrix> matrix);
  static QSharedPointer<BitMatrix> removeDashedLines(QSharedPointer<BitMatrix> matrix);
  static int readCode(QSharedPointer<BitArray> rawbits, int startIndex, int length);
            
            
 public:
  Decoder();
  QSharedPointer<DecoderResult> decode(QSharedPointer<AztecDetectorResult> detectorResult);
};
        
}
}

#endif // ZXING_AZTEC_DECODER_DECODER_H
