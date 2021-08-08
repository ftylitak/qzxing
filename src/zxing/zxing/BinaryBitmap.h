#ifndef ZXING_BINARYBITMAP_H
#define ZXING_BINARYBITMAP_H

/*
 *  BinaryBitmap.h
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

#include <QSharedPointer>
#include <zxing/common/BitMatrix.h>
#include <zxing/common/BitArray.h>
#include <zxing/Binarizer.h>

namespace zxing {
	
	class BinaryBitmap  {
	private:
		QSharedPointer<Binarizer> binarizer_;
		
	public:
		BinaryBitmap(QSharedPointer<Binarizer> binarizer);
		virtual ~BinaryBitmap();
		
		QSharedPointer<BitArray> getBlackRow(int y, QSharedPointer<BitArray> row);
		QSharedPointer<BitMatrix> getBlackMatrix();
		
		QSharedPointer<LuminanceSource> getLuminanceSource() const;

		int getWidth() const;
		int getHeight() const;

		bool isRotateSupported() const;
		QSharedPointer<BinaryBitmap> rotateCounterClockwise();
        QSharedPointer<BinaryBitmap> rotateCounterClockwise45();

		bool isCropSupported() const;
		QSharedPointer<BinaryBitmap> crop(int left, int top, int width, int height);
	};
	
}

#endif /* ZXING_BINARYBITMAP_H */
