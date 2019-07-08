#include "ExpandedPair.h"

namespace zxing {
namespace oned {
namespace rss {

ExpandedPair::ExpandedPair(DataCharacter leftChar, DataCharacter rightChar, FinderPattern finderPattern)
    : m_leftChar(leftChar),
      m_rightChar(rightChar),
      m_finderPattern(finderPattern)
{ }

DataCharacter ExpandedPair::getLeftChar() {
    return m_leftChar;
}

DataCharacter ExpandedPair::getRightChar() {
    return m_rightChar;
}

FinderPattern ExpandedPair::getFinderPattern() {
    return m_finderPattern;
}

bool ExpandedPair::mustBeLast() {
    return m_rightChar.toString().length() == 0;
}

String ExpandedPair::toString() {
    return
            String(String("[ ").getText() + m_leftChar.toString().getText() + String(" , ").getText() + m_rightChar.toString().getText() + " : " +
                   (m_finderPattern.getValue() != 0 ? "null" : std::to_string(m_finderPattern.getValue())) + " ]");
}

bool ExpandedPair::equals(const ExpandedPair &other) {
    return m_leftChar.equals(other.m_leftChar) &&
            m_rightChar.equals(other.m_rightChar) &&
            m_finderPattern.equals(other.m_finderPattern);
}

int ExpandedPair::hashCode() {
    return m_leftChar.hashCode() & m_rightChar.hashCode() & m_finderPattern.hashCode();
}



}
}
}
