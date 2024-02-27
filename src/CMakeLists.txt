file(GLOB HEADER_LIST "../include/*.h")
file(GLOB SOURCE_LIST "*.cpp")

add_library(classes ${HEADER_LIST} ${SOURCE_LIST}
        )

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)