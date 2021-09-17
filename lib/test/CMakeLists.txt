find_package(GTest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_executable(test_process_manager test_process_manager.cpp)

target_link_libraries(test_process_manager gtest pthread process_manager)