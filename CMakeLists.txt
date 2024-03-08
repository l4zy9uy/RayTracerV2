cmake_minimum_required(VERSION 3.27)
project(RayTracerV2)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(src)
add_subdirectory(main)
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
    AND BUILD_TESTING)
    add_subdirectory(test)
endif ()
add_subdirectory(test)
