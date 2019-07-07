#include "ExpandedRow.h"

namespace zxing {
namespace oned {
namespace rss {

ExpandedRow::ExpandedRow(std::vector<ExpandedPair> pairs, int rowNumber, bool wasReversed) {
    m_pairs = std::vector<ExpandedPair>(pairs);
    m_rowNumber = rowNumber;
    m_wasReversed = wasReversed;
}

std::vector<ExpandedPair> ExpandedRow::getPairs() {
    return m_pairs;
}

int ExpandedRow::getRowNumber() {
    return m_rowNumber;
}

bool ExpandedRow::isEquivalent(std::vector<ExpandedPair> otherPairs) {

    if (m_pairs.size() != otherPairs.size()) {
        return false;
    }

    for (int i = 0; i < m_pairs.size(); i++) {
        if (!m_pairs[i].equals(otherPairs[i])) {
            return false;
        }
    }

    return true;
}

String ExpandedRow::toString() {
    String result("{ ");
    for (auto i : m_pairs) {
        result.append(i.toString().getText());
    }
    result.append(" }");
    return result;
}


}
}
}
