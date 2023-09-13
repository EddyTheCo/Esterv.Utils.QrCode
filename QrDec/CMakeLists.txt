
find_package( OpenCV QUIET)
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
