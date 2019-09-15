cmake_minimum_required(VERSION 3.13)

SET(SOURCES

    zxing/iconv.h
    zxing/win_iconv.c
)

if(MSVC)
    LIST(APPEND SOURCES zxing/msvc/stdint.h)
endif(MSVC)

target_sources(qzxing PRIVATE ${SOURCES})
