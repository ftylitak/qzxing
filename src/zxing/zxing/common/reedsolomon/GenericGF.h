// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  GenericGF.h
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

#ifndef GENERICGF_H
#define GENERICGF_H

#include <vector>
#include <QSharedPointer>

namespace zxing {
  class GenericGFPoly;
  
  class GenericGF {
    
  private:
    std::vector<int> expTable;
    std::vector<int> logTable;
    QSharedPointer<GenericGFPoly> zero;
    QSharedPointer<GenericGFPoly> one;
    size_t size;
    int primitive;
    int generatorBase;
    bool initialized;

    GenericGF(int primitive, size_t size, int b);
    
    void initialize();
    void checkInit();
    
  public:
    static QSharedPointer<GenericGF> AZTEC_DATA_12;
    static QSharedPointer<GenericGF> AZTEC_DATA_10;
    static QSharedPointer<GenericGF> AZTEC_DATA_8;
    static QSharedPointer<GenericGF> AZTEC_DATA_6;
    static QSharedPointer<GenericGF> AZTEC_PARAM;
    static QSharedPointer<GenericGF> QR_CODE_FIELD_256;
    static QSharedPointer<GenericGF> DATA_MATRIX_FIELD_256;
    static QSharedPointer<GenericGF> MAXICODE_FIELD_64;

    ~GenericGF();
    
    QSharedPointer<GenericGFPoly> getZero();
    QSharedPointer<GenericGFPoly> getOne();
    size_t getSize();
    int getGeneratorBase();
    QSharedPointer<GenericGFPoly> buildMonomial(int degree, int coefficient);
    
    static int addOrSubtract(int a, int b);
    int exp(int a);
    int log(int a);
    int inverse(int a);
    int multiply(int a, int b);
  };
}

#endif //GENERICGF_H
