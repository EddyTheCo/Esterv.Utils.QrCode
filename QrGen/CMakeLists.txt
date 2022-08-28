cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(QrCodeGenLib VERSION 0.1 DESCRIPTION "library for qr codes generation" LANGUAGES CXX)


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


add_library(QrGen src/qrcodegen.cpp src/utils.cpp include/qrcodegen.hpp)

set_target_properties(QrGen PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_compile_features(QrGen PUBLIC cxx_std_11)



target_include_directories(QrGen PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	"$<INSTALL_INTERFACE:include>")

install(TARGETS QrGen EXPORT QrGenTargets DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/)

install(EXPORT QrGenTargets
        FILE QrGenTargets.cmake
	NAMESPACE qr::
        DESTINATION lib/cmake/QrGen
	)
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/QrGenConfig.cmake"
        INSTALL_DESTINATION "lib/cmake/QrGen"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
	)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/QrGenConfigVersion.cmake"
	VERSION "0.1.1.0"
	COMPATIBILITY AnyNewerVersion
	)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QrGenConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QrGenConfigVersion.cmake
        DESTINATION lib/cmake/QrGen
	)
export(EXPORT QrGenTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/QrGenTargets.cmake"
	)
