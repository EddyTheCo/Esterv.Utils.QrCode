project(QrGeneration  LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Gui Qml Quick Svg)
if (Qt6_FOUND)
	qt_add_library(QtQrGen Qrimageprovider.cpp include/Qrimageprovider.hpp)

	add_library(qrCode::QtQrGen ALIAS QtQrGen)
	target_include_directories(QtQrGen PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qrCode>")


	target_link_libraries(QtQrGen PUBLIC
		Qt6::Quick
		)
	target_link_libraries(QtQrGen PRIVATE
		QrGen
		Qt6::Core
		Qt6::Gui
		Qt6::Qml
		Qt6::Quick
		Qt6::Svg
		)

	install(TARGETS QtQrGen
		EXPORT qrCode-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT QtQr
		EXCLUDE_FROM_ALL
		)
	install(DIRECTORY include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qrCode
		COMPONENT QtQr
		EXCLUDE_FROM_ALL
		)
endif(Qt6_FOUND)
if(BUILD_DOCS)
	get_target_property(build_docs cmake_build_docs SOURCES)
	include(${build_docs})
endif()
