#include "DecodedInformation.h"

namespace zxing {
namespace oned {
namespace rss {

DecodedInformation::DecodedInformation(const DecodedInformation *other) :
    DecodedObject (other->m_newPosition),
    m_newString(other->m_newString)
{
    m_newString = other->m_newString;
    m_remaining = other->m_remaining;
    m_remainingValue = other->m_remainingValue;
}

DecodedInformation::DecodedInformation(int newPosition, String newString) :
    DecodedObject (newPosition),
    m_newString(newString)
{
    m_remaining = false;
    m_remainingValue = 0;
}

DecodedInformation::DecodedInformation(int newPosition, String newString, int remainingValue) :
    DecodedObject (newPosition),
    m_newString(newString)
{
    m_remaining = true;
    m_remainingValue = remainingValue;
}

String DecodedInformation::getNewString() {
    return m_newString;
}

bool DecodedInformation::isRemaining() {
    return m_remaining;
}

int DecodedInformation::getRemainingValue() {
    return m_remainingValue;
}


}
}
}
