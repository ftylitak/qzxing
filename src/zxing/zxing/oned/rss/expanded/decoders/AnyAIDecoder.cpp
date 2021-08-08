#include "AnyAIDecoder.h"

namespace zxing {
namespace oned {
namespace rss {

AnyAIDecoder::AnyAIDecoder(QSharedPointer<BitArray> information)
    : AbstractExpandedDecoder(information)
{

}

String AnyAIDecoder::parseInformation()
{
    String buf("");
    return getGeneralDecoder().decodeAllCodes(buf, HEADER_SIZE);
}

}
}
}
