cmake_minimum_required(VERSION 3.13)

SET(SOURCES

     BarcodeFormat.cpp
     BarcodeFormat.h
     Binarizer.cpp
     Binarizer.h
     BinaryBitmap.cpp
     BinaryBitmap.h
     ChecksumException.cpp
     ChecksumException.h
     DecodeHints.cpp
     DecodeHints.h
     EncodeHint.cpp
     EncodeHint.h
     Exception.cpp
     Exception.h
     FormatException.cpp
     FormatException.h
     IllegalStateException.h
     InvertedLuminanceSource.cpp
     InvertedLuminanceSource.h
     LuminanceSource.cpp
     LuminanceSource.h
     MultiFormatReader.cpp
     MultiFormatReader.h
     NotFoundException.h
     Reader.cpp
     Reader.h
     ReaderException.h
     Result.cpp
     Result.h
     ResultIO.cpp
     ResultPoint.cpp
     ResultPoint.h
     ResultPointCallback.cpp
     ResultPointCallback.h
     UnsupportedEncodingException.h
     WriterException.h
     ZXing.h

    )

SET(AZTEC_DIR

    aztec/AztecDetectorResult.cpp
    aztec/AztecDetectorResult.h
    aztec/AztecReader.cpp
    aztec/AztecReader.h
    aztec/decoder/AztecDecoder.cpp
    aztec/decoder/Decoder.h
    aztec/detector/AztecDetector.cpp
    aztec/detector/Detector.h

    )

SET(COMMON_DIR

    common/Array.h
    common/BitArray.cpp
    common/BitArray.h
    common/BitArrayIO.cpp
    common/BitMatrix.cpp
    common/BitMatrix.h
    common/BitSource.cpp
    common/BitSource.h
    common/CharacterSetECI.cpp
    common/CharacterSetECI.h
    common/Counted.h
    common/DecoderResult.cpp
    common/DecoderResult.h
    common/DetectorResult.cpp
    common/DetectorResult.h
    common/GlobalHistogramBinarizer.cpp
    common/GlobalHistogramBinarizer.h
    common/GreyscaleLuminanceSource.cpp
    common/GreyscaleLuminanceSource.h
    common/GreyscaleRotatedLuminanceSource.cpp
    common/GreyscaleRotatedLuminanceSource.h
    common/GridSampler.cpp
    common/GridSampler.h
    common/HybridBinarizer.cpp
    common/HybridBinarizer.h
    common/IllegalArgumentException.cpp
    common/IllegalArgumentException.h
    common/PerspectiveTransform.cpp
    common/PerspectiveTransform.h
    common/Point.h
    common/Str.cpp
    common/Str.h
    common/StringUtils.cpp
    common/StringUtils.h
    common/Types.h

    common/detector/JavaMath.h
    common/detector/MathUtils.h
    common/detector/MonochromeRectangleDetector.cpp
    common/detector/MonochromeRectangleDetector.h
    common/detector/WhiteRectangleDetector.cpp
    common/detector/WhiteRectangleDetector.h

    common/reedsolomon/GenericGF.cpp
    common/reedsolomon/GenericGF.h
    common/reedsolomon/GenericGFPoly.cpp
    common/reedsolomon/GenericGFPoly.h
    common/reedsolomon/ReedSolomonDecoder.cpp
    common/reedsolomon/ReedSolomonDecoder.h
    common/reedsolomon/ReedSolomonEncoder.cpp
    common/reedsolomon/ReedSolomonEncoder.h
    common/reedsolomon/ReedSolomonException.cpp
    common/reedsolomon/ReedSolomonException.h

    )

SET(DATAMATRIX_DIR

    datamatrix/DataMatrixReader.cpp
    datamatrix/DataMatrixReader.h
    datamatrix/DataMatrixVersion.cpp
    datamatrix/Version.h

    datamatrix/decoder/BitMatrixParser.h
    datamatrix/decoder/DataBlock.h
    datamatrix/decoder/DataMatrixBitMatrixParser.cpp
    datamatrix/decoder/DataMatrixDataBlock.cpp
    datamatrix/decoder/DataMatrixDecodedBitStreamParser.cpp
    datamatrix/decoder/DataMatrixDecoder.cpp
    datamatrix/decoder/DecodedBitStreamParser.h
    datamatrix/decoder/Decoder.h

    datamatrix/detector/CornerPoint.h
    datamatrix/detector/DataMatrixCornerPoint.cpp
    datamatrix/detector/DataMatrixDetector.cpp
    datamatrix/detector/DataMatrixDetectorException.cpp
    datamatrix/detector/Detector.h
    datamatrix/detector/DetectorException.h

    )

SET(MULTI_DIR

    multi/ByQuadrantReader.cpp
    multi/ByQuadrantReader.h
    multi/GenericMultipleBarcodeReader.cpp
    multi/GenericMultipleBarcodeReader.h
    multi/MultipleBarcodeReader.cpp
    multi/MultipleBarcodeReader.h

    multi/qrcode/QRCodeMultiReader.cpp
    multi/qrcode/QRCodeMultiReader.h

    multi/qrcode/detector/MultiDetector.cpp
    multi/qrcode/detector/MultiDetector.h
    multi/qrcode/detector/MultiFinderPatternFinder.cpp
    multi/qrcode/detector/MultiFinderPatternFinder.h

    )

SET(ONED_DIR

    oned/CodaBarReader.cpp
    oned/CodaBarReader.h
    oned/Code128Reader.cpp
    oned/Code128Reader.h
    oned/Code39Reader.cpp
    oned/Code39Reader.h
    oned/Code93Reader.cpp
    oned/Code93Reader.h
    oned/EAN13Reader.cpp
    oned/EAN13Reader.h
    oned/EAN8Reader.cpp
    oned/EAN8Reader.h
    oned/ITFReader.cpp
    oned/ITFReader.h
    oned/MultiFormatOneDReader.cpp
    oned/MultiFormatOneDReader.h
    oned/MultiFormatUPCEANReader.cpp
    oned/MultiFormatUPCEANReader.h
    oned/OneDReader.cpp
    oned/OneDReader.h
    oned/OneDResultPoint.cpp
    oned/OneDResultPoint.h
    oned/UPCAReader.cpp
    oned/UPCAReader.h
    oned/UPCEANReader.cpp
    oned/UPCEANReader.h
    oned/UPCEReader.cpp
    oned/UPCEReader.h

    )

SET(PDF417_DIR

    pdf417/PDF417Reader.cpp
    pdf417/PDF417Reader.h

    pdf417/decoder/BitMatrixParser.h
    pdf417/decoder/DecodedBitStreamParser.h
    pdf417/decoder/Decoder.h
    pdf417/decoder/PDF417BitMatrixParser.cpp
    pdf417/decoder/PDF417DecodedBitStreamParser.cpp
    pdf417/decoder/PDF417Decoder.cpp

    pdf417/decoder/ec/ErrorCorrection.cpp
    pdf417/decoder/ec/ErrorCorrection.h
    pdf417/decoder/ec/ModulusGF.cpp
    pdf417/decoder/ec/ModulusGF.h
    pdf417/decoder/ec/ModulusPoly.cpp
    pdf417/decoder/ec/ModulusPoly.h

    pdf417/detector/Detector.h
    pdf417/detector/LinesSampler.cpp
    pdf417/detector/LinesSampler.h
    pdf417/detector/PDF417Detector.cpp

    )

SET(QRCODE_DIR

    qrcode/ErrorCorrectionLevel.h
    qrcode/FormatInformation.h
    qrcode/QRCodeReader.cpp
    qrcode/QRCodeReader.h
    qrcode/QRErrorCorrectionLevel.cpp
    qrcode/QRFormatInformation.cpp
    qrcode/QRVersion.cpp
    qrcode/Version.h

    qrcode/decoder/BitMatrixParser.h
    qrcode/decoder/DataBlock.h
    qrcode/decoder/DataMask.h
    qrcode/decoder/DecodedBitStreamParser.h
    qrcode/decoder/Decoder.h
    qrcode/decoder/Mode.h
    qrcode/decoder/QRBitMatrixParser.cpp
    qrcode/decoder/QRDataBlock.cpp
    qrcode/decoder/QRDataMask.cpp
    qrcode/decoder/QRDecodedBitStreamParser.cpp
    qrcode/decoder/QRDecoder.cpp
    qrcode/decoder/QRMode.cpp

    qrcode/detector/AlignmentPattern.h
    qrcode/detector/AlignmentPatternFinder.h
    qrcode/detector/Detector.h
    qrcode/detector/FinderPattern.h
    qrcode/detector/FinderPatternFinder.h
    qrcode/detector/FinderPatternInfo.h
    qrcode/detector/QRAlignmentPattern.cpp
    qrcode/detector/QRAlignmentPatternFinder.cpp
    qrcode/detector/QRDetector.cpp
    qrcode/detector/QRFinderPattern.cpp
    qrcode/detector/QRFinderPatternFinder.cpp
    qrcode/detector/QRFinderPatternInfo.cpp

    qrcode/encoder/BlockPair.h
    qrcode/encoder/ByteMatrix.cpp
    qrcode/encoder/ByteMatrix.h
    qrcode/encoder/Encoder.h
    qrcode/encoder/MaskUtil.cpp
    qrcode/encoder/MaskUtil.h
    qrcode/encoder/MatrixUtil.cpp
    qrcode/encoder/MatrixUtil.h
    qrcode/encoder/QRCode.cpp
    qrcode/encoder/QRCode.h
    qrcode/encoder/QREncoder.cpp

    )

target_sources(qzxing PRIVATE
    ${SOURCES}
    ${AZTEC_DIR}
    ${COMMON_DIR}
    ${DATAMATRIX_DIR}
    ${MULTI_DIR}
    ${ONED_DIR}
    ${PDF417_DIR}
    ${QRCODE_DIR})
