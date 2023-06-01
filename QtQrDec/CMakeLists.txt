
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_library(QtQrDec Qrimagedecoder.cpp include/Qrimagedecoder.hpp)

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

install(TARGETS QtQrDec 
	EXPORT ${PROJECT_NAME}-config 
	DESTINATION ${CMAKE_INSTALL_LIBDIR}
	COMPONENT QtQr
install(DIRECTORY include/ 
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
	COMPONENT QtQr
	)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
	if(BUILD_TESTING)
		add_subdirectory(tests)
	endif(BUILD_TESTING)
endif(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)


