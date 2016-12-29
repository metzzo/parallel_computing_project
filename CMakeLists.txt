cmake_minimum_required(VERSION 3.6)
project(Project)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES sequential/sequential_solution.c pthread/pthread_solution.c tests/test_runner.c definitions/shared.h sequential/sequential_solution.h tests/test_runner.h definitions/shared.c tests/test_cases/test_simple_matrix.c tests/test_cases/test_big_matrix.c tests/test_cases/test_big_matrix.h tests/test_cases/test_simple_matrix.h tests/test_cases/test_constant_matrix.c tests/test_cases/test_constant_matrix.h)

find_package(Threads)
add_executable(Project ${SOURCE_FILES} sequential/sequential_solution.c)
target_link_libraries(Project ${CMAKE_THREAD_LIBS_INIT})
