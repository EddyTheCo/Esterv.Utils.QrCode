cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
include(local_conf.cmake OPTIONAL)
project(QrCodeDecLib VERSION 0.1 DESCRIPTION "library for qr codes decription" LANGUAGES CXX)


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


find_package( OpenCV REQUIRED )
add_library(QrDec qrcodedec.cpp include/qrcodedec.hpp)


target_compile_features(QrDec PUBLIC cxx_std_11)

set_target_properties(QrDec PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(QrDec PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(QrDec PRIVATE ${OpenCV_LIBS})

target_include_directories(QrDec PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	"$<INSTALL_INTERFACE:include>")

install(TARGETS QrDec EXPORT QrDecTargets DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/)

install(EXPORT QrDecTargets
        FILE QrDecTargets.cmake
	NAMESPACE qr::
        DESTINATION lib/cmake/QrDec
	)
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/QrDecConfig.cmake"
        INSTALL_DESTINATION "lib/cmake/QrDec"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
	)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/QrDecConfigVersion.cmake"
	VERSION "0.1.1.0"
	COMPATIBILITY AnyNewerVersion
	)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QrDecConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QrDecConfigVersion.cmake
        DESTINATION lib/cmake/QrDec
	)
export(EXPORT QrDecTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/QrDecTargets.cmake"
	)

