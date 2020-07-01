# License: MIT. See LICENSE in root directory.
# Date: 2020/06/27

cmake_minimum_required(VERSION 3.1.0)

project("ensemble-raw-memory" LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("${CMAKE_CURRENT_LIST_DIR}/inc")

add_compile_definitions("uchar=unsigned char")
add_compile_definitions("uint=unsigned int")

set(ENSEMBLE_RAW_MEMORY_LIB "ensemble-raw-memory-lib")
add_library(${ENSEMBLE_RAW_MEMORY_LIB} STATIC "")
target_sources(
    ${ENSEMBLE_RAW_MEMORY_LIB}
    PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/src/ensemble/raw-memory.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/inc/ensemble/raw-memory.hpp"
)

if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug")
    set(ENSEMBLE_RAW_MEMORY_EXE "ensemble-raw-memory-exe")
    add_executable(${ENSEMBLE_RAW_MEMORY_EXE} "${CMAKE_CURRENT_LIST_DIR}/test/main.cpp")
    target_link_libraries(${ENSEMBLE_RAW_MEMORY_EXE} ${ENSEMBLE_RAW_MEMORY_LIB})
endif ()
