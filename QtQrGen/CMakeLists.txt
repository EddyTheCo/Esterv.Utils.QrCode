cmake_minimum_required(VERSION 3.16)
project(qmlqr LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
include(local_conf.cmake OPTIONAL)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Core5Compat Svg)

qt_add_library(QtQrGen Qrimageprovider.cpp include/Qrimageprovider.hpp)

set_target_properties(QtQrGen PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_include_directories(QtQrGen PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        "$<INSTALL_INTERFACE:include>")
target_link_libraries(QtQrGen PUBLIC
    Qt6::Quick
)
target_link_libraries(QtQrGen PRIVATE
    QrGen
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Core5Compat
    Qt6::Svg
)

install(TARGETS QtQrGen EXPORT QtQrGenTargets LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/)

install(EXPORT QtQrGenTargets
        FILE QtQrGenTargets.cmake
        NAMESPACE qr::
        DESTINATION lib/cmake/QtQrGen
        )
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/QtQrGenConfig.cmake"
        INSTALL_DESTINATION "lib/cmake/QtQrGen"
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
        )
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/QtQrGenConfigVersion.cmake"
        VERSION "0.1.1.0"
        COMPATIBILITY AnyNewerVersion
        )
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QtQrGenConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QtQrGenConfigVersion.cmake
        DESTINATION lib/cmake/QtQrGen
        )
export(EXPORT QtQrGenTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/QtQrGenTargets.cmake"
        )
