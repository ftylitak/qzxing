// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  GenericGF.cpp
 *  zxing
 *
 *  Created by Lukas Stabe on 13/02/2012.
 *  Copyright 2012 ZXing authors All rights reserved.
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

#include <iostream>
#include <zxing/common/reedsolomon/GenericGF.h>
#include <zxing/common/reedsolomon/GenericGFPoly.h>
#include <zxing/common/IllegalArgumentException.h>

using zxing::GenericGF;
using zxing::GenericGFPoly;


QSharedPointer<GenericGF> GenericGF::AZTEC_DATA_12(new GenericGF(0x1069, 4096, 1));
QSharedPointer<GenericGF> GenericGF::AZTEC_DATA_10(new GenericGF(0x409, 1024, 1));
QSharedPointer<GenericGF> GenericGF::AZTEC_DATA_6(new GenericGF(0x43, 64, 1));
QSharedPointer<GenericGF> GenericGF::AZTEC_PARAM(new GenericGF(0x13, 16, 1));
QSharedPointer<GenericGF> GenericGF::QR_CODE_FIELD_256(new GenericGF(0x011D, 256, 0));
QSharedPointer<GenericGF> GenericGF::DATA_MATRIX_FIELD_256(new GenericGF(0x012D, 256, 1));
QSharedPointer<GenericGF> GenericGF::AZTEC_DATA_8 = DATA_MATRIX_FIELD_256;
QSharedPointer<GenericGF> GenericGF::MAXICODE_FIELD_64 = AZTEC_DATA_6;

namespace {
  size_t INITIALIZATION_THRESHOLD = 0;
}

GenericGF::GenericGF(int primitive_, size_t size_, int b)
  : size(size_), primitive(primitive_), generatorBase(b), initialized(false) {
  if (size <= INITIALIZATION_THRESHOLD) {
    initialize();
  }
}

GenericGF::~GenericGF()
{
    return;
}

void GenericGF::initialize() {
  expTable = std::vector<int>(size);
  logTable = std::vector<int>(size);

  size_t x = 1;

  for (size_t i = 0; i < size; i++) {
    expTable[i] = x;
    x <<= 1; // x = x * 2; we're assuming the generator alpha is 2
    if (x >= size) {
      x ^= primitive;
      x &= size-1;
    }
  }
  for (size_t i = 0; i < size-1; i++) {
    logTable.at(expTable.at(i)) = i;
  }
  //logTable[0] == 0 but this should never be used
  QSharedPointer<std::vector<int>> coefficients_zero(new std::vector<int>(1));
  QSharedPointer<std::vector<int>> coefficients_one(new std::vector<int>(1));

  (*coefficients_zero)[0] = 0;
  (*coefficients_one)[0] = 1;

  zero = QSharedPointer<GenericGFPoly>(new GenericGFPoly(this, coefficients_zero));
  one = QSharedPointer<GenericGFPoly>(new GenericGFPoly(this, coefficients_one));
  initialized = true;
}

void GenericGF::checkInit() {
  if (!initialized) {
    initialize();
  }
}

QSharedPointer<GenericGFPoly> GenericGF::getZero() {
  checkInit();
  return zero;
}

QSharedPointer<GenericGFPoly> GenericGF::getOne() {
  checkInit();
  return one;
}

QSharedPointer<GenericGFPoly> GenericGF::buildMonomial(int degree, int coefficient) {
  checkInit();

  if (degree < 0) {
    throw IllegalArgumentException("Degree must be non-negative");
  }
  if (coefficient == 0) {
    return zero;
  }
  QSharedPointer<std::vector<int>> coefficients(new std::vector<int>(degree + 1));
  (*coefficients)[0] = coefficient;

  return QSharedPointer<GenericGFPoly>(new GenericGFPoly(this, coefficients));
}

int GenericGF::addOrSubtract(int a, int b) {
  return a ^ b;
}

int GenericGF::exp(int a) {
  checkInit();
  return expTable[a];
}

int GenericGF::log(int a) {
  checkInit();
  if (a == 0) {
    throw IllegalArgumentException("cannot give log(0)");
  }
  return logTable[a];
}

int GenericGF::inverse(int a) {
  checkInit();
  if (a == 0) {
    throw IllegalArgumentException("Cannot calculate the inverse of 0");
  }
  return expTable[size - logTable[a] - 1];
}

int GenericGF::multiply(int a, int b) {
  checkInit();

  if (a == 0 || b == 0) {
    return 0;
  }

  return expTable[(logTable[a] + logTable[b]) % (size - 1)];
  }

size_t GenericGF::getSize() {
  return size;
}

int GenericGF::getGeneratorBase() {
  return generatorBase;
}
