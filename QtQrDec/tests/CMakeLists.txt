cmake_minimum_required(VERSION 3.16)

include(local_conf.cmake OPTIONAL)


find_package(Qt6 REQUIRED COMPONENTS Multimedia)
project(testing VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(app
	test.cpp
	)
target_link_libraries(app PRIVATE QtQrDec Qt6::Gui  Qt6::Multimedia)
qt_add_qml_module(app
        URI appqml
	VERSION 1.0
	QML_FILES main.qml
        RESOURCES pics/qrcode-feature.jpg
	)
set_target_properties(app PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
	)

target_compile_definitions(app
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
