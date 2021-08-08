#ifndef ZXING_MULTI_FORMAT_READER_H
#define ZXING_MULTI_FORMAT_READER_H

/*
 *  MultiFormatBarcodeReader.h
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

 
#include <zxing/Reader.h>
#include <zxing/common/BitArray.h>
#include <zxing/Result.h>
#include <zxing/DecodeHints.h>

namespace zxing {
  class MultiFormatReader : public Reader {
  private:
    QSharedPointer<Result> decodeInternal(QSharedPointer<BinaryBitmap> image);
  
    std::vector<QSharedPointer<Reader> > readers_;
    DecodeHints hints_;

  public:
    MultiFormatReader();
    
    QSharedPointer<Result> decode(QSharedPointer<BinaryBitmap> image);
    QSharedPointer<Result> decode(QSharedPointer<BinaryBitmap> image, DecodeHints hints);
    QSharedPointer<Result> decodeWithState(QSharedPointer<BinaryBitmap> image);
    void setHints(DecodeHints hints);
    void enableReaders(DecodeHints hints, bool allowAll = false);
    ~MultiFormatReader();
  };
}

#endif // ZXING_MULTI_FORMAT_READER_H

