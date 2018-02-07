ADD_FILES(LIB_QZXING

	CameraImageWrapper.cpp
  CameraImageWrapper.h
  ImageHandler.cpp
  ImageHandler.h
  QZXing.cpp
  QZXing.h
  QZXingFilter.cpp
  QZXingFilter.h
  QZXingImageProvider.cpp
  QZXingImageProvider.h
  QZXing_global.h

  )
add_subdirectory(zxing)

set(CMAKE_AUTOMOC ON)


get_property(LIB_QZXING_SRCLIST GLOBAL PROPERTY LIB_QZXING)

find_package(Qt5Core REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)


include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Multimedia_INCLUDE_DIRS})
include_directories(${Qt5MultimediaWidgets_INCLUDE_DIRS})
include_directories(${Qt5Quick_INCLUDE_DIRS})


# Target
GenerateProject(${CMAKE_CURRENT_SOURCE_DIR} "${LIB_QZXING_SRCLIST}")
add_library(qzxinglib SHARED ${LIB_QZXING_SRCLIST})
set_target_properties(qzxinglib PROPERTIES FOLDER Lib)

# Change Global Definitions depending on how you want to use the library
target_compile_definitions(qzxinglib 
  PRIVATE -DQZXING_LIBRARY 
  PRIVATE -DZXING_ICONV_CONST 
  PUBLIC  -DQZXING_QML
  PUBLIC  -DQZXING_MULTIMEDIA)


  qt5_use_modules(qzxinglib
    Core
    Widgets
    Svg
	Quick
  QuickControls2
	Multimedia
  MultimediaWidgets
	  )

# Target includes
target_include_directories(qzxinglib
  PUBLIC
  	.
    QZXing.h
  PRIVATE
  	
  	zxing
  	zxing/win32/zxing
  	zxing/zxing
  	)

