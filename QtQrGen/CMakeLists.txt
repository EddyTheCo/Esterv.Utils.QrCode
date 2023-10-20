find_package(Qt6 COMPONENTS Core Gui Qml Quick OPTIONAL_COMPONENTS Svg)
FetchContent_Declare(
	MyDesigns
	GIT_REPOSITORY https://github.com/EddyTheCo/MyDesigns.git
	GIT_TAG v0.3.1
	FIND_PACKAGE_ARGS 0.3 CONFIG
	)
FetchContent_MakeAvailable(MyDesigns)

if (Qt6_FOUND)
	qt_standard_project_setup()
	qt6_add_qml_module(QtQrGen
		URI  QtQrGen
		VERSION 1.0
		SOURCES Qrimageprovider.cpp include/Qrimageprovider.hpp
		QML_FILES
		qml/AddressQr.qml
		qml/PayQrPop.qml
		qml/QrLabel.qml
		RESOURCE_PREFIX
		"/esterVtech.com/imports"
		OUTPUT_TARGETS out_targets_var
		OUTPUT_DIRECTORY
		${CMAKE_BINARY_DIR}/QtQrGen
		IMPORT_PATH ${CMAKE_BINARY_DIR}
		)


	target_include_directories(QtQrGen PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qrCode>")
	if(NOT TARGET Qt6::Svg)
		FetchContent_Declare(
			qtsvg
			GIT_REPOSITORY git://code.qt.io/qt/qtsvg.git
			GIT_TAG 6.5.0
			)
		FetchContent_MakeAvailable(qtsvg)
	endif()


	target_link_libraries(QtQrGen PUBLIC
		Qt6::Quick
		)
	target_link_libraries(QtQrGen PRIVATE
		QrGen
		Qt6::Core
		Qt6::Gui
		Qt6::Qml
		Qt6::Svg
		MyDesigns
		$<$<STREQUAL:$<TARGET_PROPERTY:MyDesigns,TYPE>,STATIC_LIBRARY>:MyDesignsplugin>
		)

	install(TARGETS QtQrGen QtQrGenplugin ${out_targets_var}
		EXPORT qrCodeTargets
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT QtQr
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qrCode
		COMPONENT QtQr
		)
	install(DIRECTORY ${CMAKE_BINARY_DIR}/QtQrGen/
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/QMLPlugins/QtQrGen
		COMPONENT QtQr
		)
endif(Qt6_FOUND)
if(BUILD_DOCS)
	get_target_property(build_docs cmake_build_docs SOURCES)
	include(${build_docs})
endif()
