#ifndef BINARIZER_H_
#define BINARIZER_H_

/*
 *  Binarizer.h
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

#include <zxing/LuminanceSource.h>
#include <zxing/common/BitArray.h>
#include <zxing/common/BitMatrix.h>
#include <QSharedPointer>

namespace zxing {

class Binarizer  {
 private:
  QSharedPointer<LuminanceSource> source_;

 public:
  Binarizer(QSharedPointer<LuminanceSource> source);
  virtual ~Binarizer();

  virtual QSharedPointer<BitArray> getBlackRow(int y, QSharedPointer<BitArray> row) = 0;
  virtual QSharedPointer<BitMatrix> getBlackMatrix() = 0;

  QSharedPointer<LuminanceSource> getLuminanceSource() const ;
  virtual QSharedPointer<Binarizer> createBinarizer(QSharedPointer<LuminanceSource> source) = 0;

  int getWidth() const;
  int getHeight() const;

};

}
#endif /* BINARIZER_H_ */
