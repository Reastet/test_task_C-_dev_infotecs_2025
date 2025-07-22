cmake_minimum_required(VERSION 3.14)
project(SecExec VERSION 1.0.0 LANGUAGES CXX)




set(SOURCE_FILES
    source/main.cpp
    source/tcp_serv.cpp
)
include_directories(include)


add_executable(main ${SOURCE_FILES})


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


target_link_libraries(main PRIVATE ${LIBRARY_NAME} pthread)


link_directories(${LIBRARY_PATH})