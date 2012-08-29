QT       += core gui

greaterThan(QT_VERSION, 4.7): QT += declarative

DEFINES += QZXING_LIBRARY \
         ZXING_ICONV_CONST
		 
INCLUDEPATH  += $$PWD

HEADERS += $$PWD/QZXing_global.h \
    $$PWD/CameraImageWrapper.h \
    $$PWD/imagehandler.h \
    $$PWD/qzxing.h \
    $$PWD/zxing/ResultPointCallback.h \
    $$PWD/zxing/ResultPoint.h \
    $$PWD/zxing/Result.h \
    $$PWD/zxing/ReaderException.h \
    $$PWD/zxing/Reader.h \
    $$PWD/zxing/NotFoundException.h \
    $$PWD/zxing/MultiFormatReader.h \
    $$PWD/zxing/LuminanceSource.h \
    $$PWD/zxing/FormatException.h \
    $$PWD/zxing/Exception.h \
    $$PWD/zxing/DecodeHints.h \
    $$PWD/zxing/BinaryBitmap.h \
    $$PWD/zxing/Binarizer.h \
    $$PWD/zxing/BarcodeFormat.h \
    $$PWD/zxing/aztec/AztecReader.h \
    $$PWD/zxing/aztec/AztecDetectorResult.h \
    $$PWD/zxing/aztec/decoder/Decoder.h \
    $$PWD/zxing/aztec/detector/Detector.h \
    $$PWD/zxing/common/StringUtils.h \
    $$PWD/zxing/common/Str.h \
    $$PWD/zxing/common/Point.h \
    $$PWD/zxing/common/PerspectiveTransform.h \
    $$PWD/zxing/common/IllegalArgumentException.h \
    $$PWD/zxing/common/HybridBinarizer.h \
    $$PWD/zxing/common/GridSampler.h \
    $$PWD/zxing/common/GreyscaleRotatedLuminanceSource.h \
    $$PWD/zxing/common/GreyscaleLuminanceSource.h \
    $$PWD/zxing/common/GlobalHistogramBinarizer.h \
    $$PWD/zxing/common/EdgeDetector.h \
    $$PWD/zxing/common/DetectorResult.h \
    $$PWD/zxing/common/DecoderResult.h \
    $$PWD/zxing/common/Counted.h \
    $$PWD/zxing/common/CharacterSetECI.h \
    $$PWD/zxing/common/BitSource.h \
    $$PWD/zxing/common/BitMatrix.h \
    $$PWD/zxing/common/BitArray.h \
    $$PWD/zxing/common/Array.h \
    $$PWD/zxing/common/detector/WhiteRectangleDetector.h \
    $$PWD/zxing/common/detector/MonochromeRectangleDetector.h \
    $$PWD/zxing/common/reedsolomon/ReedSolomonException.h \
    $$PWD/zxing/common/reedsolomon/ReedSolomonDecoder.h \
    $$PWD/zxing/common/reedsolomon/GenericGFPoly.h \
    $$PWD/zxing/common/reedsolomon/GenericGF.h \
    $$PWD/zxing/datamatrix/Version.h \
    $$PWD/zxing/datamatrix/DataMatrixReader.h \
    $$PWD/zxing/datamatrix/decoder/Decoder.h \
    $$PWD/zxing/datamatrix/decoder/DecodedBitStreamParser.h \
    $$PWD/zxing/datamatrix/decoder/DataBlock.h \
    $$PWD/zxing/datamatrix/decoder/BitMatrixParser.h \
    $$PWD/zxing/datamatrix/detector/MonochromeRectangleDetector.h \
    $$PWD/zxing/datamatrix/detector/DetectorException.h \
    $$PWD/zxing/datamatrix/detector/Detector.h \
    $$PWD/zxing/datamatrix/detector/CornerPoint.h \
    $$PWD/zxing/oned/UPCEReader.h \
    $$PWD/zxing/oned/UPCEANReader.h \
    $$PWD/zxing/oned/UPCAReader.h \
    $$PWD/zxing/oned/OneDResultPoint.h \
    $$PWD/zxing/oned/OneDReader.h \
    $$PWD/zxing/oned/MultiFormatUPCEANReader.h \
    $$PWD/zxing/oned/MultiFormatOneDReader.h \
    $$PWD/zxing/oned/ITFReader.h \
    $$PWD/zxing/oned/EAN13Reader.h \
    $$PWD/zxing/oned/EAN8Reader.h \
    $$PWD/zxing/oned/Code128Reader.h \
    $$PWD/zxing/oned/Code39Reader.h \
    $$PWD/zxing/qrcode/Version.h \
    $$PWD/zxing/qrcode/QRCodeReader.h \
    $$PWD/zxing/qrcode/FormatInformation.h \
    $$PWD/zxing/qrcode/ErrorCorrectionLevel.h \
    $$PWD/zxing/qrcode/decoder/Mode.h \
    $$PWD/zxing/qrcode/decoder/Decoder.h \
    $$PWD/zxing/qrcode/decoder/DecodedBitStreamParser.h \
    $$PWD/zxing/qrcode/decoder/DataMask.h \
    $$PWD/zxing/qrcode/decoder/DataBlock.h \
    $$PWD/zxing/qrcode/decoder/BitMatrixParser.h \
    $$PWD/zxing/qrcode/detector/QREdgeDetector.h \
    $$PWD/zxing/qrcode/detector/FinderPatternInfo.h \
    $$PWD/zxing/qrcode/detector/FinderPatternFinder.h \
    $$PWD/zxing/qrcode/detector/FinderPattern.h \
    $$PWD/zxing/qrcode/detector/Detector.h \
    $$PWD/zxing/qrcode/detector/AlignmentPatternFinder.h \
    $$PWD/zxing/qrcode/detector/AlignmentPattern.h \
    $$PWD/zxing/multi/MultipleBarcodeReader.h \
    $$PWD/zxing/multi/GenericMultipleBarcodeReader.h \
    $$PWD/zxing/multi/ByQuadrantReader.h \
    $$PWD/zxing/multi/qrcode/QRCodeMultiReader.h \
    $$PWD/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h \
    $$PWD/zxing/multi/qrcode/detector/MultiDetector.h

SOURCES += $$PWD/CameraImageWrapper.cpp \
    $$PWD/qzxing.cpp \
    $$PWD/imagehandler.cpp \
    $$PWD/zxing/ResultPointCallback.cpp \
    $$PWD/zxing/ResultPoint.cpp \
    $$PWD/zxing/Result.cpp \
    $$PWD/zxing/ReaderException.cpp \
    $$PWD/zxing/Reader.cpp \
    $$PWD/zxing/NotFoundException.cpp \
    $$PWD/zxing/MultiFormatReader.cpp \
    $$PWD/zxing/LuminanceSource.cpp \
    $$PWD/zxing/FormatException.cpp \
    $$PWD/zxing/Exception.cpp \
    $$PWD/zxing/DecodeHints.cpp \
    $$PWD/zxing/BinaryBitmap.cpp \
    $$PWD/zxing/Binarizer.cpp \
    $$PWD/zxing/BarcodeFormat.cpp \
    $$PWD/zxing/aztec/AztecReader.cpp \
    $$PWD/zxing/aztec/AztecDetectorResult.cpp \
    $$PWD/zxing/common/StringUtils.cpp \
    $$PWD/zxing/common/Str.cpp \
    $$PWD/zxing/common/PerspectiveTransform.cpp \
    $$PWD/zxing/common/IllegalArgumentException.cpp \
    $$PWD/zxing/common/HybridBinarizer.cpp \
    $$PWD/zxing/common/GridSampler.cpp \
    $$PWD/zxing/common/GreyscaleRotatedLuminanceSource.cpp \
    $$PWD/zxing/common/GreyscaleLuminanceSource.cpp \
    $$PWD/zxing/common/GlobalHistogramBinarizer.cpp \
    $$PWD/zxing/common/EdgeDetector.cpp \
    $$PWD/zxing/common/DetectorResult.cpp \
    $$PWD/zxing/common/DecoderResult.cpp \
    $$PWD/zxing/common/Counted.cpp \
    $$PWD/zxing/common/CharacterSetECI.cpp \
    $$PWD/zxing/common/BitSource.cpp \
    $$PWD/zxing/common/BitMatrix.cpp \
    $$PWD/zxing/common/BitArray.cpp \
    $$PWD/zxing/common/Array.cpp \
    $$PWD/zxing/common/detector/WhiteRectangleDetector.cpp \
    $$PWD/zxing/common/detector/MonochromeRectangleDetector.cpp \
    $$PWD/zxing/common/reedsolomon/ReedSolomonException.cpp \
    $$PWD/zxing/common/reedsolomon/ReedSolomonDecoder.cpp \
    $$PWD/zxing/common/reedsolomon/GenericGFPoly.cpp \
    $$PWD/zxing/common/reedsolomon/GenericGF.cpp \
    $$PWD/zxing/datamatrix/DataMatrixReader.cpp \
    $$PWD/zxing/oned/UPCEReader.cpp \
    $$PWD/zxing/oned/UPCEANReader.cpp \
    $$PWD/zxing/oned/UPCAReader.cpp \
    $$PWD/zxing/oned/OneDResultPoint.cpp \
    $$PWD/zxing/oned/OneDReader.cpp \
    $$PWD/zxing/oned/MultiFormatUPCEANReader.cpp \
    $$PWD/zxing/oned/MultiFormatOneDReader.cpp \
    $$PWD/zxing/oned/ITFReader.cpp \
    $$PWD/zxing/oned/EAN13Reader.cpp \
    $$PWD/zxing/oned/EAN8Reader.cpp \
    $$PWD/zxing/oned/Code128Reader.cpp \
    $$PWD/zxing/oned/Code39Reader.cpp \
    $$PWD/zxing/qrcode/QRCodeReader.cpp \
    $$PWD/zxing/qrcode/detector/QREdgeDetector.cpp \
    $$PWD/zxing/multi/MultipleBarcodeReader.cpp \
    $$PWD/zxing/multi/GenericMultipleBarcodeReader.cpp \
    $$PWD/zxing/multi/ByQuadrantReader.cpp \
    $$PWD/zxing/multi/qrcode/QRCodeMultiReader.cpp \
    $$PWD/zxing/multi/qrcode/detector/MultiFinderPatternFinder.cpp \
    $$PWD/zxing/multi/qrcode/detector/MultiDetector.cpp \
    $$PWD/zxing/aztec/decoder/AztecDecoder.cpp \
    $$PWD/zxing/aztec/detector/AztecDetector.cpp \
    $$PWD/zxing/datamatrix/DataMatrixVersion.cpp \
    $$PWD/zxing/datamatrix/decoder/DataMatrixDecoder.cpp \
    $$PWD/zxing/datamatrix/decoder/DataMatrixBitMatrixParser.cpp \
    $$PWD/zxing/datamatrix/decoder/DataMatrixDataBlock.cpp \
    $$PWD/zxing/datamatrix/decoder/DataMatrixDecodedBitStreamParser.cpp \
    $$PWD/zxing/datamatrix/detector/DataMatrixCornerPoint.cpp \
    $$PWD/zxing/datamatrix/detector/DataMatrixDetector.cpp \
    $$PWD/zxing/datamatrix/detector/DataMatrixDetectorException.cpp \
    $$PWD/zxing/datamatrix/detector/DataMatrixMonochromeRectangleDetector.cpp \
    $$PWD/zxing/qrcode/decoder/QRBitMatrixParser.cpp \
    $$PWD/zxing/qrcode/decoder/QRDataBlock.cpp \
    $$PWD/zxing/qrcode/decoder/QRDataMask.cpp \
    $$PWD/zxing/qrcode/decoder/QRDecodedBitStreamParser.cpp \
    $$PWD/zxing/qrcode/decoder/QRDecoder.cpp \
    $$PWD/zxing/qrcode/decoder/QRMode.cpp \
    $$PWD/zxing/qrcode/detector/QRAlignmentPattern.cpp \
    $$PWD/zxing/qrcode/detector/QRAlignmentPatternFinder.cpp \
    $$PWD/zxing/qrcode/detector/QRDetector.cpp \
    $$PWD/zxing/qrcode/detector/QRFinderPattern.cpp \
    $$PWD/zxing/qrcode/detector/QRFinderPatternFinder.cpp \
    $$PWD/zxing/qrcode/detector/QRFinderPatternInfo.cpp \
    $$PWD/zxing/qrcode/QRVersion.cpp \
    $$PWD/zxing/qrcode/QRFormatInformation.cpp \
    $$PWD/zxing/qrcode/QRErrorCorrectionLevel.cpp

symbian {
    TARGET.UID3 = 0xE618743C
    TARGET.EPOCALLOWDLLDATA = 1

    #TARGET.CAPABILITY = All -TCB -AllFiles -DRM
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

win32{
    DEFINES += NO_ICONV
}
