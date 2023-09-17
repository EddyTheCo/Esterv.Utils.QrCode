
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick OPTIONAL_COMPONENTS Multimedia)

if (Qt6_FOUND)
	qt_standard_project_setup()
	if(NOT TARGET Qt6::Multimedia AND NOT EMSCRIPTEN)
		FetchContent_Declare(
			qtmultimedia
			GIT_REPOSITORY git://code.qt.io/qt/qtmultimedia.git
			GIT_TAG 6.5.0
			)
		FetchContent_MakeAvailable(qtmultimedia)
	endif()
endif(Qt6_FOUND)
FetchContent_Declare(
	MyDesigns
	GIT_REPOSITORY https://github.com/EddyTheCo/MyDesigns.git
	GIT_TAG v0.2.3
	FIND_PACKAGE_ARGS 0.2 CONFIG
	)
FetchContent_MakeAvailable(MyDesigns)

if (Qt6_FOUND AND TARGET QrDec)

	if(TARGET Qt6::Multimedia)
		list(APPEND qml_files  "qml/QrQmlCamera.qml")
	else()
		if(EMSCRIPTEN)
			list(APPEND qml_files  "qml/wasm/QrQmlCamera.qml")
		endif()
	endif()

	qt6_add_qml_module(QtQrDec
		URI  QtQrDec
		VERSION 1.0
		SOURCES Qrimagedecoder.cpp include/Qrimagedecoder.hpp
		QML_FILES ${qml_files}
		RESOURCE_PREFIX
		"/esterVtech.com/imports"
		OUTPUT_TARGETS out_targets_var
		OUTPUT_DIRECTORY
		${CMAKE_CURRENT_BINARY_DIR}/QtQrDec
		IMPORT_PATH ${QML_IMPORT_PATH}
		)
	target_include_directories(QtQrDec PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qrCode>")

	target_link_libraries(QtQrDec PUBLIC Qt6::Gui Qt6::Quick)
	target_link_libraries(QtQrDec PRIVATE QrDec MyDesigns)

	install(TARGETS QtQrDec  ${out_targets_var}
		EXPORT qrCodeTargets
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT QtQr
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qrCode
		COMPONENT QtQr
		)
	if(EMSCRIPTEN)
		target_compile_definitions(QtQrDec PRIVATE USE_EMSCRIPTEN)
	endif(EMSCRIPTEN)
endif(Qt6_FOUND AND TARGET QrDec)
list(APPEND QML_IMPORT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/qml ${CMAKE_CURRENT_BINARY_DIR})
list(REMOVE_DUPLICATES QML_IMPORT_PATH)
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} CACHE STRING "" FORCE)
