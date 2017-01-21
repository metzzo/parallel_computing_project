cmake_minimum_required(VERSION 3.6)
project(Project)

set(SOURCE_FILES sequential/sequential_solution.c pthread/pthread_solution.c tests/test_runner.c definitions/shared.h sequential/sequential_solution.h tests/test_runner.h definitions/shared.c tests/test_cases/test_simple_matrix.c tests/test_cases/test_big_matrix.c tests/test_cases/test_big_matrix.h tests/test_cases/test_simple_matrix.h tests/test_cases/test_constant_matrix.c tests/test_cases/test_constant_matrix.h openmp/openmp_solution.c openmp/openmp_solution.h cilk/cilk_solution.c cilk/cilk_solution.h tests/test_generator.c tests/test_generator.h tests/test_stencil.c tests/test_stencil.h pthread/pthread_barrier_osx.c pthread/pthread_barrier_osx.h)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -fcilkplus")
set(CMAKE_C_COMPILER /usr/local/bin/gcc-6)

include_directories(/usr/local/Cellar/libiomp/20150701/inclu‌​de/libiomp)

find_package(Threads)

add_executable(Project ${SOURCE_FILES})
target_link_libraries(Project ${CMAKE_THREAD_LIBS_INIT})
