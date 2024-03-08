find_package(Catch2 3 REQUIRED)

add_executable(test test.cpp)

target_compile_features(test PRIVATE cxx_std_17)

target_link_libraries(test PRIVATE classes Catch2::Catch2WithMain)
add_test(NAME testlibtest COMMAND test)