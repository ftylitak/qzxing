#include <QCoreApplication>
#include <EncodeValidator.h>

#include "DecodeValidator.h"

int main(int argc, char *argv[])
{
    DecodeValidator decodeValidator;
    decodeValidator.executeTests("../../resources/");

    zxing::qrcode::tests::EncodeValidator encodeValidator;
    encodeValidator.Execute();
}

