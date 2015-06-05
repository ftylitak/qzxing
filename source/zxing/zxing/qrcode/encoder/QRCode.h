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

  Mode* mode_ptr_;
  ErrorCorrectionLevel* ecLevel_ptr_;
  Version* version_ptr_;
  int maskPattern_;
  ByteMatrix* matrix_ptr_;

public:

  QRCode();
  ~QRCode();
  const Mode* getMode() const;
  const ErrorCorrectionLevel* getECLevel() const;
  const Version* getVersion() const;
  const int getMaskPattern() const;
  const ByteMatrix* getMatrix() const;
  const std::string toString();
  void setMode(Mode* value);
  void setECLevel(ErrorCorrectionLevel* value);
  void setVersion(Version* version);
  void setMaskPattern(int value);
  void setMatrix(ByteMatrix* value);

  static bool isValidMaskPattern(int maskPattern)
  {
    return maskPattern >= 0 && maskPattern < NUM_MASK_PATTERNS;
  }

};

}
}

#endif //QRCODE_H
