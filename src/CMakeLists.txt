cmake_minimum_required(VERSION 3.2)
project(QZXing)

find_package(Qt5 REQUIRED Core)
find_package(Qt5 REQUIRED Network)
find_package(Qt5 REQUIRED Xml)
find_package(Qt5 REQUIRED Multimedia)
find_package(Qt5 REQUIRED MultimediaWidgets Widgets)
find_package(Qt5 REQUIRED Svg Quick QuickControls2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/bigint
    ${PROJECT_SOURCE_DIR}/bigint/ChangeLog
    ${PROJECT_SOURCE_DIR}/bigint/README
    ${PROJECT_SOURCE_DIR}/win32
    ${PROJECT_SOURCE_DIR}/win32/zxing
    ${PROJECT_SOURCE_DIR}/win32/zxing/msvc
    ${PROJECT_SOURCE_DIR}/zxing
    ${PROJECT_SOURCE_DIR}/zxing/aztec
    ${PROJECT_SOURCE_DIR}/zxing/aztec/decoder
    ${PROJECT_SOURCE_DIR}/zxing/aztec/detector
    ${PROJECT_SOURCE_DIR}/zxing/common
    ${PROJECT_SOURCE_DIR}/zxing/common/detector
    ${PROJECT_SOURCE_DIR}/zxing/common/reedsolomon
    ${PROJECT_SOURCE_DIR}/zxing/datamatrix
    ${PROJECT_SOURCE_DIR}/zxing/datamatrix/decoder
    ${PROJECT_SOURCE_DIR}/zxing/datamatrix/detector
    ${PROJECT_SOURCE_DIR}/zxing/multi
    ${PROJECT_SOURCE_DIR}/zxing/multi/qrcode
    ${PROJECT_SOURCE_DIR}/zxing/multi/qrcode/detector
    ${PROJECT_SOURCE_DIR}/zxing/oned
    ${PROJECT_SOURCE_DIR}/zxing/pdf417
    ${PROJECT_SOURCE_DIR}/zxing/pdf417/decoder
    ${PROJECT_SOURCE_DIR}/zxing/pdf417/decoder/ec
    ${PROJECT_SOURCE_DIR}/zxing/pdf417/detector
    ${PROJECT_SOURCE_DIR}/zxing/qrcode
    ${PROJECT_SOURCE_DIR}/zxing/qrcode/decoder
    ${PROJECT_SOURCE_DIR}/zxing/qrcode/detector
    ${PROJECT_SOURCE_DIR}/zxing/qrcode/encoder
)

#set(CMAKE_BUILD_TYPE Debug)
#add_subdirectory(zxing)
add_library(${PROJECT_NAME} STATIC

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

    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigInteger.hh
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigInteger.cc
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigIntegerAlgorithms.hh
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigIntegerAlgorithms.cc
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigIntegerLibrary.hh
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigIntegerUtils.hh
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigIntegerUtils.cc
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigUnsigned.hh
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigUnsigned.cc
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigUnsignedInABase.hh
    ${PROJECT_SOURCE_DIR}/zxing/bigint/BigUnsignedInABase.cc
    ${PROJECT_SOURCE_DIR}/zxing/bigint/NumberlikeArray.hh

# zxing/win32/zxing

    ${PROJECT_SOURCE_DIR}/zxing/win32/zxing/iconv.h
    ${PROJECT_SOURCE_DIR}/zxing/win32/zxing/win_iconv.c
    ${PROJECT_SOURCE_DIR}/zxing/win32/zxing/msvc/stdint.h

# zxing/zxing

    ${PROJECT_SOURCE_DIR}/zxing/zxing/BarcodeFormat.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/BarcodeFormat.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/Binarizer.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/Binarizer.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/BinaryBitmap.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/BinaryBitmap.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/ChecksumException.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/ChecksumException.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/DecodeHints.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/DecodeHints.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/EncodeHint.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/EncodeHint.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/Exception.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/Exception.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/FormatException.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/FormatException.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/IllegalStateException.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/InvertedLuminanceSource.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/InvertedLuminanceSource.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/LuminanceSource.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/LuminanceSource.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/MultiFormatReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/MultiFormatReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/NotFoundException.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/Reader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/Reader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/ReaderException.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/Result.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/Result.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/ResultIO.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/ResultPoint.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/ResultPoint.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/ResultPointCallback.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/ResultPointCallback.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/UnsupportedEncodingException.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/WriterException.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/ZXing.h

# zxing/zxing/aztec

    ${PROJECT_SOURCE_DIR}/zxing/zxing/aztec/AztecDetectorResult.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/aztec/AztecDetectorResult.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/aztec/AztecReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/aztec/AztecReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/aztec/decoder/AztecDecoder.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/aztec/decoder/Decoder.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/aztec/detector/AztecDetector.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/aztec/detector/Detector.h

# zxing/zxing/common

    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/Array.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/BitArray.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/BitArray.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/BitArrayIO.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/BitMatrix.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/BitMatrix.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/BitSource.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/BitSource.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/CharacterSetECI.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/CharacterSetECI.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/Counted.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/DecoderResult.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/DecoderResult.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/DetectorResult.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/DetectorResult.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/GlobalHistogramBinarizer.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/GlobalHistogramBinarizer.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/GreyscaleLuminanceSource.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/GreyscaleLuminanceSource.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/GreyscaleRotatedLuminanceSource.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/GreyscaleRotatedLuminanceSource.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/GridSampler.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/GridSampler.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/HybridBinarizer.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/HybridBinarizer.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/IllegalArgumentException.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/IllegalArgumentException.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/PerspectiveTransform.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/PerspectiveTransform.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/Point.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/Str.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/Str.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/StringUtils.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/StringUtils.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/Types.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/detector/JavaMath.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/detector/MathUtils.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/detector/MonochromeRectangleDetector.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/detector/MonochromeRectangleDetector.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/detector/WhiteRectangleDetector.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/detector/WhiteRectangleDetector.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/GenericGF.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/GenericGF.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/GenericGFPoly.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/GenericGFPoly.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonEncoder.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonEncoder.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonException.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/common/reedsolomon/ReedSolomonException.h

# zxing/zxing/datamatrix

    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/DataMatrixReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/DataMatrixReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/DataMatrixVersion.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/Version.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/BitMatrixParser.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataBlock.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataMatrixBitMatrixParser.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataMatrixDataBlock.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataMatrixDecodedBitStreamParser.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DataMatrixDecoder.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/DecodedBitStreamParser.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/decoder/Decoder.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/CornerPoint.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/DataMatrixCornerPoint.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/DataMatrixDetector.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/DataMatrixDetectorException.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/Detector.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/datamatrix/detector/DetectorException.h

# zxing/zxing/multi

    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/ByQuadrantReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/ByQuadrantReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/GenericMultipleBarcodeReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/GenericMultipleBarcodeReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/MultipleBarcodeReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/MultipleBarcodeReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/qrcode/QRCodeMultiReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/qrcode/QRCodeMultiReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/qrcode/detector/MultiDetector.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/qrcode/detector/MultiDetector.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h

# zxing/zxing/oned

    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/CodaBarReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/CodaBarReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/Code128Reader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/Code128Reader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/Code39Reader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/Code39Reader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/Code93Reader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/Code93Reader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/EAN13Reader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/EAN13Reader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/EAN8Reader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/EAN8Reader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/ITFReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/ITFReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/MultiFormatOneDReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/MultiFormatOneDReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/MultiFormatUPCEANReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/MultiFormatUPCEANReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/OneDReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/OneDReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/OneDResultPoint.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/OneDResultPoint.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/UPCAReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/UPCAReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/UPCEANReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/UPCEANReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/UPCEReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/oned/UPCEReader.h

# zxing/zxing/pdf417

    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/PDF417Reader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/PDF417Reader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/BitMatrixParser.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/DecodedBitStreamParser.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/Decoder.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/PDF417BitMatrixParser.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/PDF417DecodedBitStreamParser.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/PDF417Decoder.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ErrorCorrection.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ErrorCorrection.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ModulusGF.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ModulusGF.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ModulusPoly.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/decoder/ec/ModulusPoly.h

    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/detector/Detector.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/detector/LinesSampler.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/detector/LinesSampler.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/pdf417/detector/PDF417Detector.cpp

# zxing/zxing/qrcode

    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/ErrorCorrectionLevel.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/FormatInformation.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/QRCodeReader.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/QRCodeReader.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/QRErrorCorrectionLevel.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/QRFormatInformation.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/QRVersion.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/Version.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/BitMatrixParser.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/DataBlock.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/DataMask.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/DecodedBitStreamParser.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/Decoder.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/Mode.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRBitMatrixParser.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRDataBlock.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRDataMask.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRDecodedBitStreamParser.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRDecoder.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/decoder/QRMode.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/AlignmentPattern.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/AlignmentPatternFinder.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/Detector.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/FinderPattern.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/FinderPatternFinder.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/FinderPatternInfo.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRAlignmentPattern.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRAlignmentPatternFinder.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRDetector.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRFinderPattern.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRFinderPatternFinder.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/detector/QRFinderPatternInfo.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/BlockPair.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/ByteMatrix.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/ByteMatrix.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/Encoder.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/MaskUtil.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/MaskUtil.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/MatrixUtil.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/MatrixUtil.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/QRCode.cpp
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/QRCode.h
    ${PROJECT_SOURCE_DIR}/zxing/zxing/qrcode/encoder/QREncoder.cpp

    )

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::Svg
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Multimedia
    Qt5::MultimediaWidgets
    iconv)

file(GLOB PUBLIC_HEADER QZXing.h)

# Change Global Definitions depending on how you want to use the library
target_compile_definitions(${PROJECT_NAME}
  PUBLIC QZXING_LIBRARY
  PUBLIC ZXING_ICONV_CONST
  PUBLIC QZXING_QML
  PUBLIC QZXING_MULTIMEDIA
 # PUBLIC DISABLE_LIBRARY_FEATURES
 )

# Target includes
target_include_directories(${PROJECT_NAME}
  PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
 #   QZXing.h
)

#target_include_directories(Server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../GlobalFiles/include")
