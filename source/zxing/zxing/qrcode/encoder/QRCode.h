#ifndef QRCODE_H
#define QRCODE_H

#include <zxing/qrcode/decoder/Mode.h>
#include <zxing/qrcode/Version.h>
#include <zxing/qrcode/ErrorCorrectionLevel.h>
#include "ByteMatrix.h"
#include <string>

namespace zxing {
namespace qrcode {

class QRCode
{
private:
  static const int NUM_MASK_PATTERNS = 8;

  Ref<Mode> mode_ptr_;
  Ref<ErrorCorrectionLevel> ecLevel_ptr_;
  Ref<Version> version_ptr_;
  int maskPattern_;
  Ref<ByteMatrix> matrix_ptr_;

public:

  QRCode();
  ~QRCode();
  Ref<Mode> getMode() const;
  Ref<ErrorCorrectionLevel> getECLevel() const;
  Ref<Version> getVersion() const;
  const int getMaskPattern() const;
  Ref<ByteMatrix> getMatrix() const;
  const std::string toString();
  void setMode(Ref<Mode> value);
  void setECLevel(Ref<ErrorCorrectionLevel> value);
  void setVersion(Ref<Version> version);
  void setMaskPattern(int value);
  void setMatrix(Ref<ByteMatrix> value);

  static bool isValidMaskPattern(int maskPattern)
  {
    return maskPattern >= 0 && maskPattern < NUM_MASK_PATTERNS;
  }

};

}
}

#endif //QRCODE_H
