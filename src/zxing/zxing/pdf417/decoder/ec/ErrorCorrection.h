// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-

#ifndef ZXING_ERROR_CORRECTION_PDF_H
#define ZXING_ERROR_CORRECTION_PDF_H
/*
 * Copyright 2012 ZXing authors
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
 *
 * 2012-09-17 HFN translation from Java into C++
 */

#include <QSharedPointer>
#include <zxing/common/DecoderResult.h>
#include <zxing/common/BitMatrix.h>
#include <zxing/pdf417/decoder/ec/ModulusGF.h>
#include <zxing/pdf417/decoder/ec/ModulusPoly.h>
#include <zxing/common/reedsolomon/ReedSolomonException.h>

namespace zxing {
namespace pdf417 {
namespace decoder {
namespace ec {


/**
 * <p>PDF417 error correction implementation.</p>
 *
 * <p>This <a href="http://en.wikipedia.org/wiki/Reed%E2%80%93Solomon_error_correction#Example">example</a>
 * is quite useful in understanding the algorithm.</p>
 *
 * @author Sean Owen
 * @see com.google.zxing.common.reedsolomon.ReedSolomonDecoder
 */
class ErrorCorrection {

 private:
  ModulusGF &field_;

 public:
  ErrorCorrection();
  void decode(QSharedPointer<std::vector<int>> received,
              int numECCodewords,
              QSharedPointer<std::vector<int>> erasures);

 private:
  std::vector<QSharedPointer<ModulusPoly> > runEuclideanAlgorithm(QSharedPointer<ModulusPoly> a, QSharedPointer<ModulusPoly> b, int R);

  QSharedPointer<std::vector<int>> findErrorLocations(QSharedPointer<ModulusPoly> errorLocator);
  QSharedPointer<std::vector<int>> findErrorMagnitudes(QSharedPointer<ModulusPoly> errorEvaluator,
                                    QSharedPointer<ModulusPoly> errorLocator,
                                    QSharedPointer<std::vector<int>> errorLocations);
};

}
}
}
}

#endif /* ZXING_ERROR_CORRECTION_PDF_H */
