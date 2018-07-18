cmake_minimum_required(VERSION 3.2)
project(QZXing)

find_package(Qt5 REQUIRED Core)
find_package(Qt5 REQUIRED Network)
find_package(Qt5 REQUIRED Xml)
find_package(Qt5 REQUIRED Multimedia)
find_package(Qt5 REQUIRED MultimediaWidgets Widgets)
find_package(Qt5 REQUIRED Svg Quick QuickControls2)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(zxing)
add_library(qzxing STATIC

# root
    CameraImageWrapper.cpp
    CameraImageWrapper.h
    ImageHandler.cpp
    ImageHandler.h
    QZXing.cpp
    QZXing.h
    QZXingFilter.cpp
    QZXingFilter.h
    QZXingImageProvider.cpp
    QZXingImageProvider.h
    QZXing_global.h

# zxing/bigint

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigInteger.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigInteger.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigIntegerAlgorithms.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigIntegerAlgorithms.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigIntegerLibrary.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigIntegerUtils.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigIntegerUtils.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigUnsigned.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigUnsigned.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigUnsignedInABase.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/BigUnsignedInABase.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint/NumberlikeArray.hh

# zxing/win32/zxing

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/win32/zxing/iconv.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/win32/zxing/win_iconv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/win32/zxing/msvc/stdint.h

# zxing/zxing

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/BarcodeFormat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/BarcodeFormat.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/Binarizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/Binarizer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/BinaryBitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/BinaryBitmap.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/ChecksumException.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/ChecksumException.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/DecodeHints.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/DecodeHints.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/EncodeHint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/EncodeHint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/Exception.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/Exception.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/FormatException.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/FormatException.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/IllegalStateException.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/InvertedLuminanceSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/InvertedLuminanceSource.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/LuminanceSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/LuminanceSource.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/MultiFormatReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/MultiFormatReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/NotFoundException.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/Reader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/ReaderException.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/Result.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/Result.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/ResultIO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/ResultPoint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/ResultPoint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/ResultPointCallback.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/ResultPointCallback.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/UnsupportedEncodingException.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/WriterException.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/ZXing.h

# zxing/zxing/aztec

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/aztec/AztecDetectorResult.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/aztec/AztecDetectorResult.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/aztec/AztecReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/aztec/AztecReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/aztec/decoder/AztecDecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/aztec/decoder/Decoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/aztec/detector/AztecDetector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/aztec/detector/Detector.h

# zxing/zxing/common

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/Array.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/BitArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/BitArray.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/BitArrayIO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/BitMatrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/BitMatrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/BitSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/BitSource.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/CharacterSetECI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/CharacterSetECI.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/Counted.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/DecoderResult.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/DecoderResult.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/DetectorResult.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/DetectorResult.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/GlobalHistogramBinarizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/GlobalHistogramBinarizer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/GreyscaleLuminanceSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/GreyscaleLuminanceSource.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/GreyscaleRotatedLuminanceSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/GreyscaleRotatedLuminanceSource.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/GridSampler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/GridSampler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/HybridBinarizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/HybridBinarizer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/IllegalArgumentException.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/IllegalArgumentException.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/PerspectiveTransform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/PerspectiveTransform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/Point.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/Str.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/Str.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/StringUtils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/StringUtils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/Types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/detector/JavaMath.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/detector/MathUtils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/detector/MonochromeRectangleDetector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/detector/MonochromeRectangleDetector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/detector/WhiteRectangleDetector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/detector/WhiteRectangleDetector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/GenericGF.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/GenericGF.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/GenericGFPoly.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/GenericGFPoly.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonEncoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonEncoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonException.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonException.h

# zxing/zxing/datamatrix

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/DataMatrixReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/DataMatrixReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/DataMatrixVersion.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/Version.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/BitMatrixParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataBlock.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataMatrixBitMatrixParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataMatrixDataBlock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataMatrixDecodedBitStreamParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataMatrixDecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DecodedBitStreamParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/Decoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/CornerPoint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/DataMatrixCornerPoint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/DataMatrixDetector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/DataMatrixDetectorException.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/Detector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/DetectorException.h

# zxing/zxing/multi

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/ByQuadrantReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/ByQuadrantReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/GenericMultipleBarcodeReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/GenericMultipleBarcodeReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/MultipleBarcodeReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/MultipleBarcodeReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/qrcode/QRCodeMultiReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/qrcode/QRCodeMultiReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/qrcode/detector/MultiDetector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/qrcode/detector/MultiDetector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h

# zxing/zxing/oned

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/CodaBarReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/CodaBarReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/Code128Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/Code128Reader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/Code39Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/Code39Reader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/Code93Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/Code93Reader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/EAN13Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/EAN13Reader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/EAN8Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/EAN8Reader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/ITFReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/ITFReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/MultiFormatOneDReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/MultiFormatOneDReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/MultiFormatUPCEANReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/MultiFormatUPCEANReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/OneDReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/OneDReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/OneDResultPoint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/OneDResultPoint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/UPCAReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/UPCAReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/UPCEANReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/UPCEANReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/UPCEReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/oned/UPCEReader.h

# zxing/zxing/pdf417

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/PDF417Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/PDF417Reader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/BitMatrixParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/DecodedBitStreamParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/Decoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/PDF417BitMatrixParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/PDF417DecodedBitStreamParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/PDF417Decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ErrorCorrection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ErrorCorrection.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ModulusGF.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ModulusGF.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ModulusPoly.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ModulusPoly.h

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/detector/Detector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/detector/LinesSampler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/detector/LinesSampler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/pdf417/detector/PDF417Detector.cpp

# zxing/zxing/qrcode

    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/ErrorCorrectionLevel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/FormatInformation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/QRCodeReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/QRCodeReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/QRErrorCorrectionLevel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/QRFormatInformation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/QRVersion.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/Version.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/BitMatrixParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/DataBlock.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/DataMask.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/DecodedBitStreamParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/Decoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/Mode.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRBitMatrixParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRDataBlock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRDataMask.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRDecodedBitStreamParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRDecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRMode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/AlignmentPattern.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/AlignmentPatternFinder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/Detector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/FinderPattern.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/FinderPatternFinder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/FinderPatternInfo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRAlignmentPattern.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRAlignmentPatternFinder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRDetector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRFinderPattern.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRFinderPatternFinder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRFinderPatternInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/BlockPair.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/ByteMatrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/ByteMatrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/Encoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/MaskUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/MaskUtil.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/MatrixUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/MatrixUtil.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/QRCode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/QRCode.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/QREncoder.cpp

    )

target_link_libraries(qzxing
    Qt5::Core
    Qt5::Widgets
    Qt5::Svg
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Multimedia
    Qt5::MultimediaWidgets )

file(GLOB PUBLIC_HEADER QZXing.h)

# Change Global Definitions depending on how you want to use the library
target_compile_definitions(qzxing
  PRIVATE -QZXING_LIBRARY
  PRIVATE -ZXING_ICONV_CONST
  PUBLIC  -QZXING_QML
  PUBLIC  -QZXING_MULTIMEDIA
  PUBLIC DISABLE_LIBRARY_FEATURES)

# Target includes
target_include_directories(qzxing
  PUBLIC
        .
    QZXing.h

  PRIVATE

        zxing
        zxing/win32/zxing
        zxing/zxing
)

