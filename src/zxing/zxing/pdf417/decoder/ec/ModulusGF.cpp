// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
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
 * 2012-09-19 HFN translation from Java into C++
 */

#include <zxing/pdf417/decoder/ec/ModulusGF.h>
#include <zxing/pdf417/decoder/ec/ModulusPoly.h>


using zxing::pdf417::decoder::ec::ModulusGF;
using zxing::pdf417::decoder::ec::ModulusPoly;

/**
 * The central Modulus Galois Field for PDF417 with prime number 929
 * and generator 3.
 */
ModulusGF ModulusGF::PDF417_GF(929,3);


/**
 * <p>A field based on powers of a generator integer, modulo some modulus.</p>
 *
 * @author Sean Owen
 * @see com.google.zxing.common.reedsolomon.GenericGF
 */
 
ModulusGF::ModulusGF(int modulus, int generator)
    : modulus_(modulus) {
    expTable_.reset(new std::vector<int>(modulus_));
    logTable_.reset(new std::vector<int>(modulus_));
  int x = 1,i;
  for (i = 0; i < modulus_; i++) {
    (*expTable_)[i] = x;
    x = (x * generator) % modulus_;
  }
  for (i = 0; i < modulus_-1; i++) {
    (*logTable_)[(*expTable_)[i]] = i;
  }
  // logTable[0] == 0 but this should never be used
	QSharedPointer<std::vector<int>>aZero(new std::vector<int>(1)),aOne(new std::vector<int>(1));
    (*aZero)[0]=0;
    (*aOne)[0]=1;
  zero_.reset(new ModulusPoly(*this, aZero));
  one_.reset(new ModulusPoly(*this, aOne));
}
 
QSharedPointer<ModulusPoly> ModulusGF::getZero() {
  return zero_;
}

QSharedPointer<ModulusPoly> ModulusGF::getOne() {
  return one_;
}

QSharedPointer<ModulusPoly> ModulusGF::buildMonomial(int degree, int coefficient)
{
  if (degree < 0) {
    throw IllegalArgumentException("monomial: degree < 0!");
  }
  if (coefficient == 0) {
    return zero_;
  }
	int nCoefficients = degree + 1;
  QSharedPointer<std::vector<int>> coefficients (new std::vector<int>(nCoefficients));
  (*coefficients)[0] = coefficient;
	QSharedPointer<ModulusPoly> result(new ModulusPoly(*this,coefficients));
  return result;
}

 

int ModulusGF::add(int a, int b) {
  return (a + b) % modulus_;
}

int ModulusGF::subtract(int a, int b) {
  return (modulus_ + a - b) % modulus_;
}

int ModulusGF::exp(int a) {
  return (*expTable_)[a];
}

int ModulusGF::log(int a) {
  if (a == 0) {
    throw IllegalArgumentException("log of zero!");
  }
  return (*logTable_)[a];
}

int ModulusGF::inverse(int a) {
  if (a == 0) {
    throw IllegalArgumentException("inverse of zero!");;
  }
  return (*expTable_)[modulus_ - (*logTable_)[a] - 1];
}

int ModulusGF::multiply(int a, int b) {
  if (a == 0 || b == 0) {
    return 0;
  }
  return (*expTable_)[((*logTable_)[a] + (*logTable_)[b]) % (modulus_ - 1)];
}

int ModulusGF::getSize() {
  return modulus_;
}
