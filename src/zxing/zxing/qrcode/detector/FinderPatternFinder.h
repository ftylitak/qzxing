// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
#ifndef ZXING_FINDER_PATTERN_FINDER_H
#define ZXING_FINDER_PATTERN_FINDER_H

/*
 *  FinderPatternFinder.h
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

#include <zxing/qrcode/detector/FinderPattern.h>
#include <zxing/qrcode/detector/FinderPatternInfo.h>
#include <QSharedPointer>
#include <zxing/common/BitMatrix.h>
#include <zxing/ResultPointCallback.h>
#include <vector>

namespace zxing {

class DecodeHints;

namespace qrcode {

class FinderPatternFinder {
private:
  static int CENTER_QUORUM;

protected:
  static int MIN_SKIP;
  static int MAX_MODULES;

  QSharedPointer<BitMatrix> image_;
  std::vector<QSharedPointer<FinderPattern> > possibleCenters_;
  bool hasSkipped_;

  QSharedPointer<ResultPointCallback> callback_;
  mutable int crossCheckStateCount[5];

  /** stateCount must be int[5] */
  static float centerFromEnd(int* stateCount, int end);
  static bool foundPatternCross(int* stateCount);

  float crossCheckVertical(size_t startI, size_t centerJ, int maxCount, int originalStateCountTotal);
  float crossCheckHorizontal(size_t startJ, size_t centerI, int maxCount, int originalStateCountTotal);

  /** stateCount must be int[5] */
  bool handlePossibleCenter(int* stateCount, size_t i, size_t j);
  int findRowSkip();
  bool haveMultiplyConfirmedCenters();
  std::vector<QSharedPointer<FinderPattern> > selectBestPatterns();
  static std::vector<QSharedPointer<FinderPattern> > orderBestPatterns(std::vector<QSharedPointer<FinderPattern> > patterns);

  QSharedPointer<BitMatrix> getImage();
  std::vector<QSharedPointer<FinderPattern> >& getPossibleCenters();

  bool crossCheckDiagonal(int startI, int centerJ, int maxCount, int originalStateCountTotal) const;
  int *getCrossCheckStateCount() const;

  static double squaredDistance(QSharedPointer<FinderPattern> a, QSharedPointer<FinderPattern> b);

public:
  static float distance(QSharedPointer<ResultPoint> p1, QSharedPointer<ResultPoint> p2);
  FinderPatternFinder(QSharedPointer<BitMatrix> image, QSharedPointer<ResultPointCallback>const&);
  QSharedPointer<FinderPatternInfo> find(DecodeHints const& hints);
};
}
}

#endif // ZXING_FINDER_PATTERN_FINDER_H
