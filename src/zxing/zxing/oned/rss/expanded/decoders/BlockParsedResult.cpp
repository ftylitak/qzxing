#include "BlockParsedResult.h"

namespace zxing {
namespace oned {
namespace rss {

BlockParsedResult::BlockParsedResult(bool finished) : m_decodedInformation(nullptr), m_finished(finished) {
}

BlockParsedResult::BlockParsedResult(const DecodedInformation &information, bool finished) {
    m_finished = finished;
    m_decodedInformation = information;
}

BlockParsedResult::BlockParsedResult(const BlockParsedResult &other) {
    m_finished = other.m_finished;
    m_decodedInformation = other.m_decodedInformation;
}

DecodedInformation BlockParsedResult::getDecodedInformation() {
    return m_decodedInformation;
}

bool BlockParsedResult::isFinished() {
    return m_finished;
}


}
}
}
