cmake_minimum_required(VERSION 3.16)
project(qmlqr LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
include(local_conf.cmake OPTIONAL)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_library(QtQrDec Qrimagedecoder.cpp include/Qrimagedecoder.hpp)

set_target_properties(QtQrDec PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_include_directories(QtQrDec PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        "$<INSTALL_INTERFACE:include>")
target_link_libraries(QtQrDec PUBLIC
    Qt6::Core
    Qt6::Qml
)
target_link_libraries(QtQrDec PRIVATE
    QrDec
    Qt6::Gui
    Qt6::Quick
)


install(TARGETS QtQrDec EXPORT QtQrDecTargets LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/)

install(EXPORT QtQrDecTargets
        FILE QtQrDecTargets.cmake
        NAMESPACE qr::
        DESTINATION lib/cmake/QtQrDec
        )
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/QtQrDecConfig.cmake"
        INSTALL_DESTINATION "lib/cmake/QtQrDec"
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
        )
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/QtQrDecConfigVersion.cmake"
        VERSION "0.1.1.0"
        COMPATIBILITY AnyNewerVersion
        )
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QtQrDecConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QtQrDecConfigVersion.cmake
        DESTINATION lib/cmake/QtQrDec
        )
export(EXPORT QtQrDecTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/QtQrDecTargets.cmake"
        )

        include(CTest)


        add_subdirectory(tests)

