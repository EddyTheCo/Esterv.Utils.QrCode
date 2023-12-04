find_package(Qt6 COMPONENTS Core Gui Qml Quick OPTIONAL_COMPONENTS Svg)

if (Qt6_FOUND)
	qt_standard_project_setup()
	qt6_add_qml_module(QtQrGen
		URI  Esterv.CustomControls.QrGen
		VERSION ${VERSION}
		SOURCES Qrimageprovider.cpp include/Qrimageprovider.hpp
		QML_FILES
		"qml/AddressQr.qml"
		"qml/PayQrPop.qml"
		"qml/QrLabel.qml"
		RESOURCE_PREFIX
		"/esterVtech.com/imports"
		OUTPUT_TARGETS out_targets_var
		OUTPUT_DIRECTORY
		${CMAKE_BINARY_DIR}/Esterv/CustomControls/QrGen
		IMPORT_PATH ${CMAKE_BINARY_DIR} ${CMAKE_INSTALL_LIBDIR}
		)


	target_include_directories(QtQrGen PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}>")
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
	target_link_libraries(QtQrGen PRIVATE QrGen Qt6::Core Qt6::Gui Qt6::Qml Qt6::Svg
		EstervDesigns::SimpleStyle EstervDesigns::customControls
		$<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::SimpleStyle,TYPE>,STATIC_LIBRARY>:EstervDesigns::SimpleStyleplugin>
		$<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::customControls,TYPE>,STATIC_LIBRARY>:EstervDesigns::customControlsplugin>)

	install(TARGETS QtQrGen ${out_targets_var}
		EXPORT ${PROJECT_NAME}-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT QtQrGen
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}
		COMPONENT QtQrGen
		)
	install(DIRECTORY ${CMAKE_BINARY_DIR}/Esterv/CustomControls/QrGen
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/Esterv
		COMPONENT QtQrGen
		)

	install(TARGETS QtQrGenplugin
		EXPORT ${PROJECT_NAME}-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/Esterv/CustomControls/QrGen
		COMPONENT QtQrGen
		)
endif(Qt6_FOUND)
