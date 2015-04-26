#ifndef BYTEMATRIX_H
#define BYTEMATRIX_H

#include <vector>
#include <string>

namespace zxing {
namespace qrcode {

class ByteMatrix
{
private:
  std::vector< std::vector<char> > bytes_;
  size_t width_;
  size_t height_;

public:

  ByteMatrix(size_t width, size_t height);

  size_t getHeight();
  size_t getWidth();
  char get(size_t x, size_t y);

  std::vector< std::vector<char> > getArray();
  void set(size_t x, size_t y, const char value);
  void set(size_t x, size_t y, size_t value);
  void set(size_t x, size_t y, bool value);
  void clear(const char value);
  const std::string toString();

};

}
}

#endif //BYTEMATRIX_H
