
project(QrGeneration  LANGUAGES CXX)

add_library(QrGen src/qrcodegen.cpp src/utils.cpp include/qrcodegen.hpp)

set_target_properties(QrGen PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_compile_features(QrGen PUBLIC cxx_std_11)

target_include_directories(QrGen PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>")

install(TARGETS QrGen 
	EXPORT ${PROJECT_NAME}-config 
	DESTINATION ${CMAKE_INSTALL_LIBDIR}
	COMPONENT Qr
	)
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
	COMPONENT Qr
	)

if(BUILD_DOCS)
	get_target_property(build_docs cmake_build_docs SOURCES)
	include(${build_docs})
endif()
