#include "QRCode.h"

#include <sstream>

namespace zxing {
namespace qrcode {

QRCode::QRCode() :
    ecLevel_ptr_(NULL),
    version_ptr_(NULL),
    maskPattern_(-1),
    matrix_ptr_(NULL) {}

QRCode::~QRCode()
{
}

Mode QRCode::getMode() const
{
    return mode_;
}

QSharedPointer<ErrorCorrectionLevel> QRCode::getECLevel() const
{
    return ecLevel_ptr_;
}

QSharedPointer<Version> QRCode::getVersion() const
{
    return version_ptr_;
}

int QRCode::getMaskPattern() const
{
    return maskPattern_;
}

QSharedPointer<ByteMatrix> QRCode::getMatrix() const
{
    return matrix_ptr_;
}

std::string QRCode::toString() const
{
    std::stringstream result;
    result << "<<";

    result << "\n mode: ";
    result << mode_.getName();

    result << "\n ecLevel: ";
    if(!ecLevel_ptr_.isNull())
        result << ecLevel_ptr_->name();
    else
        result << "null";

    result << "\n version: ";
    if(version_ptr_)
    {
        std::string version_str;
        std::ostringstream convert;
        convert << version_ptr_->getVersionNumber();
        version_str = convert.str();
        result << version_str;
    }
    else
        result << "null";

    result << "\n maskPattern: ";
    result << maskPattern_;

    if (matrix_ptr_)
        result << "\n matrix:\n" << matrix_ptr_->toString();
    else
        result << "\n matrix: null\n";

    result << "\n>>";
    return result.str();
}

void QRCode::setMode(const Mode& value)
{
    mode_ = value;
}

void QRCode::setECLevel(QSharedPointer<ErrorCorrectionLevel> value)
{
    ecLevel_ptr_ = value;
}

void QRCode::setVersion(QSharedPointer<Version> version)
{
    version_ptr_ = version;
}

void QRCode::setMaskPattern(int value)
{
    maskPattern_ = value;
}

void QRCode::setMatrix(QSharedPointer<ByteMatrix> value)
{
    matrix_ptr_ = value;
}

}
}
