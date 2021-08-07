#ifndef ZXING_BIT_MATRIX_PARSER_PDF_H
#define ZXING_BIT_MATRIX_PARSER_PDF_H

/*
 *  BitMatrixParser.h / PDF417
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

#include <zxing/ReaderException.h>
#include <zxing/FormatException.h>
#include <zxing/common/BitMatrix.h>
#include <QSharedPointer>
#include <stdint.h>

namespace zxing {
namespace pdf417 {
namespace decoder {

class BitMatrixParser  {
private:
  static const int MAX_ROWS;
  // Maximum Codewords (Data + Error)
  static const int MAX_CW_CAPACITY;
  static const int MODULES_IN_SYMBOL;

  QSharedPointer<BitMatrix> bitMatrix_;
  int rows_; /* = 0 */
  int leftColumnECData_; /* = 0 */
  int rightColumnECData_; /* = 0 */
  /* added 2012-06-22 HFN */
  int aLeftColumnTriple_[3];
  int aRightColumnTriple_[3];
  int eraseCount_; /* = 0 */
  QSharedPointer<std::vector<int>> erasures_;
  int ecLevel_; /* = -1 */

public:
  static const int SYMBOL_TABLE[];
  static const int SYMBOL_TABLE_LENGTH;
  static const int CODEWORD_TABLE[];
  
public:
  BitMatrixParser(QSharedPointer<BitMatrix> bitMatrix);
  QSharedPointer<std::vector<int>> getErasures() const {return erasures_;}
  int getECLevel() const {return ecLevel_;}
  int getEraseCount() const {return eraseCount_;}
  QSharedPointer<std::vector<int>> readCodewords(); /* throw(FormatException) */
  static int getCodeword(int64_t symbol, int *pi = NULL);

private:
  bool VerifyOuterColumns(int rownumber);
  static QSharedPointer<std::vector<int>> trimArray(QSharedPointer<std::vector<int>> array, int size);
  static int findCodewordIndex(int64_t symbol);

  
  int processRow(int rowNumber,
                QSharedPointer<std::vector<int>> codewords, int next);
  
  int processRow(QSharedPointer<std::vector<int>> rowCounters, int rowNumber, int rowHeight,
    QSharedPointer<std::vector<int>> codewords, int next); /* throw(FormatException)  */ 
protected:
  bool IsEqual(int &a, int &b, int rownumber);
};
 
}
}
}

#endif // ZXING_BIT_MATRIX_PARSER_PDF_H
