#include "Pair.h"

namespace zxing {
namespace oned {
namespace rss {

Pair::Pair(int value, int checksumPortion, FinderPattern finderPattern)
    : DataCharacter (value, checksumPortion), m_finderPattern(finderPattern)
{
}

Pair::Pair()
    : DataCharacter (0, 0), m_finderPattern(FinderPattern())
{
}

FinderPattern Pair::getFinderPattern() {
    return m_finderPattern;
}

int Pair::getCount() {
    return m_count;
}

void Pair::incrementCount() {
    m_count++;
}


}
}
}
