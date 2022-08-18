cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

#project(qrCode VERSION 0.1 DESCRIPTION "library for qr codes" LANGUAGES CXX)


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


add_library(qrGen src/qrcodegen.cpp include/qrcodegen.hpp)


target_compile_features(qrGen PUBLIC cxx_std_11)



target_include_directories(qrGen PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	"$<INSTALL_INTERFACE:include>")

install(TARGETS qrGen EXPORT qrGenTargets DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/)

install(EXPORT qrGenTargets
	FILE qrGenTargets.cmake
	NAMESPACE qr::
	DESTINATION lib/cmake/qrGen
	)
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/qrGenConfig.cmake"
	INSTALL_DESTINATION "lib/cmake/qrGen"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
	)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/qrGenConfigVersion.cmake"
	VERSION "0.1.1.0"
	COMPATIBILITY AnyNewerVersion
	)
install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/qrGenConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/qrGenConfigVersion.cmake
	DESTINATION lib/cmake/qrGen
	)
export(EXPORT qrGenTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/qrGenTargets.cmake"
	)
