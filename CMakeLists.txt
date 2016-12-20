cmake_minimum_required(VERSION 3.6)
project(Project)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES sequential/sequential.c pthread/pthread_solution.c tests/test_runner.c definitions/shared.h sequential/sequential.h tests/test_runner.h definitions/shared.c)

find_package(Threads)
add_executable(Project ${SOURCE_FILES} sequential/sequential.c)
target_link_libraries(Project ${CMAKE_THREAD_LIBS_INIT})
