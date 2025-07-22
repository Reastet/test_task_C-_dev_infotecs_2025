cmake_minimum_required(VERSION 3.14)
project(FirstExec VERSION 1.0.0 LANGUAGES CXX)




set(SOURCE_FILES
    source/main.cpp
    source/i_o_system.cpp
    source/logger.cpp
    source/thread_controller.cpp
    source/buffer_controller.cpp
)
include_directories(include)


set(LIBRARY_PATH "../../library/build/lib")
set(LIBRARY_NAME "LogWriter-static") 
add_library(${LIBRARY_NAME} STATIC IMPORTED)
set_target_properties(${LIBRARY_NAME} PROPERTIES
    IMPORTED_LOCATION ${LIBRARY_PATH}/${CMAKE_STATIC_LIBRARY_PREFIX}${LIBRARY_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX}
)

add_executable(main ${SOURCE_FILES})


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


target_link_libraries(main PRIVATE ${LIBRARY_NAME} pthread)


link_directories(${LIBRARY_PATH})

