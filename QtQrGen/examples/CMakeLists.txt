if(BUILD_EXAMPLES)
	if(EMSCRIPTEN)
		find_package(Qt6 REQUIRED COMPONENTS QuickControls2)
		find_package(EstervDesigns 0.4 REQUIRED COMPONENTS Controls CONFIG )
	endif(EMSCRIPTEN)

        foreach(example "image" 
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
                target_link_libraries(${example} PRIVATE Qt::Gui Qt::Qml Qt::Quick QtQrGen
                        $<$<STREQUAL:$<TARGET_PROPERTY:QtQrGen,TYPE>,STATIC_LIBRARY>:QtQrGenplugin>
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
