cmake_minimum_required(VERSION 3.27)
project(RayTracerV2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3")

add_subdirectory(src)
add_subdirectory(main)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
    AND BUILD_TESTING)
    add_subdirectory(test)
endif ()
add_subdirectory(test)
