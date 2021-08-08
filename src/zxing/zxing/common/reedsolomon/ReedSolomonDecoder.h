#ifndef ZXING_REED_SOLOMON_DECODER_H
#define ZXING_REED_SOLOMON_DECODER_H

/*
 *  ReedSolomonDecoder.h
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

#include <memory>
#include <vector>
#include <QSharedPointer>
#include <zxing/common/reedsolomon/GenericGFPoly.h>
#include <zxing/common/reedsolomon/GenericGF.h>

namespace zxing {
class GenericGFPoly;
class GenericGF;

class ReedSolomonDecoder {
private:
  QSharedPointer<GenericGF> field;
public:
  ReedSolomonDecoder(QSharedPointer<GenericGF> fld);
  ~ReedSolomonDecoder();
  void decode(QSharedPointer<std::vector<int>> received, int twoS);
  std::vector<QSharedPointer<GenericGFPoly> > runEuclideanAlgorithm(QSharedPointer<GenericGFPoly> a, QSharedPointer<GenericGFPoly> b, int R);

private:
  QSharedPointer<std::vector<int>> findErrorLocations(QSharedPointer<GenericGFPoly> errorLocator);
  QSharedPointer<std::vector<int>> findErrorMagnitudes(QSharedPointer<GenericGFPoly> errorEvaluator, QSharedPointer<std::vector<int>> errorLocations);
};
}

#endif // ZXING_REED_SOLOMON_DECODER_H
