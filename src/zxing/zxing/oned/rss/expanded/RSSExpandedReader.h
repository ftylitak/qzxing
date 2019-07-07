#ifndef RSS_EXPANDED_READER_H
#define RSS_EXPANDED_READER_H

/*
 * Copyright (C) 2010 ZXing authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * These authors would like to acknowledge the Spanish Ministry of Industry,
 * Tourism and Trade, for the support in the project TSI020301-2008-2
 * "PIRAmIDE: Personalizable Interactions with Resources on AmI-enabled
 * Mobile Dynamic Environments", led by Treelogic
 * ( http://www.treelogic.com/ ):
 *
 *   http://www.piramidepse.com/
 */

#include <zxing/oned/rss/AbstractRSSReader.h>
#include <zxing/common/detector/MathUtils.h>
#include <zxing/oned/rss/RSSUtils.h>
#include "ExpandedPair.h"
#include "ExpandedRow.h"
#include "BitArrayBuilder.h"
#include "decoders/AbstractExpandedDecoder.h"

#include <vector>
#include <algorithm>

namespace zxing {

namespace oned {

namespace rss {

/**
 * @author Pablo Orduña, University of Deusto (pablo.orduna@deusto.es)
 * @author Eduardo Castillejo, University of Deusto (eduardo.castillejo@deusto.es)
 */
class RSSExpandedReader : public AbstractRSSReader
{

private:
    std::vector<ExpandedPair> m_pairs;// = new std::vector<ExpandedPair>(MAX_PAIRS);
    std::vector<ExpandedRow> m_rows;// = new ArrayList<>();
    std::vector<int> m_startEnd;// = new int[2];
    bool m_startFromEven;

public:
    Ref<Result> decodeRow(int rowNumber,
                          Ref<BitArray> row,
                          DecodeHints hints);

    void reset();

    // Not private for testing
    std::vector<ExpandedPair> decodeRow2pairs(int rowNumber, Ref<BitArray> row);

    std::vector<ExpandedPair> checkRows(boolean reverse);

    // Try to construct a valid rows sequence
    // Recursion is used to implement backtracking
    std::vector<ExpandedPair> checkRows(std::vector<ExpandedRow> collectedRows, int currentRow);

    // Whether the pairs form a valid find pattern sequence,
    // either complete or a prefix
    static boolean isValidSequence(std::vector<ExpandedPair> pairs);

    void storeRow(int rowNumber, bool wasReversed);

    // Remove all the rows that contains only specified pairs
    static void removePartialRows(std::vector<ExpandedPair> pairs, std::vector<ExpandedRow> rows);

    // Returns true when one of the rows already contains all the pairs
    static bool isPartialRow(std::vector<ExpandedPair> pairs, std::vector<ExpandedRow> rows);

    // Only used for unit testing
    std::vector<ExpandedRow> getRows();

    // Not private for unit testing
    static Ref<Result> constructResult(std::vector<ExpandedPair> pairs);

    bool checkChecksum();

    static int getNextSecondBar(Ref<BitArray> row, int initialPos);

    // not private for testing
    ExpandedPair retrieveNextPair(Ref<BitArray> row, std::vector<ExpandedPair> previousPairs, int rowNumber);

    void findNextPair(Ref<BitArray> row, std::vector<ExpandedPair> previousPairs, int forcedOffset);

    //    private static void reverseCounters(int [] counters) {
    //    int length = counters.length;
    //    for (int i = 0; i < length / 2; ++i) {
    //    int tmp = counters[i];
    //    counters[i] = counters[length - i - 1];
    //    counters[length - i - 1] = tmp;
    //}
    //}

    FinderPattern parseFoundFinderPattern(Ref<BitArray> row, int rowNumber, bool oddPattern);

    DataCharacter decodeDataCharacter(Ref<BitArray> row,
                                      FinderPattern pattern,
                                      bool isOddPattern,
                                      bool leftChar);

    static bool isNotA1left(FinderPattern pattern, boolean isOddPattern, boolean leftChar);

    void adjustOddEvenCounts(int numModules);
};

}
}
}

#endif
