cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(qrCode VERSION 0.1 DESCRIPTION "library for qr codes" LANGUAGES CXX)

include(local_conf.cmake OPTIONAL)
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
		STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
		"Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(USE_QT " build or not the qt interface of the library " ON)
option(BUILD_Dec "build or not the decoding part of the library" OFF)
add_subdirectory(QrGen)
if(BUILD_Dec)
add_subdirectory(QrDec)
endif(BUILD_Dec)
if(USE_QT)
add_subdirectory(QtQrGen)
if(BUILD_Dec)
add_subdirectory(QtQrDec)
endif(BUILD_Dec)
endif(USE_QT)

