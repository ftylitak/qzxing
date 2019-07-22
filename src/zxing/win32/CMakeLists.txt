cmake_minimum_required(VERSION 3.13)

SET(SOURCES

    zxing/iconv.h
    zxing/win_iconv.c
    zxing/msvc/stdint.h

    )

target_sources(qzxing PRIVATE ${SOURCES})
