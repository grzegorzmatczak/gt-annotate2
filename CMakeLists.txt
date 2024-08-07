cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(gt-annotate2  VERSION 0.0  DESCRIPTION "gt-annotate2 Windows/Linux"  LANGUAGES C CXX)

set(DEFAULT_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Release")
set(TARGET_NAME "gt-annotate2")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")
if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lX11 -Wall" )
endif (UNIX)

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /O2 /MD" )
endif (WIN32)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

if (WIN32)
	set(QT5_PATH  "D:\\Qt\\5.15.2\\msvc2019_64")
	list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH})
	list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH}"\\bin\\")
endif (WIN32)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(QT_DEBUG_PLUGINS 1)
include_directories( "src" )
include_directories( "include" )
include_directories( "utils2/include" )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL)

enable_testing()
add_subdirectory(utils2 build)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(SRC
  src/main.cpp
  src/colorpicker.cpp
  src/pensizepicker.cpp
  src/graphicsview.cpp
  src/graphicsscene.cpp
  src/view.cpp
  src/painter.cpp
  src/paintersettings.cpp
  src/labeldialog.cpp
  src/toolbar.cpp
  src/graphicspixmapitem.cpp
  src/graphicsrectitem.cpp
  src/mainwindow.cpp)
  

set(HEADERS
  include/colorpicker.hpp
  include/pensizepicker.hpp
  include/graphicsview.hpp
  include/graphicsscene.hpp
  include/view.hpp
  include/painter.hpp
  include/paintersettings.hpp
  include/labeldialog.hpp
  include/toolbar.hpp
  include/graphicspixmapitem.hpp
  include/graphicsrectitem.hpp
  include/mainwindow.hpp)

macro(copy_json jsonname)
  configure_file(${jsonname} Debug/${jsonname})
  configure_file(${jsonname} Release/${jsonname})
endmacro()

copy_json(config.json)

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Threads::Threads utils2_lib Qt5::OpenGL)

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE} ")

if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release" AND WIN32)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()


if (WIN32)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
       COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(WIN32)