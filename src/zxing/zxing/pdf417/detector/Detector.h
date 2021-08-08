#ifndef ZXING_DETECTOR_H_
#define ZXING_DETECTOR_H_

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

#include <zxing/common/Point.h>
#include <zxing/common/DetectorResult.h>
#include <zxing/NotFoundException.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>

namespace zxing {
namespace pdf417 {
namespace detector {

class Detector {
private:
  static const int INTEGER_MATH_SHIFT = 8;
  static const int PATTERN_MATCH_RESULT_SCALE_FACTOR = 1 << INTEGER_MATH_SHIFT;
  static const int MAX_AVG_VARIANCE;
  static const int MAX_INDIVIDUAL_VARIANCE;

  static const int START_PATTERN[];
  static const int START_PATTERN_LENGTH;
  static const int START_PATTERN_REVERSE[];
  static const int START_PATTERN_REVERSE_LENGTH;
  static const int STOP_PATTERN[];
  static const int STOP_PATTERN_LENGTH;
  static const int STOP_PATTERN_REVERSE[];
  static const int STOP_PATTERN_REVERSE_LENGTH;

  QSharedPointer<BinaryBitmap> image_;
  
  static QSharedPointer<std::vector<QSharedPointer<ResultPoint>> > findVertices(QSharedPointer<BitMatrix> matrix, int rowStep);
  static QSharedPointer<std::vector<QSharedPointer<ResultPoint>> > findVertices180(QSharedPointer<BitMatrix> matrix, int rowStep);

  static QSharedPointer<std::vector<int>> findGuardPattern(QSharedPointer<BitMatrix> matrix,
                                        int column,
                                        int row,
                                        int width,
                                        bool whiteFirst,
                                        const int pattern[],
                                        int patternSize,
                                        QSharedPointer<std::vector<int>>& counters);
  static int patternMatchVariance(QSharedPointer<std::vector<int>>& counters, const int pattern[],
                                  int maxIndividualVariance);

  static void correctVertices(QSharedPointer<BitMatrix> matrix,
                              QSharedPointer<std::vector<QSharedPointer<ResultPoint>> >& vertices,
                              bool upsideDown);
  static void findWideBarTopBottom(QSharedPointer<BitMatrix> matrix,
                                   QSharedPointer<std::vector<QSharedPointer<ResultPoint>> >& vertices,
                                   int offsetVertice,
                                   int startWideBar,
                                   int lenWideBar,
                                   int lenPattern,
                                   int nIncrement);
  static void findCrossingPoint(QSharedPointer<std::vector<QSharedPointer<ResultPoint>> >& vertices,
                                int idxResult,
                                int idxLineA1,int idxLineA2,
                                int idxLineB1,int idxLineB2,
                                QSharedPointer<BitMatrix>& matrix);
  static Point intersection(Line a, Line b);
  static float computeModuleWidth(QSharedPointer<std::vector<QSharedPointer<ResultPoint>> >& vertices);
  static int computeDimension(QSharedPointer<ResultPoint> const& topLeft,
                              QSharedPointer<ResultPoint> const& topRight,
                              QSharedPointer<ResultPoint> const& bottomLeft,
                              QSharedPointer<ResultPoint> const& bottomRight,
                              float moduleWidth);
  int computeYDimension(QSharedPointer<ResultPoint> const& topLeft,
                        QSharedPointer<ResultPoint> const& topRight,
                        QSharedPointer<ResultPoint> const& bottomLeft,
                        QSharedPointer<ResultPoint> const& bottomRight,
                        float moduleWidth);

  QSharedPointer<BitMatrix> sampleLines(QSharedPointer<std::vector<QSharedPointer<ResultPoint>> > const& vertices, int dimensionY, int dimension);

public:
  Detector(QSharedPointer<BinaryBitmap> image);
  QSharedPointer<BinaryBitmap> getImage();
  QSharedPointer<DetectorResult> detect();
  QSharedPointer<DetectorResult> detect(DecodeHints const& hints);
};

}
}
}

#endif // ZXING_DETECTOR_H_
