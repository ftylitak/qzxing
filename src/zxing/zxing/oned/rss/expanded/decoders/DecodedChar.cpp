#include "DecodedChar.h"

namespace zxing {
namespace oned {
namespace rss {

DecodedChar::DecodedChar(int newPosition, char value) : DecodedObject (newPosition) {
    m_value = value;
}

char DecodedChar::getValue() {
    return m_value;
}

bool DecodedChar::isFNC1() {
    return m_value == FNC1;
}

}
}
}
