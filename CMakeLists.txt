cmake_minimum_required(VERSION 3.24)
option(BUILD_QRDEC "Build Decoding part" ON)
option(BUILD_QRENC "Build Encoding part" ON)
include(${CMAKE_CURRENT_BINARY_DIR}/local_conf.cmake OPTIONAL)

include(FetchContent)
FetchContent_Declare(
	ccommon
	GIT_REPOSITORY https://github.com/EddyTheCo/Common.git
	GIT_TAG v0.3.0
	)
FetchContent_MakeAvailable(ccommon)
version_from_git(
	LOG       OFF
	TIMESTAMP "%Y%m%d%H%M%S"
	)
project(qrCode VERSION ${VERSION} DESCRIPTION "library for qr code manipulation" LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(GNUInstallDirs)

find_package(Qt6 COMPONENTS Core Gui Qml Quick ShaderTools Multimedia)


if(BUILD_QRDEC)
	add_subdirectory(QrDec)
endif(BUILD_QRDEC)
if(BUILD_QRENC)
	add_subdirectory(QrGen)
endif(BUILD_QRENC)
add_subdirectory(QtQrDec)
add_subdirectory(QtQrGen)


build_exports()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	build_cpack()
endif(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
if(BUILD_DOCS)
	build_docs()
endif()
