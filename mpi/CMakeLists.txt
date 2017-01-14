cmake_minimum_required(VERSION 3.6)
project(mpi)

set(SOURCE_FILES mpi_solution.c mpi_solution.h ../sequential/sequential_solution.c ../definitions/shared.h ../sequential/sequential_solution.h ../definitions/shared.c ../tests/test_generator.c ../tests/test_generator.h ../tests/test_stencil.c ../tests/test_stencil.h)
set(CMAKE_C_COMPILER /usr/local/bin/mpicc)

add_executable(mpi ${SOURCE_FILES})
