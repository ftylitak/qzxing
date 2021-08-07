// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
#ifndef ZXING_GLOBALHISTOGRAMBINARIZER_H
#define ZXING_GLOBALHISTOGRAMBINARIZER_H
/*
 *  GlobalHistogramBinarizer.h
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

#include <zxing/Binarizer.h>
#include <zxing/common/BitArray.h>
#include <zxing/common/BitMatrix.h>

namespace zxing {
	
class GlobalHistogramBinarizer : public Binarizer {
private:
  QSharedPointer<std::vector<zxing::byte>> luminances;
  QSharedPointer<std::vector<int>> buckets;
public:
  GlobalHistogramBinarizer(QSharedPointer<LuminanceSource> source);
  virtual ~GlobalHistogramBinarizer();
		
  virtual QSharedPointer<BitArray> getBlackRow(int y, QSharedPointer<BitArray> row);
  virtual QSharedPointer<BitMatrix> getBlackMatrix();
  static int estimateBlackPoint(QSharedPointer<std::vector<int>> const& buckets);
  QSharedPointer<Binarizer> createBinarizer(QSharedPointer<LuminanceSource> source);
private:
  void initArrays(int luminanceSize);
};

}
	
#endif /* ZXING_GLOBALHISTOGRAMBINARIZER_H */
