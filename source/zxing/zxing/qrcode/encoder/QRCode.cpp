#include "QRCode.h"

#include <sstream>

namespace zxing {
namespace qrcode {

QRCode::QRCode() :
    mode_ptr_(NULL),
    ecLevel_ptr_(NULL),
    version_ptr_(NULL),
    maskPattern_(-1),
    matrix_ptr_(NULL) {}

const Mode *QRCode::getMode() const
{
  return mode_ptr_;
}

const ErrorCorrectionLevel *QRCode::getECLevel() const
{
  return ecLevel_ptr_;
}

const Version *QRCode::getVersion() const
{
  return version_ptr_;
}

const int QRCode::getMaskPattern() const
{
  return maskPattern_;
}

const ByteMatrix *QRCode::getMatrix() const
{
  return matrix_ptr_;
}

const std::string QRCode::toString()
{
  std::stringstream result;
  result << "<<\n";
  result << " mode: {unimpl}";
  //result << mode_;
  result << "\n ecLevel: {unimpl}";
  //result << ecLevel_;
  result << "\n version: ";
  //result << version_;
  result << "\n maskPattern: ";
  result << maskPattern_;
//  if (matrix_ == null) {
//    result.append("\n matrix: null\n");
//  } else {
    result << "\n matrix:\n";
    result << matrix_ptr_->toString();
//  }
  result << ">>\n";
  return result.str();
}

void QRCode::setMode(const Mode& value)
{
  mode_ptr_ = new Mode(value);
}

/*
 * Make copy constructors for all the used classes.
 * Also make destructors for all
 */

void QRCode::setECLevel(const ErrorCorrectionLevel& value)
{
  //ecLevel_ptr_ = value;
}

void QRCode::setVersion(const Version& version)
{
  //version_ptr_ = version;
}

void QRCode::setMaskPattern(int value)
{
  //maskPattern_ptr_ = value;
}

void QRCode::setMatrix(const ByteMatrix &value)
{
  //matrix_ptr_ = value;
}

}
}
