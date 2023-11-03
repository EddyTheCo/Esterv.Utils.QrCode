
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick OPTIONAL_COMPONENTS Multimedia)
FetchContent_Declare(
	MyDesigns
	GIT_REPOSITORY https://github.com/EddyTheCo/MyDesigns.git
	GIT_TAG v0.3.1
	FIND_PACKAGE_ARGS 0.3 CONFIG
	)
FetchContent_MakeAvailable(MyDesigns)
if (Qt6_FOUND AND TARGET QrDec)
	qt_standard_project_setup()
	qt6_add_qml_module(QtQrDec
		URI  QtQrDec
		VERSION 1.0
		SOURCES Qrimagedecoder.cpp include/Qrimagedecoder.hpp
                QML_FILES
                qml/QrQmlCamera.qml
		qml/QrCam.qml
		qml/QrTextCamPop.qml
		RESOURCE_PREFIX
		"/esterVtech.com/imports"
		OUTPUT_TARGETS out_targets_var
		OUTPUT_DIRECTORY
		${CMAKE_BINARY_DIR}/QtQrDec
		IMPORT_PATH ${CMAKE_BINARY_DIR}
		)
	target_include_directories(QtQrDec PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qrCode>")

        target_link_libraries(QtQrDec PUBLIC Qt6::Gui Qt6::Quick QrDec $<TARGET_NAME_IF_EXISTS:Qt6::Multimedia> MyDesigns
		$<$<STREQUAL:$<TARGET_PROPERTY:MyDesigns,TYPE>,STATIC_LIBRARY>:MyDesignsplugin>)

	install(TARGETS QtQrDec QtQrDecplugin ${out_targets_var}
		EXPORT qrCodeTargets
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT QtQr
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qrCode
		COMPONENT QtQr
		)
	install(DIRECTORY ${CMAKE_BINARY_DIR}/QtQrDec/
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/QMLPlugins/QtQrDec
		COMPONENT QtQr
		)

	if(EMSCRIPTEN)
                target_compile_definitions(QtQrDec PUBLIC USE_EMSCRIPTEN)
	endif(EMSCRIPTEN)
endif(Qt6_FOUND AND TARGET QrDec)
