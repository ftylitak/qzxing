#include "FieldParser.h"

namespace zxing {
namespace oned {
namespace rss {

static const int VARIABLE_LENGTH = 99999;

struct DigitData {
    std::string digit;
    int variableLength;
    int length;
};

static const DigitData TWO_DIGIT_DATA_LENGTH[] {
  // "DIGITS", new Integer(LENGTH)
  //    or
  // "DIGITS", VARIABLE_LENGTH, new Integer(MAX_SIZE)

  { "00", 0, 18},
  { "01", 0, 14},
  { "02", 0, 14},

  { "10", VARIABLE_LENGTH, 20},
  { "11", 0, 6},
  { "12", 0, 6},
  { "13", 0, 6},
  { "15", 0, 6},
  { "17", 0, 6},

  { "20", 0, 2},
  { "21", VARIABLE_LENGTH, 20},
  { "22", VARIABLE_LENGTH, 29},

  { "30", VARIABLE_LENGTH, 8},
  { "37", VARIABLE_LENGTH, 8},

  //internal company codes
  { "90", VARIABLE_LENGTH, 30},
  { "91", VARIABLE_LENGTH, 30},
  { "92", VARIABLE_LENGTH, 30},
  { "93", VARIABLE_LENGTH, 30},
  { "94", VARIABLE_LENGTH, 30},
  { "95", VARIABLE_LENGTH, 30},
  { "96", VARIABLE_LENGTH, 30},
  { "97", VARIABLE_LENGTH, 30},
  { "98", VARIABLE_LENGTH, 30},
  { "99", VARIABLE_LENGTH, 30},
};

static const DigitData THREE_DIGIT_DATA_LENGTH[] {
  // Same format as above

  { "240", VARIABLE_LENGTH, 30},
  { "241", VARIABLE_LENGTH, 30},
  { "242", VARIABLE_LENGTH, 6},
  { "250", VARIABLE_LENGTH, 30},
  { "251", VARIABLE_LENGTH, 30},
  { "253", VARIABLE_LENGTH, 17},
  { "254", VARIABLE_LENGTH, 20},

  { "400", VARIABLE_LENGTH, 30},
  { "401", VARIABLE_LENGTH, 30},
  { "402", 0, 17},
  { "403", VARIABLE_LENGTH, 30},
  { "410", 0, 13},
  { "411", 0, 13},
  { "412", 0, 13},
  { "413", 0, 13},
  { "414", 0, 13},
  { "420", VARIABLE_LENGTH, 20},
  { "421", VARIABLE_LENGTH, 15},
  { "422", 0, 3},
  { "423", VARIABLE_LENGTH, 15},
  { "424", 0, 3},
  { "425", 0, 3},
  { "426", 0, 3},
};

static const DigitData THREE_DIGIT_PLUS_DIGIT_DATA_LENGTH[] {
  // Same format as above

  { "310", 0, 6},
  { "311", 0, 6},
  { "312", 0, 6},
  { "313", 0, 6},
  { "314", 0, 6},
  { "315", 0, 6},
  { "316", 0, 6},
  { "320", 0, 6},
  { "321", 0, 6},
  { "322", 0, 6},
  { "323", 0, 6},
  { "324", 0, 6},
  { "325", 0, 6},
  { "326", 0, 6},
  { "327", 0, 6},
  { "328", 0, 6},
  { "329", 0, 6},
  { "330", 0, 6},
  { "331", 0, 6},
  { "332", 0, 6},
  { "333", 0, 6},
  { "334", 0, 6},
  { "335", 0, 6},
  { "336", 0, 6},
  { "340", 0, 6},
  { "341", 0, 6},
  { "342", 0, 6},
  { "343", 0, 6},
  { "344", 0, 6},
  { "345", 0, 6},
  { "346", 0, 6},
  { "347", 0, 6},
  { "348", 0, 6},
  { "349", 0, 6},
  { "350", 0, 6},
  { "351", 0, 6},
  { "352", 0, 6},
  { "353", 0, 6},
  { "354", 0, 6},
  { "355", 0, 6},
  { "356", 0, 6},
  { "357", 0, 6},
  { "360", 0, 6},
  { "361", 0, 6},
  { "362", 0, 6},
  { "363", 0, 6},
  { "364", 0, 6},
  { "365", 0, 6},
  { "366", 0, 6},
  { "367", 0, 6},
  { "368", 0, 6},
  { "369", 0, 6},
  { "390", VARIABLE_LENGTH, 15},
  { "391", VARIABLE_LENGTH, 18},
  { "392", VARIABLE_LENGTH, 15},
  { "393", VARIABLE_LENGTH, 18},
  { "703", VARIABLE_LENGTH, 30},
};

static const DigitData FOUR_DIGIT_DATA_LENGTH[] {
  // Same format as above

  { "7001", 0, 13},
  { "7002", VARIABLE_LENGTH, 30},
  { "7003", 0, 10},

  { "8001", 0, 14},
  { "8002", VARIABLE_LENGTH, 20},
  { "8003", VARIABLE_LENGTH, 30},
  { "8004", VARIABLE_LENGTH, 30},
  { "8005", 0, 6},
  { "8006", 0, 18},
  { "8007", VARIABLE_LENGTH, 30},
  { "8008", VARIABLE_LENGTH, 12},
  { "8018", 0, 18},
  { "8020", VARIABLE_LENGTH, 25},
  { "8100", 0, 6},
  { "8101", 0, 10},
  { "8102", 0, 2},
  { "8110", VARIABLE_LENGTH, 70},
  { "8200", VARIABLE_LENGTH, 70},
};

FieldParser::FieldParser() {
}

String FieldParser::parseFieldsInGeneralPurpose(String rawInformation) {
    if (rawInformation.getText().empty()) {
        return String("");
    }

    // Processing 2-digit AIs

    if (rawInformation.length() < 2) {
        throw NotFoundException();
    }

    String firstTwoDigits(rawInformation.substring(0, 2)->getText());

    for (DigitData dataLength : TWO_DIGIT_DATA_LENGTH) {
        if (dataLength.digit == firstTwoDigits.getText()) {
            if (dataLength.variableLength == VARIABLE_LENGTH) {
                return processVariableAI(2, dataLength.length, rawInformation);
            }
            return processFixedAI(2, dataLength.length, rawInformation);
        }
    }

    if (rawInformation.length() < 3) {
        throw NotFoundException();
    }

    String firstThreeDigits(rawInformation.substring(0, 3)->getText());

    for (DigitData dataLength : THREE_DIGIT_DATA_LENGTH) {
        if (dataLength.digit == firstThreeDigits.getText()) {
            if (dataLength.variableLength == VARIABLE_LENGTH) {
                return processVariableAI(3, dataLength.length, rawInformation);
            }
            return processFixedAI(3, dataLength.length, rawInformation);
        }
    }


    for (DigitData dataLength : THREE_DIGIT_PLUS_DIGIT_DATA_LENGTH) {
        if (dataLength.digit == firstThreeDigits.getText()) {
            if (dataLength.variableLength == VARIABLE_LENGTH) {
                return processVariableAI(4, dataLength.length, rawInformation);
            }
            return processFixedAI(4, dataLength.length, rawInformation);
        }
    }

    if (rawInformation.length() < 4) {
        throw NotFoundException();
    }

    String firstFourDigits(rawInformation.substring(0, 4)->getText());

    for (DigitData dataLength : FOUR_DIGIT_DATA_LENGTH) {
        if (dataLength.digit == firstFourDigits.getText()) {
            if (dataLength.variableLength == VARIABLE_LENGTH) {
                return processVariableAI(4, dataLength.length, rawInformation);
            }
            return processFixedAI(4, dataLength.length, rawInformation);
        }
    }

    throw NotFoundException();
}

String FieldParser::processFixedAI(int aiSize, int fieldSize, String rawInformation)
{
    if (rawInformation.length() < aiSize) {
        throw NotFoundException();
    }

    String ai(rawInformation.substring(0, aiSize)->getText());

    if (rawInformation.length() < aiSize + fieldSize) {
        throw NotFoundException();
    }

    String field(rawInformation.substring(aiSize, aiSize + fieldSize)->getText());
    String remaining(rawInformation.substring(aiSize + fieldSize, 0)->getText());
    String result('(' + ai.getText() + ')' + field.getText());
    String parsedAI = parseFieldsInGeneralPurpose(remaining);
    if (parsedAI.getText() == "") {
        return result;
    } else {
        result.append(parsedAI.getText());
        return result;
    }
}

String FieldParser::processVariableAI(int aiSize, int variableFieldSize, String rawInformation)
{
    String ai(rawInformation.substring(0, aiSize)->getText());
    int maxSize = std::min(rawInformation.length(), aiSize + variableFieldSize);
    String field(rawInformation.substring(aiSize, maxSize)->getText());
    String remaining(rawInformation.substring(maxSize, 0)->getText());
    String result('(' + ai.getText() + ')' + field.getText());
    String parsedAI = parseFieldsInGeneralPurpose(remaining);
    if (parsedAI.getText() == "") {
        return result;
    } else {
        result.append(parsedAI.getText());
        return result;
    }
}

}
}
}
