
if(EMSCRIPTEN)
    find_package(Qt6 COMPONENTS Core Gui Qml Quick ShaderTools)
else()
    find_package(Qt6 COMPONENTS Core Gui Qml Quick ShaderTools Multimedia)
endif(EMSCRIPTEN)

FetchContent_Declare(
    EstervDesigns
    GIT_REPOSITORY https://github.com/EddyTheCo/MyDesigns.git
    GIT_TAG develop
    FIND_PACKAGE_ARGS 1.0 COMPONENTS SimpleStyle CustomControls CONFIG
)
FetchContent_MakeAvailable(EstervDesigns)


if (Qt6_FOUND AND TARGET QrDec)
    qt_standard_project_setup()
    qt6_add_qml_module(QtQrDec
        URI  Esterv.CustomControls.QrDec
        VERSION 1.0
        SOURCES Qrimagedecoder.cpp include/Qrimagedecoder.hpp
        QML_FILES
        "qml/QrCam.qml"
        "qml/QrDecPop.qml"
        "qml/QrTextField.qml"
        RESOURCE_PREFIX
        "/esterVtech.com/imports"
        OUTPUT_TARGETS out_targets_var
        OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Esterv/CustomControls/QrDec
        IMPORT_PATH ${CMAKE_BINARY_DIR} ${CMAKE_INSTALL_LIBDIR}
    )

add_library(${PROJECT_NAME}::QtQrDec ALIAS QtQrDec)
add_library(${PROJECT_NAME}::QtQrDecplugin ALIAS QtQrDecplugin)


qt6_add_shaders(QtQrDec "esterVtech.com.imports.QtQrDec.shaders"
    BATCHABLE
    PRECOMPILE
    OPTIMIZED
    OUTPUT_TARGETS out_targets_var2
    PREFIX
    "/esterVtech.com/imports/Designs"
    FILES
    "frag/qrscanner.frag"
)
target_include_directories(QtQrDec PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}>")
if(EMSCRIPTEN)
    target_compile_definitions(QtQrDec PRIVATE USE_EMSCRIPTEN)
else()
    target_link_libraries(QtQrDec PUBLIC Qt6::Multimedia)
endif(EMSCRIPTEN)
target_link_libraries(QtQrDec PUBLIC Qt6::Gui Qt6::Quick QrDec
    EstervDesigns::SimpleStyle EstervDesigns::customControls
    $<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::SimpleStyle,TYPE>,STATIC_LIBRARY>:EstervDesigns::SimpleStyleplugin>
    $<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::customControls,TYPE>,STATIC_LIBRARY>:EstervDesigns::customControlsplugin>)

install(TARGETS QtQrDec ${out_targets_var} ${out_targets_var2}
    EXPORT ${PROJECT_NAME}-config
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT QtQrDec
)
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}
    COMPONENT QtQrDec
)
install(DIRECTORY ${CMAKE_BINARY_DIR}/Esterv/CustomControls/QrDec
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/Esterv/CustomControls
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
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(examples)
endif(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
else(Qt6_FOUND AND TARGET QrDec)
    message(STATUS "The QML Module for QRCODE decoding will not be built")
endif(Qt6_FOUND AND TARGET QrDec)
