#ifndef BYTEMATRIX_H
#define BYTEMATRIX_H

#include <vector>
#include <string>
#include <zxing/common/Counted.h>

namespace zxing {
namespace qrcode {

class ByteMatrix : public Counted
{
private:
  std::vector< std::vector<unsigned char> > bytes_;
  size_t width_;
  size_t height_;

public:

  ByteMatrix(size_t width, size_t height);

  size_t getHeight() const;
  size_t getWidth() const;
  unsigned char get(size_t x, size_t y) const;

  std::vector<std::vector<unsigned char> > getArray() const;
  void set(size_t x, size_t y, const unsigned char value);
  void set(size_t x, size_t y, size_t value);
  void set(size_t x, size_t y, bool value);
  void clear(const unsigned char value);
  const std::string toString() const;

};

}
}

#endif //BYTEMATRIX_H
