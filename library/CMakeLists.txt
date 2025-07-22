cmake_minimum_required(VERSION 3.14)
project(LogWriter VERSION 1.0.0 LANGUAGES CXX)
set(SOURCE_LIB ${CMAKE_SOURCE_DIR}/source/log_writer.cpp)
add_library(LogWriter-shared SHARED ${SOURCE_LIB})
add_library(LogWriter-static STATIC ${SOURCE_LIB})

target_include_directories(LogWriter-shared PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(LogWriter-static PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_target_properties(LogWriter-shared PROPERTIES  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(LogWriter-static PROPERTIES  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
   ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)