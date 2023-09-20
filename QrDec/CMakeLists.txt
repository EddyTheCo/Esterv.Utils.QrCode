find_package(OpenCV)
if(NOT OpenCV_FOUND AND NOT ANDROID)
	set(builturl "https://github.com/EddyTheCo/install-OpenCV-action/releases/download/v0.0.14/OpenCV-ubuntu-latest-wasm_false.tar")
	if(WIN32)
		set(builturl "https://github.com/EddyTheCo/install-OpenCV-action/releases/download/v0.0.14/OpenCV-windows-latest-wasm_false.tar")
	endif(WIN32)
	if (APPLE)
		set(builturl "https://github.com/EddyTheCo/install-OpenCV-action/releases/download/v0.0.14/OpenCV-macos-latest-wasm_false.tar")
	endif(APPLE)	
	if(EMSCRIPTEN)
		set(builturl "https://github.com/EddyTheCo/install-OpenCV-action/releases/download/v0.0.14/OpenCV-ubuntu-latest-wasm_true.tar")
	endif(EMSCRIPTEN)
	FetchContent_Declare(
		OpenCV
		URL  ${builturl}
		)
	FetchContent_GetProperties(OpenCV)
	if(NOT OpenCV_POPULATED)
		message(STATUS "OpenCV prebuilt will be downloaded from ${builturl} if not found on the system")
		FetchContent_Populate(OpenCV)
		message(STATUS "OpenCV is installed in ${opencv_SOURCE_DIR}")
		set(OpenCV_DIR ${opencv_SOURCE_DIR}/lib/cmake/opencv4)
		if(WIN32)
			set(OpenCV_DIR ${opencv_SOURCE_DIR})
		endif(WIN32)
		find_package(OpenCV)
	endif()
endif()



if(OpenCV_FOUND)

	add_library(QrDec qrcodedec.cpp)

	set_target_properties(QrDec PROPERTIES POSITION_INDEPENDENT_CODE ON)

	target_include_directories(QrDec PRIVATE ${OpenCV_INCLUDE_DIRS})
	target_link_libraries(QrDec PRIVATE ${OpenCV_LIBS})

	target_include_directories(QrDec PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qrCode>")

	install(TARGETS QrDec
		EXPORT qrCodeTargets
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT Qr
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qrCode
		COMPONENT Qr
		)
else()
	message(STATUS "OpenCV was not found")
endif(OpenCV_FOUND)
