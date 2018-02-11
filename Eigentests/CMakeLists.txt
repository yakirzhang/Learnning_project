add_executable(test_eigen metrix1.cpp)
find_package(Eigen3)
target_include_directories(test_eigen PUBLIC ${EIGEN3_INCLUDE_DIR})
target_link_libraries(test_eigen PUBLIC ${EIGEN3_LIBRARIES}  gtest)
