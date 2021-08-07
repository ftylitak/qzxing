#ifndef ZXING_FINDER_PATTERN_INFO_H
#define ZXING_FINDER_PATTERN_INFO_H

/*
 *  FinderPatternInfo.h
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
#include <QSharedPointer>
#include <vector>

namespace zxing {
namespace qrcode {

class FinderPatternInfo  {
private:
  QSharedPointer<FinderPattern> bottomLeft_;
  QSharedPointer<FinderPattern> topLeft_;
  QSharedPointer<FinderPattern> topRight_;

public:
  FinderPatternInfo(std::vector<QSharedPointer<FinderPattern> > patternCenters);

  QSharedPointer<FinderPattern> getBottomLeft();
  QSharedPointer<FinderPattern> getTopLeft();
  QSharedPointer<FinderPattern> getTopRight();
};
}
}

#endif // ZXING_FINDER_PATTERN_INFO_H
