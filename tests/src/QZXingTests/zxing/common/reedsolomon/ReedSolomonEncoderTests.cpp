#include "ReedSolomonEncoderTests.h"
#include "zxing/common/reedsolomon/ReedSolomonEncoder.h"
#include "zxing/common/reedsolomon/ReedSolomonDecoder.h"

namespace zxing{
namespace tests{

const int ReedSolomonTests::DECODER_RANDOM_TEST_ITERATIONS = 3;
const int ReedSolomonTests::DECODER_TEST_ITERATIONS = 10;

ReedSolomonTests::ReedSolomonTests()
{

}

void ReedSolomonTests::execute()
{
    testQRCode();
}

void ReedSolomonTests::testQRCode()
{
    // Test case from example given in ISO 18004, Annex I
    testEncodeDecode(GenericGF::QR_CODE_FIELD_256, {
        0x10, 0x20, 0x0C, 0x56, 0x61, 0x80, 0xEC, 0x11,
        0xEC, 0x11, 0xEC, 0x11, 0xEC, 0x11, 0xEC, 0x11
        },
        {0xA5, 0x24, 0xD4, 0xC1, 0xED, 0x36, 0xC7, 0x87,
        0x2C, 0x55});

    testEncodeDecode(GenericGF::QR_CODE_FIELD_256, {
        0x72, 0x67, 0x2F, 0x77, 0x69, 0x6B, 0x69, 0x2F,
        0x4D, 0x61, 0x69, 0x6E, 0x5F, 0x50, 0x61, 0x67,
        0x65, 0x3B, 0x3B, 0x00, 0xEC, 0x11, 0xEC, 0x11,
        0xEC, 0x11, 0xEC, 0x11, 0xEC, 0x11, 0xEC, 0x11 },
        {0xD8, 0xB8, 0xEF, 0x14, 0xEC, 0xD0, 0xCC, 0x85,
        0x73, 0x40, 0x0B, 0xB5, 0x5A, 0xB8, 0x8B, 0x2E,
        0x08, 0x62 });
    // real life test cases
    // synthetic test cases - suspended for now
//    testEncodeDecodeRandom(GenericGF::QR_CODE_FIELD_256, 10, 240);
//    testEncodeDecodeRandom(GenericGF::QR_CODE_FIELD_256, 128, 127);
//    testEncodeDecodeRandom(GenericGF::QR_CODE_FIELD_256, 220, 35);
  }

void ReedSolomonTests::corrupt(std::vector<zxing::byte> &received, int howMany, int max)
{
    std::vector<bool> corrupted(received.size(), false);
    for (int j = 0; j < howMany; j++) {
        int location = generateRandomNumber(received.size());
        int value = generateRandomNumber(max);
        if (corrupted[location] || received[location] == value) {
            j--;
        } else {
            corrupted[location] = true;
            received[location] = value;
        }
    }
}

void ReedSolomonTests::testEncodeDecodeRandom(QSharedPointer<GenericGF> field, int dataSize, int ecSize)
{
    assertTrue(dataSize > 0 && dataSize <= field->getSize() - 3); /*"Invalid data size for " + field, */
    assertTrue(ecSize > 0 && ecSize + dataSize <= field->getSize()); /*"Invalid ECC size for " + field, */
    ReedSolomonEncoder encoder(field);
    std::vector<zxing::byte> message;//(dataSize + ecSize);
    std::vector<zxing::byte> dataWords(dataSize);
    std::vector<zxing::byte> ecWords(ecSize);
    initializeRandom();
    int iterations = field->getSize() > 256 ? 1 : DECODER_RANDOM_TEST_ITERATIONS;
    for (int i = 0; i < iterations; i++) {
        // generate random data
        for (int k = 0; k < dataSize; k++) {
            dataWords[k] = generateRandomNumber(field->getSize());
        }
        // generate ECC words
        message = dataWords;
        encoder.encode(message, ecWords.size());
        message.insert(std::end(message), std::begin(ecWords), std::end(ecWords));
        // check to see if Decoder can fix up to ecWords/2 random errors
        testDecoder(field, dataWords, ecWords);
    }
}

void ReedSolomonTests::testEncodeDecode(QSharedPointer<GenericGF> field,
                      const std::vector<zxing::byte> &dataWords,
                      const std::vector<zxing::byte> &ecWords)
{
    testEncoder(field, dataWords, ecWords);
    testDecoder(field, dataWords, ecWords);
}

void ReedSolomonTests::testEncoder(QSharedPointer<GenericGF> field,
                                  const std::vector<zxing::byte> &dataWords,
                                  const std::vector<zxing::byte> &ecWords)
{
    ReedSolomonEncoder encoder(field);
    std::vector<zxing::byte> messageExpected;
    std::vector<zxing::byte> message(dataWords);

    messageExpected = dataWords;
    messageExpected.insert(std::end(messageExpected), std::begin(ecWords), std::end(ecWords));

    encoder.encode(message, ecWords.size());
    assertDataEquals("",//"Encode in " + field + " (" + dataWords.size() + ',' + ecWords.size() + ") failed",
                     messageExpected, message);
  }

void ReedSolomonTests::testDecoder(QSharedPointer<GenericGF> field,
                                   const std::vector<zxing::byte> &dataWords,
                                   const std::vector<zxing::byte> &ecWords) {
    ReedSolomonDecoder decoder(field);
    std::vector<zxing::byte> message;
    std::vector<zxing::byte> referenceMessage;

    int maxErrors = ecWords.size() / 2;
    initializeRandom();
    int iterations = field->getSize() > 256 ? 1 : DECODER_TEST_ITERATIONS;

    referenceMessage = dataWords;
    referenceMessage.insert(std::end(referenceMessage), std::begin(ecWords), std::end(ecWords));

    for (int j = 0; j < iterations; j++) {
        for (int i = 0; i < int(ecWords.size()); i++) {
            if (i > 10 && i < int(ecWords.size()) / 2 - 10) {
                // performance improvement - skip intermediate cases in long-running tests
                i += ecWords.size() / 10;
            }

            message = referenceMessage;
            corrupt(message, i, field->getSize());

            QSharedPointer<std::vector<int>> messageArrayRef(new std::vector<int>(message.size()));
            for(int i=0; i<int(message.size()); i++)
                (*messageArrayRef)[i] = message[i];

            try {
                decoder.decode(messageArrayRef, ecWords.size());
            } catch(zxing::Exception &e) {
                // fail only if maxErrors exceeded
                assertTrue(i > maxErrors); /*"Decode in " + field + " (" + dataWords.length + ',' + ecWords.length + ") failed at " + i + " errors: " + e,*/
                // else stop
                break;
            }

            if (i < maxErrors) {
                //"Decode in " + field + " (" + dataWords.size() + ',' + ecWords.size() + ") failed at " + i + " errors"
                assertDataEquals("decoded data error",referenceMessage, messageArrayRef);
            }
        }
    }
}

}
}
