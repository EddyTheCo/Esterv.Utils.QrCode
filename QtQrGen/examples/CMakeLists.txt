if(BUILD_EXAMPLES)
  include(InstallRequiredSystemLibraries)
  if(EMSCRIPTEN OR ANDROID)
    find_package(Qt6 REQUIRED COMPONENTS QuickControls2)
    find_package(EstervDesigns 1.2 REQUIRED COMPONENTS FlatControl CONFIG)
  endif(EMSCRIPTEN OR ANDROID)

  foreach(example "Image" "Text")
    qt_add_executable(${example} ${example}.cpp)

    qt6_add_qml_module(
      ${example}
      URI
      Examples${example}
      VERSION
      1.0
      QML_FILES
      "qml/${example}.qml"
      RESOURCE_PREFIX
      "/esterVtech.com/imports"
      IMPORT_PATH
      ${CMAKE_BINARY_DIR})
    target_link_libraries(
      ${example}
      PRIVATE
        Qt::Gui
        Qt::Qml
        Qt::Quick
        QtQrGen
        $<$<STREQUAL:$<TARGET_PROPERTY:QtQrGen,TYPE>,STATIC_LIBRARY>:QtQrGenplugin>
    )

    set_target_properties(${example} PROPERTIES WIN32_EXECUTABLE ON
                                                MACOSX_BUNDLE ON)
    install(
      TARGETS ${example}
      COMPONENT ${PROJECT_NAME}-examples
      BUNDLE DESTINATION . COMPONENT ${PROJECT_NAME}-examples
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
              COMPONENT ${PROJECT_NAME}-examples)
    if(QTDEPLOY)
      qt_generate_deploy_qml_app_script(TARGET ${example} OUTPUT_SCRIPT
                                        deploy_script)
      install(SCRIPT ${deploy_script} COMPONENT ${PROJECT_NAME}-examples)
    endif(QTDEPLOY)
    if(ANDROID)
      set_property(
        TARGET ${example}
        APPEND
        PROPERTY QT_ANDROID_MIN_SDK_VERSION 30)
      set_property(
        TARGET ${example}
        APPEND
        PROPERTY QT_ANDROID_TARGET_SDK_VERSION 34)
      set_property(
        TARGET ${example}
        APPEND
        PROPERTY QT_ANDROID_SDK_BUILD_TOOLS_REVISION 34.0.0)

      FetchContent_Declare(
        android_openssl
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
      )
      FetchContent_GetProperties(android_openssl)
      if(NOT android_openssl_POPULATED)
        FetchContent_Populate(android_openssl)
        include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)
        add_android_openssl_libraries(${example})
      endif(NOT android_openssl_POPULATED)
    endif(ANDROID)
    if(EMSCRIPTEN OR ANDROID)
      target_link_libraries(
        ${example}
        PRIVATE
          EstervDesigns::FlatControl
          Qt6::QuickControls2
          $<$<STREQUAL:$<TARGET_PROPERTY:Esterv::FlatControl,TYPE>,STATIC_LIBRARY>:Esterv::FlatControlplugin>
      )
      target_compile_definitions(${example}
                                 PRIVATE FORCE_STYLE="Esterv.Controls.Flat")
    endif(EMSCRIPTEN OR ANDROID)
  endforeach()
endif(BUILD_EXAMPLES)
