project(bb-grove)
cmake_minimum_required(VERSION 3.0)
aux_source_directory(. SRC_LIST)
find_package(Threads)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} m ${CMAKE_THREAD_LIBS_INIT})






