cmake_minimum_required(VERSION 3.3)
project(QZXing)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(BUILD_SHARED "Build as shared library" OFF)

if(BUILD_SHARED)
    SET(SOVERSION_MAJOR 3)
    SET(SOVERSION_MINOR 3)
    SET(SOVERSION_PATCH 0)
    SET(SOVERSION_FULL "${SOVERSION_MAJOR}.${SOVERSION_MINOR}.${SOVERSION_PATCH}")

    OPTION(QZXING_MULTIMEDIA "" OFF)
    OPTION(QZXING_USE_QML "" OFF)
    OPTION(QZXING_USE_ENCODER "" OFF)
    OPTION(QZXING_MULTIMEDIA "" OFF)
    OPTION(QZXING_USE_QML "" OFF)
    OPTION(QZXING_USE_ENCODER "" OFF)
    OPTION(QZXING_USE_DECODER_QR_CODE "" OFF)
    OPTION(QZXING_USE_DECODER_1D_BARCODES "" OFF)
    OPTION(QZXING_USE_DECODER_DATA_MATRIX "" OFF)
    OPTION(QZXING_USE_DECODER_AZTEC "" OFF)
    OPTION(QZXING_USE_DECODER_PDF17 "" OFF)
    OPTION(QZXING_USE_DECODER_1D_BARCODES "" OFF)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Multimedia )
find_package(Qt5 REQUIRED Svg Quick QuickControls2)

SET(BIGINT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint)
SET(WIN32_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/zxing/win32/zxing)
SET(ZXING_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing)

set(CMAKE_AUTOMOC ON)
set(CMAKE_WARN_ON)

set(PUBLIC_HEADERS
    QZXing.h
    QZXing_global.h
)

set(PUBLIC_DEFINES "")

set(SOURCES

    CameraImageWrapper.cpp
    CameraImageWrapper.h
    ImageHandler.cpp
    ImageHandler.h
    QZXing.cpp
    ${PUBLIC_HEADERS}
    )

if(QZXING_MULTIMEDIA)

    LIST(APPEND SOURCES QZXingFilter.cpp QZXingFilter.h)
    LIST(APPEND PUBLIC_HEADERS QZXingFilter.h)
    LIST(APPEND PUBLIC_DEFINES QZXING_MULTIMEDIA)

    SET(QZXING_USE_QML ON)

endif(QZXING_MULTIMEDIA)

if(QZXING_USE_QML)
    LIST(APPEND SOURCES QZXingImageProvider.cpp QZXingImageProvider.h)
    LIST(APPEND PUBLIC_HEADERS QZXingImageProvider.h)
    LIST(APPEND PUBLIC_DEFINES QZXING_QML)
endif(QZXING_USE_QML)

if(QZXING_USE_ENCODER)
    LIST(APPEND PUBLIC_DEFINES ENABLE_ENCODER_GENERIC ENABLE_ENCODER_QR_CODE)
endif(QZXING_USE_ENCODER)

if(BUILD_SHARED)
    add_library(qzxing SHARED ${SOURCES})
    set_target_properties(qzxing
        PROPERTIES
        VERSION ${SOVERSION_FULL}
        SOVERSION ${SOVERSION_MAJOR}
)
else()
    add_library(qzxing "" ${SOURCES})
endif()

if(WIN32)
    add_subdirectory(zxing/win32)
    if(MSVC)
        add_definitions(-D__STDC_LIMIT_MACROS)
    endif(MSVC)

    add_definitions(-DNO_ICONV)
endif(WIN32)

if(ANDROID)
    add_definitions(-DNO_ICONV)
endif()

if(VS_WINRT_COMPONENT)
    add_definitions(-DNO_ICONV)
endif(VS_WINRT_COMPONENT)

add_subdirectory(zxing/bigint)

add_subdirectory(zxing/zxing)

target_link_libraries(qzxing Qt5::Core Qt5::Gui)

if(QZXING_MULTIMEDIA)
    target_link_libraries(qzxing Qt5::Multimedia)
endif(QZXING_MULTIMEDIA)

if(QZXING_USE_QML)
    target_link_libraries(qzxing
        Qt5::Svg
        Qt5::Quick
        Qt5::QuickControls2)
endif(QZXING_USE_QML)

if(QZXING_USE_DECODER_QR_CODE)
    target_compile_definitions(qzxing PRIVATE -DENABLE_DECODER_QR_CODE)
endif()

if(QZXING_USE_DECODER_1D_BARCODES)
    target_compile_definitions(qzxing PRIVATE -DENABLE_DECODER_1D_BARCODES)
endif()

if(QZXING_USE_DECODER_DATA_MATRIX)
    target_compile_definitions(qzxing PRIVATE -DENABLE_DECODER_DATA_MATRIX)
endif()

if(QZXING_USE_DECODER_AZTEC)
    target_compile_definitions(qzxing PRIVATE -DENABLE_DECODER_AZTEC)
endif()

if(QZXING_USE_DECODER_PDF17)
    target_compile_definitions(qzxing PRIVATE -DENABLE_DECODER_PDF17)
endif()

if(QZXING_USE_DECODER_1D_BARCODES)
    target_compile_definitions(qzxing PRIVATE -DENABLE_DECODER_1D_BARCODES)
endif()

if(!BUILD_SHARED)
    # Change Global Definitions depending on how you want to use the library
    list(APPEND PUBLIC_DEFINES DISABLE_LIBRARY_FEATURES)
endif()

target_compile_definitions(qzxing PUBLIC ${PUBLIC_DEFINES})

# Target includes
target_include_directories(qzxing
  PRIVATE
        .
        zxing
        zxing/win32/zxing
        zxing/zxing
        zxing/bigint
  PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

if(BUILD_SHARED)
    include (GNUInstallDirs)
    include (JoinPaths)

    set(QZXING_INSTALL_TARGETS qzxing)

    install (
        TARGETS ${QZXING_INSTALL_TARGETS} EXPORT QZXingTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    install (
        FILES ${PUBLIC_HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/qzxing"
    )

    join_paths(PC_LIBDIR "\${prefix}" "${CMAKE_INSTALL_LIBDIR}")
    join_paths(PC_INCLUDEDIR "\${prefix}" "${CMAKE_INSTALL_INCLUDEDIR}" "qzxing")

    string(REPLACE ";" " -D" PC_DEFINES "${PUBLIC_DEFINES}")
    if(PC_DEFINES)
        set(PC_DEFINES "-D${PC_DEFINES}")
    endif()

    configure_file(QZXing.pc.in ${CMAKE_CURRENT_BINARY_DIR}/QZXing.pc @ONLY)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QZXing.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()
