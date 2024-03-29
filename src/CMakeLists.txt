# Assuming this is the CMakeLists.txt inside the 'src' directory

# Create a_ list of header files.
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")

# Create a_ list of source files.
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Add a_ library target called 'classes' to be built from the source and header files.
add_library(classes ${HEADER_LIST} ${SOURCE_LIST}
        ../test/test.cpp)

# Specify include directories for the 'classes' target.
# We use PROJECT_SOURCE_DIR assuming the 'include' directory is at the root project level.
target_include_directories(classes PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Organize the header files in the IDE under 'Header Files' group.
source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)
