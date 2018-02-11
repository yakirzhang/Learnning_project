# GTest
#find_package(GTest REQUIRED)
add_library(gtest INTERFACE)
message(STATUS ${THIRDPARTY_LIBRARY}/include/gtests)
target_include_directories(gtest INTERFACE ${THIRDPARTY_LIBRARY}/include/gtests)
target_link_libraries(gtest INTERFACE ${THIRDPARTY_LIBRARY}/libs/gtests/libgtest.a ${THIRDPARTY_LIBRARY}/libs/gtests/libgtest_main.a pthread)
