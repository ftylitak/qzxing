cmake_minimum_required(VERSION 3.1)

project(BarcodeEncoder LANGUAGES CXX)

add_subdirectory(../../src build)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc")

target_include_directories(BarcodeEncoder
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../src
)

target_compile_definitions(${PROJECT_NAME}
  #PUBLIC QZXING_LIBRARY   #####
  PUBLIC ZXING_ICONV_CONST
  PUBLIC QZXING_QML
  PUBLIC QZXING_MULTIMEDIA
  PUBLIC DISABLE_LIBRARY_FEATURES  ####

  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick qzxing)
