#include "DecodedNumeric.h"

namespace zxing {
namespace oned {
namespace rss {

DecodedNumeric::DecodedNumeric(int newPosition, int firstDigit, int secondDigit)
    : DecodedObject(newPosition) {

    if (firstDigit < 0 || firstDigit > 10 || secondDigit < 0 || secondDigit > 10) {
        throw FormatException::getFormatInstance();
    }

    m_newPosition = newPosition;
    m_firstDigit  = firstDigit;
    m_secondDigit = secondDigit;
}

int DecodedNumeric::getFirstDigit() {
    return m_firstDigit;
}

int DecodedNumeric::getSecondDigit() {
    return m_secondDigit;
}

int DecodedNumeric::getValue() {
    return m_firstDigit * 10 + m_secondDigit;
}

bool DecodedNumeric::isFirstDigitFNC1() {
    return m_firstDigit == FNC1;
}

bool DecodedNumeric::isSecondDigitFNC1() {
    return m_secondDigit == FNC1;
}

}
}
}
