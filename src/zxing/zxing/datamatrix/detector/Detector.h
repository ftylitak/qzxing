// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
#ifndef ZXING_DETECTOR_H
#define ZXING_DETECTOR_H

/*
 *  Detector.h
 *  zxing
 *
 *  Created by Luiz Silva on 09/02/2010.
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
#include <zxing/common/PerspectiveTransform.h>
#include <zxing/common/detector/WhiteRectangleDetector.h>

namespace zxing {
namespace datamatrix {

class ResultPointsAndTransitions {
  private:
    QSharedPointer<ResultPoint> to_;
    QSharedPointer<ResultPoint> from_;
    int transitions_;

  public:
    ResultPointsAndTransitions();
    ResultPointsAndTransitions(QSharedPointer<ResultPoint> from, QSharedPointer<ResultPoint> to, int transitions);
    QSharedPointer<ResultPoint> getFrom();
    QSharedPointer<ResultPoint> getTo();
    int getTransitions();
};

class Detector {
  private:
    QSharedPointer<BitMatrix> image_;

  protected:
    QSharedPointer<BitMatrix> sampleGrid(QSharedPointer<BitMatrix> image, int dimensionX, int dimensionY,
        QSharedPointer<PerspectiveTransform> transform);

    void insertionSort(std::vector<QSharedPointer<ResultPointsAndTransitions> >& vector);

    QSharedPointer<ResultPoint> correctTopRightRectangular(QSharedPointer<ResultPoint> bottomLeft,
        QSharedPointer<ResultPoint> bottomRight, QSharedPointer<ResultPoint> topLeft, QSharedPointer<ResultPoint> topRight,
        int dimensionTop, int dimensionRight);
    QSharedPointer<ResultPoint> correctTopRight(QSharedPointer<ResultPoint> bottomLeft, QSharedPointer<ResultPoint> bottomRight,
        QSharedPointer<ResultPoint> topLeft, QSharedPointer<ResultPoint> topRight, int dimension);
    bool isValid(QSharedPointer<ResultPoint> p);
    int distance(QSharedPointer<ResultPoint> a, QSharedPointer<ResultPoint> b);
    QSharedPointer<ResultPointsAndTransitions> transitionsBetween(QSharedPointer<ResultPoint> from, QSharedPointer<ResultPoint> to);
    int min(int a, int b) {
      return a > b ? b : a;
    }
    /**
     * Ends up being a bit faster than round(). This merely rounds its
     * argument to the nearest int, where x.5 rounds up.
     */
    int round(float d) {
      return (int) (d + 0.5f);
    }

  public:
    QSharedPointer<BitMatrix> getImage();
    Detector(QSharedPointer<BitMatrix> image);

    virtual QSharedPointer<PerspectiveTransform> createTransform(QSharedPointer<ResultPoint> topLeft,
        QSharedPointer<ResultPoint> topRight, QSharedPointer<ResultPoint> bottomLeft, QSharedPointer<ResultPoint> bottomRight,
        int dimensionX, int dimensionY);

    QSharedPointer<DetectorResult> detect();

  private:
    int compare(QSharedPointer<ResultPointsAndTransitions> a, QSharedPointer<ResultPointsAndTransitions> b);
};

}
}

#endif // ZXING_DETECTOR_H
