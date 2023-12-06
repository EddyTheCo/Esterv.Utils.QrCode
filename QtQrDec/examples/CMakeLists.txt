if(BUILD_EXAMPLES)
	if(EMSCRIPTEN)
		find_package(Qt6 REQUIRED COMPONENTS QuickControls2)
		find_package(EstervDesigns 0.4 REQUIRED COMPONENTS Controls CONFIG )
	endif(EMSCRIPTEN)

	foreach(example "qrcam"
			)
		qt_add_executable(${example} ${example}.cpp )

		qt6_add_qml_module(${example}
			URI  E${example}
			VERSION 1.0
			QML_FILES
			"qml/${example}.qml"
			RESOURCE_PREFIX
			"/esterVtech.com/imports"
			IMPORT_PATH ${CMAKE_BINARY_DIR}
			)
                    if(NOT EMSCRIPTEN)
                        target_link_libraries(${example} PRIVATE Qt6::Multimedia)
                    endif(NOT EMSCRIPTEN)
                target_link_libraries(${example} PRIVATE Qt::Gui Qt::Qml Qt::Quick $<TARGET_NAME_IF_EXISTS:Qt6::Multimedia> QtQrDec
                        $<$<STREQUAL:$<TARGET_PROPERTY:QtQrDec,TYPE>,STATIC_LIBRARY>:QtQrDecplugin>
			)

		set_target_properties(${example} PROPERTIES
			WIN32_EXECUTABLE ON
			MACOSX_BUNDLE ON
			)
		install(TARGETS ${example}
			BUNDLE  DESTINATION .
			DESTINATION ${CMAKE_INSTALL_BINDIR}
			)
		if(QTDEPLOY)
			qt_generate_deploy_qml_app_script(
				TARGET ${example}
				OUTPUT_SCRIPT deploy_script
				)
			install(SCRIPT ${deploy_script})
		endif(QTDEPLOY)
		if(EMSCRIPTEN)
			target_link_libraries(${example} PRIVATE EstervDesigns::FlatControl Qt6::QuickControls2
				$<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::FlatControl,TYPE>,STATIC_LIBRARY>:EstervDesigns::FlatControlplugin>
				)
			target_compile_definitions(${example} PRIVATE FORCE_STYLE="Esterv.Controls.Flat")
		endif(EMSCRIPTEN)
	endforeach()
endif(BUILD_EXAMPLES)
