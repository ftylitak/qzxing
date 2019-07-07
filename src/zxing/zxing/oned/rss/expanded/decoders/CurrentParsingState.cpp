#include "CurrentParsingState.h"

namespace zxing {
namespace oned {
namespace rss {

CurrentParsingState::CurrentParsingState() {
    position = 0;
    encoding = State::NUMERIC;
}

int CurrentParsingState::getPosition() {
    return position;
}

void CurrentParsingState::setPosition(int _position) {
    position = _position;
}

void CurrentParsingState::incrementPosition(int delta) {
    position += delta;
}

bool CurrentParsingState::isAlpha() {
    return encoding == State::ALPHA;
}

bool CurrentParsingState::isNumeric() {
    return encoding == State::NUMERIC;
}

bool CurrentParsingState::isIsoIec646() {
    return encoding == State::ISO_IEC_646;
}

void CurrentParsingState::setNumeric() {
    encoding = State::NUMERIC;
}

void CurrentParsingState::setAlpha() {
    encoding = State::ALPHA;
}

void CurrentParsingState::setIsoIec646() {
    encoding = State::ISO_IEC_646;
}


}
}
}
