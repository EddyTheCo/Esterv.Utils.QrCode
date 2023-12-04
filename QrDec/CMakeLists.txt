find_package(OpenCV COMPONENTS core objdetect imgproc flann features2d calib3d )

option(OpenCV_DOWNLOAD "On or off" ON)
if(NOT OpenCV_FOUND AND OpenCV_DOWNLOAD)
	set(builturl "https://github.com/EddyTheCo/install-OpenCV-action/releases/latest/download/OpenCV-ubuntu-latest-wasm_false-android_none.tar")
	if(WIN32)
		set(builturl "https://github.com/EddyTheCo/install-OpenCV-action/releases/latest/download/OpenCV-windows-latest-wasm_false-android_none.tar")
	endif(WIN32)
	if (APPLE)
		set(builturl "https://github.com/EddyTheCo/install-OpenCV-action/releases/latest/download/OpenCV-macos-latest-wasm_false-android_none.tar")
	endif(APPLE)
	if(EMSCRIPTEN)
		set(builturl "https://github.com/EddyTheCo/install-OpenCV-action/releases/latest/download/OpenCV-ubuntu-latest-wasm_true-android_none.tar")
	endif(EMSCRIPTEN)
	if(ANDROID)
		set(builturl "https://github.com/EddyTheCo/install-OpenCV-action/releases/latest/download/OpenCV-ubuntu-latest-wasm_false-android_${ANDROID_ABI}.tar")
	endif(ANDROID)
	FetchContent_Declare(
		OpenCV
		DOWNLOAD_EXTRACT_TIMESTAMP true
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
		if(ANDROID)
			set(OpenCV_DIR ${opencv_SOURCE_DIR}/sdk/native/jni)
		endif(ANDROID)
		find_package(OpenCV COMPONENTS core objdetect imgproc flann features2d calib3d )
	endif()
	if(OpenCV_FOUND AND NOT ANDROID AND NOT EMSCRIPTEN)
		install(IMPORTED_RUNTIME_ARTIFACTS ${OpenCV_LIBS}
			DESTINATION ${CMAKE_INSTALL_LIBDIR}
			COMPONENT Qr
			)
	endif()
endif()



if(OpenCV_FOUND)
	add_library(QrDec qrcodedec.cpp)

	add_library(${PROJECT_NAME}::QrDec ALIAS QrDec)
	target_include_directories(QrDec PUBLIC $<BUILD_INTERFACE:${OpenCV_INCLUDE_DIRS}>)
	target_link_libraries(QrDec PUBLIC ${OpenCV_LIBS})

	target_include_directories(QrDec PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}>")
	install(TARGETS QrDec
		EXPORT ${PROJECT_NAME}-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT QrDec
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}
		COMPONENT QrDec
		)
else()
	message(STATUS "The QRCODE decoding library will not be built")
endif(OpenCV_FOUND)
