cmake_minimum_required(VERSION 3.15)
project(WorldTimeLib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
else()
    message(FATAL_ERROR "VCPKG_ROOT environment variable is not set")
endif()

find_package(CURL REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

add_library(WorldTimeLib STATIC
    WorldTimeApi.cpp
    WorldTimeApi.h
)

target_include_directories(WorldTimeLib PRIVATE ${CURL_INCLUDE_DIR} ${JSONCPP_INCLUDE_DIRS})

target_link_libraries(WorldTimeLib PRIVATE CURL::libcurl jsoncpp_lib)
