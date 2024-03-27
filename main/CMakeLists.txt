include_directories(${assimp_SOURCE_DIR}/include)
add_executable(RayTracerV2 main.cpp)

target_link_libraries(RayTracerV2 PUBLIC classes assimp)
target_include_directories(RayTracerV2 PUBLIC "${PROJECT_SOURCE_DIR}/include")