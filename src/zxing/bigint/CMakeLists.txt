cmake_minimum_required(VERSION 3.13)


SET(SOURCES
     BigInteger.hh
     BigInteger.cc
     BigIntegerAlgorithms.hh
     BigIntegerAlgorithms.cc
     BigIntegerLibrary.hh
     BigIntegerUtils.hh
     BigIntegerUtils.cc
     BigUnsigned.hh
     BigUnsigned.cc
     BigUnsignedInABase.hh
     BigUnsignedInABase.cc
     NumberlikeArray.hh
    )

target_sources(qzxing PRIVATE ${SOURCES})
