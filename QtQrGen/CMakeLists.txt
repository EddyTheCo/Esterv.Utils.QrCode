find_package(Qt6 COMPONENTS Core Gui Qml Quick OPTIONAL_COMPONENTS Svg)

if (Qt6_FOUND AND TARGET QrGen)
	FetchContent_Declare(
		EstervDesigns
		GIT_REPOSITORY https://github.com/EddyTheCo/MyDesigns.git
		GIT_TAG v1.2.0
		FIND_PACKAGE_ARGS 1.2 COMPONENTS SimpleStyle CustomControls CONFIG
		)
	FetchContent_MakeAvailable(EstervDesigns)
	qt_standard_project_setup()
	qt6_add_qml_module(QtQrGen
		URI  Esterv.CustomControls.QrGen
		VERSION ${VERSION}
		SOURCES Qrimageprovider.cpp include/Qrimageprovider.hpp
		QML_FILES
		"qml/QrGenImage.qml"
		"qml/QrGenPop.qml"
		"qml/QrText.qml"
		RESOURCE_PREFIX
		"/esterVtech.com/imports"
		OUTPUT_TARGETS out_targets_var
		OUTPUT_DIRECTORY
		${CMAKE_BINARY_DIR}/Esterv/CustomControls/QrGen
		IMPORT_PATH ${CMAKE_BINARY_DIR} 
		)

	add_library(${PROJECT_NAME}::QtQrGen ALIAS QtQrGen)
	add_library(${PROJECT_NAME}::QtQrGenplugin ALIAS QtQrGenplugin)
	set_target_properties(QtQrGen PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_MAJOR})
	target_compile_definitions(QtQrGen PRIVATE WINDOWS_GEN)

	qt6_add_shaders(QtQrGen "esterVtech.com.imports.QtQrGen.shaders"
		BATCHABLE
		PRECOMPILE
		OPTIMIZED
		OUTPUT_TARGETS out_targets_var2
		PREFIX
		"/esterVtech.com/imports/Designs"
		FILES
		"frag/qrscanner.frag"
		)

	target_include_directories(QtQrGen PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Esterv/>")
	if(NOT TARGET Qt6::Svg)
		FetchContent_Declare(
			qtsvg
			GIT_REPOSITORY https://github.com/qt/qtsvg.git
			GIT_TAG 6.6.0
			)
		FetchContent_MakeAvailable(qtsvg)
	endif()


	target_link_libraries(QtQrGen PUBLIC
		Qt6::Quick
		)
	target_link_libraries(QtQrGen PRIVATE QrGen Qt6::Core Qt6::Gui Qt6::Qml Qt6::Svg
		EstervDesigns::SimpleStyle EstervDesigns::CustomControls
		$<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::SimpleStyle,TYPE>,STATIC_LIBRARY>:EstervDesigns::SimpleStyleplugin>
		$<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::CustomControls,TYPE>,STATIC_LIBRARY>:EstervDesigns::CustomControlsplugin>)

	install(TARGETS QtQrGen ${out_targets_var} ${out_targets_var2}
		EXPORT ${PROJECT_NAME}-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT QtQrGen
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv
		COMPONENT QtQrGen
		)
	install(DIRECTORY ${CMAKE_BINARY_DIR}/Esterv/CustomControls/QrGen
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/Esterv/CustomControls
		COMPONENT QtQrGen
		)

	install(TARGETS QtQrGenplugin
		EXPORT ${PROJECT_NAME}-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/Esterv/CustomControls/QrGen
		COMPONENT QtQrGen
		)
	if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
		add_subdirectory(examples)
	endif(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
endif(Qt6_FOUND AND TARGET QrGen)
