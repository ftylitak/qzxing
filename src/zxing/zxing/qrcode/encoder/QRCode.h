#ifndef QRCODE_H
#define QRCODE_H

#include <zxing/qrcode/decoder/Mode.h>
#include <zxing/qrcode/Version.h>
#include <zxing/qrcode/ErrorCorrectionLevel.h>
#include "ByteMatrix.h"
#include <QSharedPointer>
#include <string>

namespace zxing {
namespace qrcode {

class QRCode 
{
private:

  Mode mode_;
  QSharedPointer<ErrorCorrectionLevel> ecLevel_ptr_;
  QSharedPointer<Version> version_ptr_;
  int maskPattern_;
  QSharedPointer<ByteMatrix> matrix_ptr_;

public:
  static const int NUM_MASK_PATTERNS = 8;

  QRCode();
  ~QRCode();
  Mode getMode() const;
  QSharedPointer<ErrorCorrectionLevel> getECLevel() const;
  QSharedPointer<Version> getVersion() const;
  int getMaskPattern() const;
  QSharedPointer<ByteMatrix> getMatrix() const;
  std::string toString() const;
  void setMode(const Mode &value);
  void setECLevel(QSharedPointer<ErrorCorrectionLevel> value);
  void setVersion(QSharedPointer<Version> version);
  void setMaskPattern(int value);
  void setMatrix(QSharedPointer<ByteMatrix> value);

  static bool isValidMaskPattern(int maskPattern)
  {
    return maskPattern >= 0 && maskPattern < NUM_MASK_PATTERNS;
  }

};

}
}

#endif //QRCODE_H
