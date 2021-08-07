// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
#ifndef ZXING_DETECTOR_H
#define ZXING_DETECTOR_H

/*
 *  Detector.h
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

#include <QSharedPointer>
#include <zxing/common/DetectorResult.h>
#include <zxing/common/BitMatrix.h>
#include <zxing/qrcode/detector/AlignmentPattern.h>
#include <zxing/common/PerspectiveTransform.h>
#include <zxing/ResultPointCallback.h>
#include <zxing/qrcode/detector/FinderPatternInfo.h>

namespace zxing {

class DecodeHints;

namespace qrcode {

class Detector  {
private:
  QSharedPointer<BitMatrix> image_;
  QSharedPointer<ResultPointCallback> callback_;

protected:
  QSharedPointer<BitMatrix> getImage() const;
  QSharedPointer<ResultPointCallback> getResultPointCallback() const;

  static QSharedPointer<BitMatrix> sampleGrid(QSharedPointer<BitMatrix> image, int dimension, QSharedPointer<PerspectiveTransform>);
  static int computeDimension(QSharedPointer<ResultPoint> topLeft, QSharedPointer<ResultPoint> topRight, QSharedPointer<ResultPoint> bottomLeft,
                              float moduleSize);
  float calculateModuleSize(QSharedPointer<ResultPoint> topLeft, QSharedPointer<ResultPoint> topRight, QSharedPointer<ResultPoint> bottomLeft);
  float calculateModuleSizeOneWay(QSharedPointer<ResultPoint> pattern, QSharedPointer<ResultPoint> otherPattern);
  float sizeOfBlackWhiteBlackRunBothWays(int fromX, int fromY, int toX, int toY);
  float sizeOfBlackWhiteBlackRun(int fromX, int fromY, int toX, int toY);
  QSharedPointer<AlignmentPattern> findAlignmentInRegion(float overallEstModuleSize, int estAlignmentX, int estAlignmentY,
      float allowanceFactor);
  QSharedPointer<DetectorResult> processFinderPatternInfo(QSharedPointer<FinderPatternInfo> info);
public:
  virtual QSharedPointer<PerspectiveTransform> createTransform(QSharedPointer<ResultPoint> topLeft, QSharedPointer<ResultPoint> topRight, QSharedPointer <
      ResultPoint > bottomLeft, QSharedPointer<ResultPoint> alignmentPattern, int dimension);

  Detector(QSharedPointer<BitMatrix> image);
  QSharedPointer<DetectorResult> detect(DecodeHints const& hints);


};
}
}

#endif // ZXING_DETECTOR_H
