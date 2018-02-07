

ADD_FILES( LIB_QZXING

	ErrorCorrectionLevel.h
	FormatInformation.h
	QRCodeReader.cpp
	QRCodeReader.h
	QRErrorCorrectionLevel.cpp
	QRFormatInformation.cpp
	QRVersion.cpp
	Version.h
	decoder/BitMatrixParser.h
	decoder/DataBlock.h
	decoder/DataMask.h
	decoder/DecodedBitStreamParser.h
	decoder/Decoder.h
	decoder/Mode.h
	decoder/QRBitMatrixParser.cpp
	decoder/QRDataBlock.cpp
	decoder/QRDataMask.cpp
	decoder/QRDecodedBitStreamParser.cpp
	decoder/QRDecoder.cpp
	decoder/QRMode.cpp
	detector/AlignmentPattern.h
	detector/AlignmentPatternFinder.h
	detector/Detector.h
	detector/FinderPattern.h
	detector/FinderPatternFinder.h
	detector/FinderPatternInfo.h
	detector/QRAlignmentPattern.cpp
	detector/QRAlignmentPatternFinder.cpp
	detector/QRDetector.cpp
	detector/QRFinderPattern.cpp
	detector/QRFinderPatternFinder.cpp
	detector/QRFinderPatternInfo.cpp
	encoder/BlockPair.h
	encoder/ByteMatrix.cpp
	encoder/ByteMatrix.h
	encoder/Encoder.h
	encoder/MaskUtil.cpp
	encoder/MaskUtil.h
	encoder/MatrixUtil.cpp
	encoder/MatrixUtil.h
	encoder/QRCode.cpp
	encoder/QRCode.h
	encoder/QREncoder.cpp

	)