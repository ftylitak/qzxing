#ifndef DECODED_NUMERIC_H
#define DECODED_NUMERIC_H

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

#include <zxing/FormatException.h>
#include "DecodedObject.h"

namespace zxing {

namespace oned {

namespace rss {

/**
 * @author Pablo Orduña, University of Deusto (pablo.orduna@deusto.es)
 * @author Eduardo Castillejo, University of Deusto (eduardo.castillejo@deusto.es)
 */

class DecodedNumeric : public DecodedObject
{

public:
    static const int FNC1 = 10;
    DecodedNumeric(int newPosition, int firstDigit, int secondDigit);

    int getFirstDigit();

    int getSecondDigit();

    int getValue();

    bool isFirstDigitFNC1();

    bool isSecondDigitFNC1();

private:
    int m_firstDigit;
    int m_secondDigit;

};

}
}
}

#endif
