ADD_FILES( LIB_QZXING

	PDF417Reader.cpp
	PDF417Reader.h
	decoder/BitMatrixParser.h
	decoder/DecodedBitStreamParser.h
	decoder/Decoder.h
	decoder/PDF417BitMatrixParser.cpp
	decoder/PDF417DecodedBitStreamParser.cpp
	decoder/PDF417Decoder.cpp		
	decoder/ec/ErrorCorrection.cpp
	decoder/ec/ErrorCorrection.h
	decoder/ec/ModulusGF.cpp
	decoder/ec/ModulusGF.h
	decoder/ec/ModulusPoly.cpp
	decoder/ec/ModulusPoly.h			
	
	detector/Detector.h
	detector/LinesSampler.cpp
	detector/LinesSampler.h
	detector/PDF417Detector.cpp
	)