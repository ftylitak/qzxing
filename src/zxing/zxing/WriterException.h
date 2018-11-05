#ifndef WRITEREXCEPTION_H
#define WRITEREXCEPTION_H

#include <zxing/Exception.h>

namespace zxing {

class WriterException : public Exception {
 public:
  WriterException() noexcept;
  WriterException(char const* msg) noexcept;
  ~WriterException() noexcept;
};

}

#endif // WRITEREXCEPTION_H
