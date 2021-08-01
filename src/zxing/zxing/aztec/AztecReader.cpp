// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  AztecReader.cpp
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

#include <zxing/aztec/AztecReader.h>
#include <zxing/aztec/detector/Detector.h>
#include <zxing/common/DecoderResult.h>
#include <iostream>


using zxing::Result;
using zxing::aztec::AztecReader;

// VC++
using zxing::BinaryBitmap;
using zxing::DecodeHints;

AztecReader::AztecReader() : decoder_()
{
  // nothing
}

QSharedPointer<Result> AztecReader::decode(QSharedPointer<zxing::BinaryBitmap> image)
{
  Detector detector(image->getBlackMatrix());

  QSharedPointer<AztecDetectorResult> detectorResult(detector.detect());

  QSharedPointer<std::vector<QSharedPointer<ResultPoint>>> points(detectorResult->getPoints());

  QSharedPointer<DecoderResult> decoderResult(decoder_.decode(detectorResult));

  QSharedPointer<Result> result(new Result(decoderResult->getText(),
                                decoderResult->getRawBytes(),
                                points,
                                BarcodeFormat::AZTEC));

  return result;
}

QSharedPointer<Result> AztecReader::decode(QSharedPointer<BinaryBitmap> image, DecodeHints)
{
  //cout << "decoding with hints not supported for aztec" << "\n" << flush;
  return this->decode(image);
}

AztecReader::~AztecReader()
{
  // nothing
}

zxing::aztec::Decoder &AztecReader::getDecoder()
{
  return decoder_;
}
