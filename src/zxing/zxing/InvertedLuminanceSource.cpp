// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  Copyright 2013 ZXing authors All rights reserved.
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

#include <zxing/ZXing.h>
#include <zxing/InvertedLuminanceSource.h>


using zxing::LuminanceSource;

namespace zxing
{

  InvertedLuminanceSource::InvertedLuminanceSource(QSharedPointer<LuminanceSource> const &delegate_)
      : Super(delegate_->getWidth(), delegate_->getHeight()), delegate(delegate_) {}

  QSharedPointer<std::vector<zxing::byte>> InvertedLuminanceSource::getRow(int y, QSharedPointer<std::vector<zxing::byte>> row) const
  {
    row = delegate->getRow(y, row);
    int width = getWidth();
    for (int i = 0; i < width; i++)
    {
      (*row)[i] = 0xFF - (*row)[i];
    }
    return row;
  }

  QSharedPointer<std::vector<zxing::byte>> InvertedLuminanceSource::getMatrix() const
  {
    QSharedPointer<std::vector<zxing::byte>> matrix = delegate->getMatrix();
    int length = getWidth() * getHeight();
    QSharedPointer<std::vector<zxing::byte>> invertedMatrix(new std::vector<zxing::byte>(length));
    for (int i = 0; i < length; i++)
    {
      (*invertedMatrix)[i] = 0xFF - (*matrix)[i];
    }
    return invertedMatrix;
  }

  zxing::boolean InvertedLuminanceSource::isCropSupported() const
  {
    return delegate->isCropSupported();
  }

  QSharedPointer<LuminanceSource> InvertedLuminanceSource::crop(int left, int top, int width, int height) const
  {
    return QSharedPointer<LuminanceSource>(new InvertedLuminanceSource(delegate->crop(left, top, width, height)));
  }

  zxing::boolean InvertedLuminanceSource::isRotateSupported() const
  {
    return delegate->isRotateSupported();
  }

  QSharedPointer<LuminanceSource> InvertedLuminanceSource::invert() const
  {
    return delegate;
  }

  QSharedPointer<LuminanceSource> InvertedLuminanceSource::rotateCounterClockwise() const
  {
    return QSharedPointer<LuminanceSource>(new InvertedLuminanceSource(delegate->rotateCounterClockwise()));
  }

}
