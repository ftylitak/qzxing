SET(SOURCES

    ${WIN32_DIR}/zxing/iconv.h
    ${WIN32_DIR}/zxing/win_iconv.c
)

if(MSVC)
    LIST(APPEND SOURCES ${WIN32_DIR}/zxing/msvc/stdint.h)
endif(MSVC)

target_sources(qzxing PRIVATE ${SOURCES})
