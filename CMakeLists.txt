cmake_minimum_required(VERSION 3.10)
PROJECT(tncc)

add_subdirectory(deps/fmt)

if( NOT ${CMAKE_BUILD_TYPE} MATCHES "Debug" )
    set(CMAKE_BUILD_TYPE "Release")
else()
    add_definitions(-DDEBUG)
endif()

if(MSVC)
    set( CMAKE_CXX_FLAGS_DEBUG_INIT "/W4")
    set( CMAKE_CXX_FLAGS_RELEASE_INIT "/O2")
else()
    set( CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -Wpedantic -g")
    set( CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")
endif()

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Select other build directory for example build/" )
endif()

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

set(CMAKE_CXX_STANDARD 20)


file(GLOB PROJECT_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_link_libraries(${PROJECT_NAME} fmt)