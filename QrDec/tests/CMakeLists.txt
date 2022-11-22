cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(module_test VERSION 0.1 DESCRIPTION "diferent tests for the library" LANGUAGES CXX)



add_executable(load_from_file load_from_file.cpp)
target_link_libraries(load_from_file PRIVATE QrDec)
add_test(NAME load_from_file COMMAND load_from_file ${CMAKE_CURRENT_BINARY_DIR}/qrcode-feature.jpg)


target_include_directories(load_from_file PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(load_from_file PRIVATE ${OpenCV_LIBS})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/qrcode-feature.jpg	
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
