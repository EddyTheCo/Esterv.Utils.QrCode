cmake_minimum_required(VERSION 3.24)

option(BUILD_QRDEC "Build Decoding part" ON)
option(BUILD_QRGEN "Build Generation part" ON)
option(OpenCV_DOWNLOAD "Download prebuilts if find_package fails" ON)
option(BUILD_EXAMPLES "Build the examples" ON)

include(${CMAKE_CURRENT_BINARY_DIR}/local_conf.cmake OPTIONAL)

include(FetchContent)
FetchContent_Declare(
  ccommon
  GIT_REPOSITORY https://github.com/EddyTheCo/Common.git
  GIT_TAG v0.5.0)
FetchContent_MakeAvailable(ccommon)
version_from_git(LOG OFF TIMESTAMP "%Y%m%d%H%M%S")
project(
  EstervQrCode
  VERSION ${VERSION}
  DESCRIPTION "Library for qr code manipulation"
  LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(GNUInstallDirs)

if(BUILD_QRDEC)
  add_subdirectory(QrDec)
endif(BUILD_QRDEC)
if(BUILD_QRGEN)
  add_subdirectory(QrGen)
endif(BUILD_QRGEN)

add_subdirectory(QtQrDec)
add_subdirectory(QtQrGen)

set(SET_COMPONENTS "")
foreach(component "QrDec" "QrGen" "QtQrDec" "QtQrGen")
  if(TARGET "${component}")
    string(APPEND SET_COMPONENTS
           "set(${PROJECT_NAME}_${component}_FOUND \"ON\")\n")
  endif()
endforeach()

build_exports()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  build_cpack()
endif(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
if(BUILD_DOCS)
  build_docs()
endif(BUILD_DOCS)
