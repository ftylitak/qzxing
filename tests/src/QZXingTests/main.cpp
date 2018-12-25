#include <QCoreApplication>
#include <EncodeValidator.h>

#include "DecodeValidator.h"

int main(int /*argc*/, char **/*argv[]*/)
{
    DecodeValidator decodeValidator;
    decodeValidator.executeTests("../../resources/");

    zxing::tests::EncodeValidator encodeValidator;
    encodeValidator.execute();
}

