
add_executable(RayTracerV2 main.cpp)

target_link_libraries(RayTracerV2 PUBLIC classes)
target_include_directories(RayTracerV2 PUBLIC "${PROJECT_SOURCE_DIR}/include")