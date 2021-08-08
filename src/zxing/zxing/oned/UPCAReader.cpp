// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  UPCAReader.cpp
 *  ZXing
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

#include "UPCAReader.h"
#include <zxing/ReaderException.h>

using zxing::oned::UPCAReader;

using zxing::Result;

// VC++
using zxing::BitArray;
using zxing::BinaryBitmap;
using zxing::DecodeHints;

UPCAReader::UPCAReader() : ean13Reader() {}

QSharedPointer<Result> UPCAReader::decodeRow(int rowNumber, QSharedPointer<BitArray> row, zxing::DecodeHints hints) {
  return maybeReturnResult(ean13Reader.decodeRow(rowNumber, row, hints));
}

QSharedPointer<Result> UPCAReader::decodeRow(int rowNumber,
                                  QSharedPointer<BitArray> row,
                                  Range const& startGuardRange) {
  return maybeReturnResult(ean13Reader.decodeRow(rowNumber, row, startGuardRange));
}

QSharedPointer<Result> UPCAReader::decode(QSharedPointer<BinaryBitmap> image, DecodeHints hints) {
  return maybeReturnResult(ean13Reader.decode(image, hints));
}

int UPCAReader::decodeMiddle(QSharedPointer<BitArray> row,
                             Range const& startRange,
                             std::string& resultString) {
  return ean13Reader.decodeMiddle(row, startRange, resultString);
}

QSharedPointer<Result> UPCAReader::maybeReturnResult(QSharedPointer<Result> result) {
  if (result.isNull()) {
    return result;
  }
  const std::string& text = (result->getText())->getText();
  if (text[0] == '0') {
    QSharedPointer<String> resultString(new String(text.substr(1)));
    QSharedPointer<Result> res(new Result(resultString, result->getRawBytes(), result->getResultPoints(),
                               BarcodeFormat::UPC_A));
    return res;
  }
  return QSharedPointer<Result>();
}

zxing::BarcodeFormat UPCAReader::getBarcodeFormat(){
  return BarcodeFormat::UPC_A;
}
