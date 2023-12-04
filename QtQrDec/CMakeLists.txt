
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick ShaderTools OPTIONAL_COMPONENTS Multimedia)
FetchContent_Declare(
	EstervDesigns
	GIT_REPOSITORY https://github.com/EddyTheCo/MyDesigns.git
	GIT_TAG improvements
	FIND_PACKAGE_ARGS 0.4 COMPONENTS SimpleStyle CustomControls CONFIG
	)
FetchContent_MakeAvailable(EstervDesigns)


if (Qt6_FOUND AND TARGET QrDec)
	qt_standard_project_setup()
	qt6_add_qml_module(QtQrDec
		URI  Esterv.CustomControls.QrDec
		VERSION ${VERSION}
		SOURCES Qrimagedecoder.cpp include/Qrimagedecoder.hpp
		QML_FILES
		qml/QrQmlCamera.qml
		qml/QrCam.qml
		qml/QrTextCamPop.qml
		RESOURCE_PREFIX
		"/esterVtech.com/imports"
		OUTPUT_TARGETS out_targets_var
		OUTPUT_DIRECTORY
		${CMAKE_BINARY_DIR}/Esterv/CustomControls/QrDec
		IMPORT_PATH ${CMAKE_BINARY_DIR} ${CMAKE_INSTALL_LIBDIR}
		)

	target_include_directories(QtQrDec PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}>")

	target_link_libraries(QtQrDec PUBLIC Qt6::Gui Qt6::Quick QrDec $<TARGET_NAME_IF_EXISTS:Qt6::Multimedia>
		EstervDesigns::SimpleStyle EstervDesigns::customControls
		$<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::SimpleStyle,TYPE>,STATIC_LIBRARY>:EstervDesigns::SimpleStyleplugin>
		$<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::customControls,TYPE>,STATIC_LIBRARY>:EstervDesigns::customControlsplugin>)

	install(TARGETS QtQrDec ${out_targets_var}
		EXPORT ${PROJECT_NAME}-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT QtQrDec
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}
		COMPONENT QtQrDec
		)
	install(DIRECTORY ${CMAKE_BINARY_DIR}/Esterv/CustomControls/QrDec
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/Esterv
		COMPONENT QtQrDec
		)

	install(TARGETS QtQrDecplugin
		EXPORT ${PROJECT_NAME}-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/Esterv/CustomControls/QrDec
		COMPONENT QtQrDec
		)

	if(EMSCRIPTEN)
		target_compile_definitions(QtQrDec PRIVATE USE_EMSCRIPTEN)
	endif(EMSCRIPTEN)
else(Qt6_FOUND AND TARGET QrDec)
	message(STATUS "The QML Module for QRCODE decoding will not be built")
endif(Qt6_FOUND AND TARGET QrDec)
