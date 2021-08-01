// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  Detector.h
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

#ifndef ZXING_AZTEC_DETECTOR_DETECTOR_H
#define ZXING_AZTEC_DETECTOR_DETECTOR_H

#include <vector>

#include <zxing/common/BitArray.h>
#include <zxing/ResultPoint.h>
#include <zxing/common/BitMatrix.h>
#include <zxing/DecodeHints.h>
#include <zxing/aztec/AztecDetectorResult.h>

namespace zxing {
namespace aztec {

class Point  {
 private:
  const int x;
  const int y;
            
 public:
  QSharedPointer<ResultPoint> toResultPoint() { 
    return QSharedPointer<ResultPoint>(new ResultPoint(float(x), float(y)));
  }
            
  Point(int ax, int ay) : x(ax), y(ay) {}

  int getX() const { return x; }
  int getY() const { return y; }
};
        
class Detector  {
            
 private:
  QSharedPointer<BitMatrix> image_;
            
  bool compact_;
  int nbLayers_;
  int nbDataBlocks_;
  int nbCenterLayers_;
  int shift_;
            
  void extractParameters(std::vector<QSharedPointer<Point> > bullEyeCornerPoints);
  QSharedPointer<std::vector<QSharedPointer<ResultPoint>> > getMatrixCornerPoints(std::vector<QSharedPointer<Point> > bullEyeCornerPoints);
  static void correctParameterData(QSharedPointer<BitArray> parameterData, bool compact);
  std::vector<QSharedPointer<Point> > getBullEyeCornerPoints(QSharedPointer<Point> pCenter);
  QSharedPointer<Point> getMatrixCenter();
  QSharedPointer<BitMatrix> sampleGrid(QSharedPointer<BitMatrix> image,
                            QSharedPointer<ResultPoint> topLeft,
                            QSharedPointer<ResultPoint> bottomLeft,
                            QSharedPointer<ResultPoint> bottomRight,
                            QSharedPointer<ResultPoint> topRight);
  void getParameters(QSharedPointer<BitArray> parameterData);
  QSharedPointer<BitArray> sampleLine(QSharedPointer<Point> p1, QSharedPointer<Point> p2, int size);
  bool isWhiteOrBlackRectangle(QSharedPointer<Point> p1,
                               QSharedPointer<Point> p2,
                               QSharedPointer<Point> p3,
                               QSharedPointer<Point> p4);
  int getColor(QSharedPointer<Point> p1, QSharedPointer<Point> p2);
  QSharedPointer<Point> getFirstDifferent(QSharedPointer<Point> init, bool color, int dx, int dy);
  bool isValid(int x, int y);
  static float distance(QSharedPointer<Point> a, QSharedPointer<Point> b);
            
 public:
  Detector(QSharedPointer<BitMatrix> image);
  QSharedPointer<AztecDetectorResult> detect();
};

}
}

#endif // ZXING_AZTEC_DETECTOR_DETECTOR_H
