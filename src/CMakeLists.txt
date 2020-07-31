# Author: Kang Lin (kl222@126.com)

cmake_minimum_required(VERSION 2.8.12)

if(POLICY CMP0100)
    cmake_policy(SET CMP0100 NEW)
endif()

if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

project(QZXing)

# TODO: Modify the version to the correct version
SET(BUILD_VERSION "2.3")
# Find Git Version Patch
IF(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    if(NOT GIT)
        SET(GIT $ENV{GIT})
    endif()
    if(NOT GIT)
        FIND_PROGRAM(GIT NAMES git git.exe git.cmd)
    endif()
    IF(GIT)
        EXECUTE_PROCESS(
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMAND ${GIT} describe --tags
            OUTPUT_VARIABLE GIT_VERSION  OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        if(NOT GIT_VERSION)
            EXECUTE_PROCESS(
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND ${GIT} rev-parse --short HEAD
                OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE
            )
        endif()
        SET(BUILD_VERSION ${GIT_VERSION})
    ENDIF()
ENDIF()
message("BUILD_VERSION:${BUILD_VERSION}")
set(VERSION ${BUILD_VERSION})

# Open qt compile tools
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_VERBOSE_MAKEFILE ON)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(GenerateExportHeader)

# Record the files that will need to be deleted
CONFIGURE_FILE(
    "cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
# Create delete target
ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

SET(BIGINT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/zxing/bigint)
SET(WIN32_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/zxing/win32/zxing)
SET(ZXING_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/zxing/zxing)

SET(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(INSTALL_HEADER_FILES
    QZXing.h
    QZXing_global.h
    )

set(HEADER_FILES
    CameraImageWrapper.h
    ImageHandler.h
    ${INSTALL_HEADER_FILES}
    )

set(SOURCE_FILES
    CameraImageWrapper.cpp
    ImageHandler.cpp
    QZXing.cpp
    )

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    PUBLIC_HEADER "${INSTALL_HEADER_FILES}" # Install head files
    VERSION ${BUILD_VERSION})
target_compile_definitions(${PROJECT_NAME} PRIVATE
    QZXING_LIBRARY ZXING_ICONV_CONST)

# Need qt components
SET(QT_COMPONENTS Core Gui)

option(QZXING_MULTIMEDIA "Use multimedia" ON)
if(QZXING_MULTIMEDIA)
    target_sources(${PROJECT_NAME} PRIVATE QZXingFilter.cpp QZXingFilter.h)
    target_compile_definitions(${PROJECT_NAME} PRIVATE QZXING_MULTIMEDIA)
    LIST(APPEND QT_COMPONENTS Multimedia)
    SET(QZXING_QML ON)
endif(QZXING_MULTIMEDIA)

option(QZXING_QML "Use qml" ${QZXING_QML})
if(QZXING_QML)
    target_sources(${PROJECT_NAME} PRIVATE QZXingImageProvider.cpp QZXingImageProvider.h)
    LIST(APPEND EXPORT_DEFINES QZXING_QML)
    LIST(APPEND QT_COMPONENTS Quick)
    SET(QZXING_ENABLE_ENCODER ON)
endif(QZXING_QML)

find_package(Qt5 COMPONENTS ${QT_COMPONENTS} REQUIRED)
message("Qt5_VERSION:${Qt5_VERSION}")
if(Qt5_VERSION VERSION_LESS "5.0.0")
    message(FATAL_ERROR "Current qt version:${Qt5_VERSION}, Qt must greater then 5.0.0")
endif()
FOREACH(_COMPONENT ${QT_COMPONENTS})
    LIST(APPEND QT_LIBRARIES ${Qt5${_COMPONENT}_LIBRARIES})
ENDFOREACH()
get_filename_component(QT_INSTALL_DIR "${Qt5_DIR}/../../.." ABSOLUTE)

target_link_libraries(${PROJECT_NAME} PUBLIC ${QT_LIBRARIES})

option(QZXING_ENABLE_ENCODER "Enable encoder" ${QZXING_ENABLE_ENCODER})
if(QZXING_ENABLE_ENCODER)
    LIST(APPEND EXPORT_DEFINES ENABLE_ENCODER_GENERIC)
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()

# iconv
if(WIN32)
    SET(QZXING_ENABLE_ICONV ON)
else()
    SET(QZXING_ENABLE_ICONV OFF)
endif()
option(QZXING_ENABLE_ICONV "Enable iconv" ${QZXING_ENABLE_ICONV})
if(QZXING_ENABLE_ICONV)
    if(WIN32)
        add_subdirectory(zxing/win32)
        if(MSVC)
            target_compile_definitions(${PROJECT_NAME} PRIVATE -D__STDC_LIMIT_MACROS)
        endif(MSVC)
    endif(WIN32)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE NO_ICONV)
endif()

add_subdirectory(zxing/bigint)

add_subdirectory(zxing/zxing)

# Target includes
target_include_directories(${PROJECT_NAME}
    PRIVATE
        .
        zxing
        zxing/win32/zxing
        zxing/zxing
        zxing/bigint
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Export defines by configure_file
target_compile_definitions(${PROJECT_NAME} PUBLIC ${EXPORT_DEFINES})

if(ANDROID)
    # Install target
    INSTALL(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}Config
            RUNTIME DESTINATION "libs/${ANDROID_ABI}"
                COMPONENT Runtime
            LIBRARY DESTINATION "libs/${ANDROID_ABI}"
                COMPONENT Runtime
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )
else()
    # Install target
    if(WIN32)
        INSTALL(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}Config
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
                COMPONENT Runtime
            LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
                COMPONENT Runtime
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )
    else()
        INSTALL(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}Config
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
                COMPONENT Runtime
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
                COMPONENT Runtime
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )
    endif()
endif()

export(TARGETS ${PROJECT_NAME}
       APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
)
# Install cmake configure files
install(EXPORT ${PROJECT_NAME}Config
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        )
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${BUILD_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

# Install pkg-config configure file
foreach(ed ${EXPORT_DEFINES})
    set(PC_EXPORT_DEFINES "${PC_EXPORT_DEFINES} -D${ed}")
endforeach()
configure_file(QZXing.pc.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
