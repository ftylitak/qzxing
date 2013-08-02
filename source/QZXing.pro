

QT       += core gui

VERSION = 2.2

greaterThan(QT_VERSION, 4.7): QT += declarative

TARGET = QZXing
TEMPLATE = lib

# CONFIG += staticlib

DEFINES += QZXING_LIBRARY \
         ZXING_ICONV_CONST

INCLUDEPATH  += ./ \
    zxing


HEADERS += QZXing_global.h \
    CameraImageWrapper.h \
    imagehandler.h \
    qzxing.h \
    zxing/zxing/ZXing.h \
    zxing/zxing/IllegalStateException.h \
    zxing/zxing/InvertedLuminanceSource.h \
    zxing/zxing/ChecksumException.h \
    zxing/zxing/ResultPointCallback.h \
    zxing/zxing/ResultPoint.h \
    zxing/zxing/Result.h \
    zxing/zxing/ReaderException.h \
    zxing/zxing/Reader.h \
    zxing/zxing/NotFoundException.h \
    zxing/zxing/MultiFormatReader.h \
    zxing/zxing/LuminanceSource.h \
    zxing/zxing/FormatException.h \
    zxing/zxing/Exception.h \
    zxing/zxing/DecodeHints.h \
    zxing/zxing/BinaryBitmap.h \
    zxing/zxing/Binarizer.h \
    zxing/zxing/BarcodeFormat.h \
    zxing/zxing/aztec/AztecReader.h \
    zxing/zxing/aztec/AztecDetectorResult.h \
    zxing/zxing/aztec/decoder/Decoder.h \
    zxing/zxing/aztec/detector/Detector.h \
    zxing/zxing/common/StringUtils.h \
    zxing/zxing/common/Str.h \
    zxing/zxing/common/Point.h \
    zxing/zxing/common/PerspectiveTransform.h \
    zxing/zxing/common/IllegalArgumentException.h \
    zxing/zxing/common/HybridBinarizer.h \
    zxing/zxing/common/GridSampler.h \
    zxing/zxing/common/GreyscaleRotatedLuminanceSource.h \
    zxing/zxing/common/GreyscaleLuminanceSource.h \
    zxing/zxing/common/GlobalHistogramBinarizer.h \
    zxing/zxing/common/DetectorResult.h \
    zxing/zxing/common/DecoderResult.h \
    zxing/zxing/common/Counted.h \
    zxing/zxing/common/CharacterSetECI.h \
    zxing/zxing/common/BitSource.h \
    zxing/zxing/common/BitMatrix.h \
    zxing/zxing/common/BitArray.h \
    zxing/zxing/common/Array.h \
    zxing/zxing/common/detector/MathUtils.h \
    zxing/zxing/common/detector/JavaMath.h \
    zxing/zxing/common/detector/WhiteRectangleDetector.h \
    zxing/zxing/common/detector/MonochromeRectangleDetector.h \
    zxing/zxing/common/reedsolomon/ReedSolomonException.h \
    zxing/zxing/common/reedsolomon/ReedSolomonDecoder.h \
    zxing/zxing/common/reedsolomon/GenericGFPoly.h \
    zxing/zxing/common/reedsolomon/GenericGF.h \
    zxing/zxing/datamatrix/Version.h \
    zxing/zxing/datamatrix/DataMatrixReader.h \
    zxing/zxing/datamatrix/decoder/Decoder.h \
    zxing/zxing/datamatrix/decoder/DecodedBitStreamParser.h \
    zxing/zxing/datamatrix/decoder/DataBlock.h \
    zxing/zxing/datamatrix/decoder/BitMatrixParser.h \
    zxing/zxing/datamatrix/detector/DetectorException.h \
    zxing/zxing/datamatrix/detector/Detector.h \
    zxing/zxing/datamatrix/detector/CornerPoint.h \
    zxing/zxing/oned/UPCEReader.h \
    zxing/zxing/oned/UPCEANReader.h \
    zxing/zxing/oned/UPCAReader.h \
    zxing/zxing/oned/OneDResultPoint.h \
    zxing/zxing/oned/OneDReader.h \
    zxing/zxing/oned/MultiFormatUPCEANReader.h \
    zxing/zxing/oned/MultiFormatOneDReader.h \
    zxing/zxing/oned/ITFReader.h \
    zxing/zxing/oned/EAN13Reader.h \
    zxing/zxing/oned/EAN8Reader.h \
    zxing/zxing/oned/Code128Reader.h \
    zxing/zxing/oned/Code39Reader.h \
    zxing/zxing/oned/CodaBarReader.h \
    zxing/zxing/oned/Code93Reader.h \
    zxing/zxing/qrcode/Version.h \
    zxing/zxing/qrcode/QRCodeReader.h \
    zxing/zxing/qrcode/FormatInformation.h \
    zxing/zxing/qrcode/ErrorCorrectionLevel.h \
    zxing/zxing/qrcode/decoder/Mode.h \
    zxing/zxing/qrcode/decoder/Decoder.h \
    zxing/zxing/qrcode/decoder/DecodedBitStreamParser.h \
    zxing/zxing/qrcode/decoder/DataMask.h \
    zxing/zxing/qrcode/decoder/DataBlock.h \
    zxing/zxing/qrcode/decoder/BitMatrixParser.h \
    zxing/zxing/qrcode/detector/FinderPatternInfo.h \
    zxing/zxing/qrcode/detector/FinderPatternFinder.h \
    zxing/zxing/qrcode/detector/FinderPattern.h \
    zxing/zxing/qrcode/detector/Detector.h \
    zxing/zxing/qrcode/detector/AlignmentPatternFinder.h \
    zxing/zxing/qrcode/detector/AlignmentPattern.h \
    zxing/zxing/multi/MultipleBarcodeReader.h \
    zxing/zxing/multi/GenericMultipleBarcodeReader.h \
    zxing/zxing/multi/ByQuadrantReader.h \
    zxing/zxing/multi/qrcode/QRCodeMultiReader.h \
    zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h \
    zxing/zxing/multi/qrcode/detector/MultiDetector.h \
    zxing/zxing/pdf417/decoder/ec/ErrorCorrection.h \
    zxing/zxing/pdf417/decoder/ec/ModulusGF.h \
    zxing/zxing/pdf417/decoder/ec/ModulusPoly.h \
    zxing/zxing/pdf417/decoder/BitMatrixParser.h \
    zxing/zxing/pdf417/decoder/DecodedBitStreamParser.h \
    zxing/zxing/pdf417/decoder/Decoder.h \
    zxing/zxing/pdf417/detector/Detector.h \
    zxing/zxing/pdf417/detector/LinesSampler.h \
    zxing/zxing/pdf417/PDF417Reader.h \
    zxing/bigint/NumberlikeArray.hh \
    zxing/bigint/BigUnsignedInABase.hh \
    zxing/bigint/BigUnsigned.hh \
    zxing/bigint/BigIntegerUtils.hh \
    zxing/bigint/BigIntegerLibrary.hh \
    zxing/bigint/BigIntegerAlgorithms.hh \
    zxing/bigint/BigInteger.hh 

SOURCES += CameraImageWrapper.cpp \
    qzxing.cpp \
    imagehandler.cpp \
    zxing/zxing/ResultIO.cpp \
    zxing/zxing/InvertedLuminanceSource.cpp \
    zxing/zxing/ChecksumException.cpp \
    zxing/zxing/ResultPointCallback.cpp \
    zxing/zxing/ResultPoint.cpp \
    zxing/zxing/Result.cpp \
    zxing/zxing/Reader.cpp \
    zxing/zxing/MultiFormatReader.cpp \
    zxing/zxing/LuminanceSource.cpp \
    zxing/zxing/FormatException.cpp \
    zxing/zxing/Exception.cpp \
    zxing/zxing/DecodeHints.cpp \
    zxing/zxing/BinaryBitmap.cpp \
    zxing/zxing/Binarizer.cpp \
    zxing/zxing/BarcodeFormat.cpp \
    zxing/zxing/aztec/AztecReader.cpp \
    zxing/zxing/aztec/AztecDetectorResult.cpp \
    zxing/zxing/common/StringUtils.cpp \
    zxing/zxing/common/Str.cpp \
    zxing/zxing/common/PerspectiveTransform.cpp \
    zxing/zxing/common/IllegalArgumentException.cpp \
    zxing/zxing/common/HybridBinarizer.cpp \
    zxing/zxing/common/GridSampler.cpp \
    zxing/zxing/common/GreyscaleRotatedLuminanceSource.cpp \
    zxing/zxing/common/GreyscaleLuminanceSource.cpp \
    zxing/zxing/common/GlobalHistogramBinarizer.cpp \
    zxing/zxing/common/DetectorResult.cpp \
    zxing/zxing/common/DecoderResult.cpp \
    zxing/zxing/common/CharacterSetECI.cpp \
    zxing/zxing/common/BitSource.cpp \
    zxing/zxing/common/BitMatrix.cpp \
    zxing/zxing/common/BitArray.cpp \
    zxing/zxing/common/BitArrayIO.cpp \
    zxing/zxing/common/detector/WhiteRectangleDetector.cpp \
    zxing/zxing/common/detector/MonochromeRectangleDetector.cpp \
    zxing/zxing/common/reedsolomon/ReedSolomonException.cpp \
    zxing/zxing/common/reedsolomon/ReedSolomonDecoder.cpp \
    zxing/zxing/common/reedsolomon/GenericGFPoly.cpp \
    zxing/zxing/common/reedsolomon/GenericGF.cpp \
    zxing/zxing/datamatrix/DataMatrixReader.cpp \
    zxing/zxing/oned/UPCEReader.cpp \
    zxing/zxing/oned/UPCEANReader.cpp \
    zxing/zxing/oned/UPCAReader.cpp \
    zxing/zxing/oned/OneDResultPoint.cpp \
    zxing/zxing/oned/OneDReader.cpp \
    zxing/zxing/oned/MultiFormatUPCEANReader.cpp \
    zxing/zxing/oned/MultiFormatOneDReader.cpp \
    zxing/zxing/oned/ITFReader.cpp \
    zxing/zxing/oned/EAN13Reader.cpp \
    zxing/zxing/oned/EAN8Reader.cpp \
    zxing/zxing/oned/Code128Reader.cpp \
    zxing/zxing/oned/Code39Reader.cpp \
    zxing/zxing/oned/CodaBarReader.cpp \
    zxing/zxing/oned/Code93Reader.cpp \
    zxing/zxing/qrcode/QRCodeReader.cpp \
    zxing/zxing/multi/MultipleBarcodeReader.cpp \
    zxing/zxing/multi/GenericMultipleBarcodeReader.cpp \
    zxing/zxing/multi/ByQuadrantReader.cpp \
    zxing/zxing/multi/qrcode/QRCodeMultiReader.cpp \
    zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.cpp \
    zxing/zxing/multi/qrcode/detector/MultiDetector.cpp \
    zxing/zxing/aztec/decoder/AztecDecoder.cpp \
    zxing/zxing/aztec/detector/AztecDetector.cpp \
    zxing/zxing/datamatrix/DataMatrixVersion.cpp \
    zxing/zxing/datamatrix/decoder/DataMatrixDecoder.cpp \
    zxing/zxing/datamatrix/decoder/DataMatrixBitMatrixParser.cpp \
    zxing/zxing/datamatrix/decoder/DataMatrixDataBlock.cpp \
    zxing/zxing/datamatrix/decoder/DataMatrixDecodedBitStreamParser.cpp \
    zxing/zxing/datamatrix/detector/DataMatrixCornerPoint.cpp \
    zxing/zxing/datamatrix/detector/DataMatrixDetector.cpp \
    zxing/zxing/datamatrix/detector/DataMatrixDetectorException.cpp \
    zxing/zxing/qrcode/decoder/QRBitMatrixParser.cpp \
    zxing/zxing/qrcode/decoder/QRDataBlock.cpp \
    zxing/zxing/qrcode/decoder/QRDataMask.cpp \
    zxing/zxing/qrcode/decoder/QRDecodedBitStreamParser.cpp \
    zxing/zxing/qrcode/decoder/QRDecoder.cpp \
    zxing/zxing/qrcode/decoder/QRMode.cpp \
    zxing/zxing/qrcode/detector/QRAlignmentPattern.cpp \
    zxing/zxing/qrcode/detector/QRAlignmentPatternFinder.cpp \
    zxing/zxing/qrcode/detector/QRDetector.cpp \
    zxing/zxing/qrcode/detector/QRFinderPattern.cpp \
    zxing/zxing/qrcode/detector/QRFinderPatternFinder.cpp \
    zxing/zxing/qrcode/detector/QRFinderPatternInfo.cpp \
    zxing/zxing/qrcode/QRVersion.cpp \
    zxing/zxing/qrcode/QRFormatInformation.cpp \
    zxing/zxing/qrcode/QRErrorCorrectionLevel.cpp \
    zxing/zxing/pdf417/decoder/ec/ErrorCorrection.cpp \
    zxing/zxing/pdf417/decoder/ec/ModulusGF.cpp \
    zxing/zxing/pdf417/decoder/ec/ModulusPoly.cpp \
    zxing/zxing/pdf417/decoder/PDF417BitMatrixParser.cpp \
    zxing/zxing/pdf417/decoder/PDF417DecodedBitStreamParser.cpp \
    zxing/zxing/pdf417/decoder/PDF417Decoder.cpp \
    zxing/zxing/pdf417/detector/PDF417Detector.cpp \
    zxing/zxing/pdf417/detector/LinesSampler.cpp \
    zxing/zxing/pdf417/PDF417Reader.cpp \
    zxing/bigint/BigUnsignedInABase.cc \
    zxing/bigint/BigUnsigned.cc \
    zxing/bigint/BigIntegerUtils.cc \
    zxing/bigint/BigIntegerAlgorithms.cc \
    zxing/bigint/BigInteger.cc 

symbian {
    TARGET.UID3 = 0xE618743C
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = QZXing.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
#    TARGET.CAPABILITY = All -TCB -AllFiles -DRM
    TARGET.CAPABILITY += NetworkServices \
        ReadUserData \
        WriteUserData \
        LocalServices \
        UserEnvironment \
        Location
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }

    DEFINES += NOFMAXL
    INSTALLS += target
}

win32-msvc*{

    INCLUDEPATH += zxing/win32/zxing \
                zxing/win32/zxing/stdint
    HEADERS += zxing/win32/zxing/stdint/stdint.h \
				zxing/win32/zxing/iconv.h
	SOURCES += zxing/win32/zxing/win_iconv.c
}

win32-g++{
    INCLUDEPATH += $$PWD/zxing/win32/zxing
    HEADERS += $$PWD/zxing/win32/zxing/iconv.h
    SOURCES += $$PWD/zxing/win32/zxing/win_iconv.c
}

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog


