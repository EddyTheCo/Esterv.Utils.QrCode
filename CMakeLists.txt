cmake_minimum_required(VERSION 3.24)
option(BUILD_QRDEC "Build Decoding part" ON)
option(BUILD_QRENC "Build Encoding part" ON)
include(${CMAKE_CURRENT_BINARY_DIR}/local_conf.cmake OPTIONAL)

include(FetchContent)
FetchContent_Declare(
	ccommon
	GIT_REPOSITORY https://github.com/EddyTheCo/Common.git
	GIT_TAG use_IFW
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

if(BUILD_QRDEC)
    add_subdirectory(QrDec)
endif(BUILD_QRDEC)
if(BUILD_QRENC)
    add_subdirectory(QrGen)
endif(BUILD_QRENC)
add_subdirectory(QtQrDec)
add_subdirectory(QtQrGen)



install(EXPORT ${PROJECT_NAME}-config
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
	NAMESPACE ${PROJECT_NAME}::
	COMPONENT ${PROJECT_NAME}
	)
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
	)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${VERSION}
	COMPATIBILITY SameMajorVersion
	)
install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
	COMPONENT ${PROJECT_NAME}
	)
export(EXPORT ${PROJECT_NAME}-config
	FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	)

	if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
		set(cpack_file_name "${PROJECT_NAME}-v${SEMVER}-${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_VERSION}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_CXX_COMPILER_ID}")
		if(NOT BUILD_SHARED_LIBS)
			set(cpack_file_name "${cpack_file_name}-static")
		endif(NOT BUILD_SHARED_LIBS)
		set(CPACK_PACKAGE_FILE_NAME ${cpack_file_name})
		include(CPack)
		include(CPackIFW)
		cpack_add_component(${PROJECT_NAME})
		cpack_ifw_configure_component(${PROJECT_NAME} LICENSES "License" ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
		cpack_ifw_add_repository("Repo" URL "${REPO_URL}/packages/${CMAKE_SYSTEM_NAME}/" )
	endif(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
if(BUILD_DOCS)
	build_docs()
endif()
