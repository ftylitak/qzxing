#include "AbstractRSSReader.h"

namespace zxing {
namespace oned {
namespace rss {

AbstractRSSReader::AbstractRSSReader()
{
    m_decodeFinderCounters = std::vector<int>(4);
    m_dataCharacterCounters = std::vector<int>(8);
    m_oddRoundingErrors = std::vector<float>(4);
    m_evenRoundingErrors = std::vector<float>(4);
    m_oddCounts = std::vector<int>(m_dataCharacterCounters.size() / 2);
    m_evenCounts = std::vector<int>(m_dataCharacterCounters.size() / 2);
}

std::vector<int> AbstractRSSReader::getDecodeFinderCounters()
{
    return m_decodeFinderCounters;
}

std::vector<int> AbstractRSSReader::getDataCharacterCounters()
{
    return m_dataCharacterCounters;
}

std::vector<float> AbstractRSSReader::getOddRoundingErrors()
{
    return m_oddRoundingErrors;
}

std::vector<float> AbstractRSSReader::getEvenRoundingErrors()
{
    return m_evenRoundingErrors;
}

std::vector<int> AbstractRSSReader::getOddCounts()
{
    return m_oddCounts;
}

int AbstractRSSReader::parseFinderValue(std::vector<int> counters, std::vector<std::vector<int> > finderPatterns)
{
    for (int value = 0; value < finderPatterns.size(); value++) {
        if (patternMatchVariance(counters, finderPatterns[value], MAX_INDIVIDUAL_VARIANCE) <
                MAX_AVG_VARIANCE) {
            return value;
        }
    }
    throw NotFoundException();
}

void AbstractRSSReader::increment(std::vector<int> array, std::vector<float> errors) {
    int index = 0;
    float biggestError = errors[0];
    for (int i = 1; i < array.size(); i++) {
        if (errors[i] > biggestError) {
            biggestError = errors[i];
            index = i;
        }
    }
    array[index]++;
}

void AbstractRSSReader::decrement(std::vector<int> array, std::vector<float> errors) {
    int index = 0;
    float biggestError = errors[0];
    for (int i = 1; i < array.size(); i++) {
        if (errors[i] < biggestError) {
            biggestError = errors[i];
            index = i;
        }
    }
    array[index]--;
}

bool AbstractRSSReader::isFinderPattern(std::vector<int> counters) {
    int firstTwoSum = counters[0] + counters[1];
    int sum = firstTwoSum + counters[2] + counters[3];
    float ratio = firstTwoSum / (float) sum;
    if (ratio >= MIN_FINDER_PATTERN_RATIO && ratio <= MAX_FINDER_PATTERN_RATIO) {
        // passes ratio test in spec, but see if the counts are unreasonable
        int minCounter = INT_MAX;
        int maxCounter = INT_MIN;
        for (int counter : counters) {
            if (counter > maxCounter) {
                maxCounter = counter;
            }
            if (counter < minCounter) {
                minCounter = counter;
            }
        }
        return maxCounter < 10 * minCounter;
    }
    return false;
}


}
}
}
