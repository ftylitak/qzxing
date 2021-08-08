#ifndef ZXING_WHITERECTANGLEDETECTOR_H
#define ZXING_WHITERECTANGLEDETECTOR_H

/*
 *  WhiteRectangleDetector.h
 *
 *
 *  Created by Luiz Silva on 09/02/2010.
 *  Copyright 2010  authors All rights reserved.
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

#include <vector>
#include <zxing/ReaderException.h>
#include <zxing/ResultPoint.h>
#include <zxing/common/BitMatrix.h>
#include <QSharedPointer>
#include <zxing/ResultPoint.h>


namespace zxing {

class WhiteRectangleDetector  {
  private:
    static int INIT_SIZE;
    static int CORR;
    QSharedPointer<BitMatrix> image_;
    int width_;
    int height_;
    int leftInit_;
    int rightInit_;
    int downInit_;
    int upInit_;

  public:
    WhiteRectangleDetector(QSharedPointer<BitMatrix> image);
    WhiteRectangleDetector(QSharedPointer<BitMatrix> image, int initSize, int x, int y);
    std::vector<QSharedPointer<ResultPoint> > detect();

  private: 
    QSharedPointer<ResultPoint> getBlackPointOnSegment(int aX, int aY, int bX, int bY);
    std::vector<QSharedPointer<ResultPoint> > centerEdges(QSharedPointer<ResultPoint> y, QSharedPointer<ResultPoint> z,
                                    QSharedPointer<ResultPoint> x, QSharedPointer<ResultPoint> t);
    bool containsBlackPoint(int a, int b, int fixed, bool horizontal);
};
}

#endif // ZXING_WHITERECTANGLEDETECTOR_H
