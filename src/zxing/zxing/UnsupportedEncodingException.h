#ifndef UNSUPPORTEDENCODINGEXCEPTION_H
#define UNSUPPORTEDENCODINGEXCEPTION_H

#include <zxing/Exception.h>

namespace zxing {

class UnsupportedEncodingException : public Exception {
 public:
  UnsupportedEncodingException() noexcept;
  UnsupportedEncodingException(char const* msg) noexcept;
  ~UnsupportedEncodingException() noexcept;
};

}

#endif // UNSUPPORTEDENCODINGEXCEPTION_H
