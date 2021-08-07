#ifndef ZXING_MODULUS_GFPOLY_PDF_H
#define ZXING_MODULUS_GFPOLY_PDF_H

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

namespace zxing {
namespace pdf417 {
namespace decoder {
namespace ec {

class ModulusGF;

/**
 * @author Sean Owen
 * @see com.google.zxing.common.reedsolomon.GenericGFPoly
 */
class ModulusPoly {

  private:
	ModulusGF &field_;
	QSharedPointer<std::vector<int>> coefficients_;
  public:
	ModulusPoly(ModulusGF& field, QSharedPointer<std::vector<int>> coefficients);
	~ModulusPoly();
	QSharedPointer<std::vector<int>> getCoefficients();
	int getDegree();
	bool isZero();
	int getCoefficient(int degree);
	int evaluateAt(int a);
	QSharedPointer<ModulusPoly> add(QSharedPointer<ModulusPoly> other);
	QSharedPointer<ModulusPoly> subtract(QSharedPointer<ModulusPoly> other);
	QSharedPointer<ModulusPoly> multiply(QSharedPointer<ModulusPoly> other);
	QSharedPointer<ModulusPoly> negative();
	QSharedPointer<ModulusPoly> multiply(int scalar);
	QSharedPointer<ModulusPoly> multiplyByMonomial(int degree, int coefficient);
	std::vector<QSharedPointer<ModulusPoly> > divide(QSharedPointer<ModulusPoly> other);
	#if 0
    public String toString();
	#endif
};

}
}
}
}

#endif /* ZXING_MODULUS_GFPOLY_PDF_H */
