# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rfischer/Dropbox/Studium_Sem5/PC/Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project.dir/flags.make

CMakeFiles/Project.dir/tests/benchmark_runner.c.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/tests/benchmark_runner.c.o: ../tests/benchmark_runner.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Project.dir/tests/benchmark_runner.c.o"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project.dir/tests/benchmark_runner.c.o   -c /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/tests/benchmark_runner.c

CMakeFiles/Project.dir/tests/benchmark_runner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project.dir/tests/benchmark_runner.c.i"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/tests/benchmark_runner.c > CMakeFiles/Project.dir/tests/benchmark_runner.c.i

CMakeFiles/Project.dir/tests/benchmark_runner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project.dir/tests/benchmark_runner.c.s"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/tests/benchmark_runner.c -o CMakeFiles/Project.dir/tests/benchmark_runner.c.s

CMakeFiles/Project.dir/tests/benchmark_runner.c.o.requires:

.PHONY : CMakeFiles/Project.dir/tests/benchmark_runner.c.o.requires

CMakeFiles/Project.dir/tests/benchmark_runner.c.o.provides: CMakeFiles/Project.dir/tests/benchmark_runner.c.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/tests/benchmark_runner.c.o.provides.build
.PHONY : CMakeFiles/Project.dir/tests/benchmark_runner.c.o.provides

CMakeFiles/Project.dir/tests/benchmark_runner.c.o.provides.build: CMakeFiles/Project.dir/tests/benchmark_runner.c.o


CMakeFiles/Project.dir/sequential/sequential_solution.c.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/sequential/sequential_solution.c.o: ../sequential/sequential_solution.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Project.dir/sequential/sequential_solution.c.o"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project.dir/sequential/sequential_solution.c.o   -c /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/sequential/sequential_solution.c

CMakeFiles/Project.dir/sequential/sequential_solution.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project.dir/sequential/sequential_solution.c.i"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/sequential/sequential_solution.c > CMakeFiles/Project.dir/sequential/sequential_solution.c.i

CMakeFiles/Project.dir/sequential/sequential_solution.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project.dir/sequential/sequential_solution.c.s"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/sequential/sequential_solution.c -o CMakeFiles/Project.dir/sequential/sequential_solution.c.s

CMakeFiles/Project.dir/sequential/sequential_solution.c.o.requires:

.PHONY : CMakeFiles/Project.dir/sequential/sequential_solution.c.o.requires

CMakeFiles/Project.dir/sequential/sequential_solution.c.o.provides: CMakeFiles/Project.dir/sequential/sequential_solution.c.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/sequential/sequential_solution.c.o.provides.build
.PHONY : CMakeFiles/Project.dir/sequential/sequential_solution.c.o.provides

CMakeFiles/Project.dir/sequential/sequential_solution.c.o.provides.build: CMakeFiles/Project.dir/sequential/sequential_solution.c.o


CMakeFiles/Project.dir/pthread/pthread_solution.c.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/pthread/pthread_solution.c.o: ../pthread/pthread_solution.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Project.dir/pthread/pthread_solution.c.o"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project.dir/pthread/pthread_solution.c.o   -c /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/pthread/pthread_solution.c

CMakeFiles/Project.dir/pthread/pthread_solution.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project.dir/pthread/pthread_solution.c.i"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/pthread/pthread_solution.c > CMakeFiles/Project.dir/pthread/pthread_solution.c.i

CMakeFiles/Project.dir/pthread/pthread_solution.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project.dir/pthread/pthread_solution.c.s"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/pthread/pthread_solution.c -o CMakeFiles/Project.dir/pthread/pthread_solution.c.s

CMakeFiles/Project.dir/pthread/pthread_solution.c.o.requires:

.PHONY : CMakeFiles/Project.dir/pthread/pthread_solution.c.o.requires

CMakeFiles/Project.dir/pthread/pthread_solution.c.o.provides: CMakeFiles/Project.dir/pthread/pthread_solution.c.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/pthread/pthread_solution.c.o.provides.build
.PHONY : CMakeFiles/Project.dir/pthread/pthread_solution.c.o.provides

CMakeFiles/Project.dir/pthread/pthread_solution.c.o.provides.build: CMakeFiles/Project.dir/pthread/pthread_solution.c.o


CMakeFiles/Project.dir/definitions/shared.c.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/definitions/shared.c.o: ../definitions/shared.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Project.dir/definitions/shared.c.o"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project.dir/definitions/shared.c.o   -c /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/definitions/shared.c

CMakeFiles/Project.dir/definitions/shared.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project.dir/definitions/shared.c.i"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/definitions/shared.c > CMakeFiles/Project.dir/definitions/shared.c.i

CMakeFiles/Project.dir/definitions/shared.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project.dir/definitions/shared.c.s"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/definitions/shared.c -o CMakeFiles/Project.dir/definitions/shared.c.s

CMakeFiles/Project.dir/definitions/shared.c.o.requires:

.PHONY : CMakeFiles/Project.dir/definitions/shared.c.o.requires

CMakeFiles/Project.dir/definitions/shared.c.o.provides: CMakeFiles/Project.dir/definitions/shared.c.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/definitions/shared.c.o.provides.build
.PHONY : CMakeFiles/Project.dir/definitions/shared.c.o.provides

CMakeFiles/Project.dir/definitions/shared.c.o.provides.build: CMakeFiles/Project.dir/definitions/shared.c.o


CMakeFiles/Project.dir/openmp/openmp_solution.c.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/openmp/openmp_solution.c.o: ../openmp/openmp_solution.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Project.dir/openmp/openmp_solution.c.o"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project.dir/openmp/openmp_solution.c.o   -c /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/openmp/openmp_solution.c

CMakeFiles/Project.dir/openmp/openmp_solution.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project.dir/openmp/openmp_solution.c.i"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/openmp/openmp_solution.c > CMakeFiles/Project.dir/openmp/openmp_solution.c.i

CMakeFiles/Project.dir/openmp/openmp_solution.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project.dir/openmp/openmp_solution.c.s"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/openmp/openmp_solution.c -o CMakeFiles/Project.dir/openmp/openmp_solution.c.s

CMakeFiles/Project.dir/openmp/openmp_solution.c.o.requires:

.PHONY : CMakeFiles/Project.dir/openmp/openmp_solution.c.o.requires

CMakeFiles/Project.dir/openmp/openmp_solution.c.o.provides: CMakeFiles/Project.dir/openmp/openmp_solution.c.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/openmp/openmp_solution.c.o.provides.build
.PHONY : CMakeFiles/Project.dir/openmp/openmp_solution.c.o.provides

CMakeFiles/Project.dir/openmp/openmp_solution.c.o.provides.build: CMakeFiles/Project.dir/openmp/openmp_solution.c.o


CMakeFiles/Project.dir/cilk/cilk_solution.c.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/cilk/cilk_solution.c.o: ../cilk/cilk_solution.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Project.dir/cilk/cilk_solution.c.o"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project.dir/cilk/cilk_solution.c.o   -c /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cilk/cilk_solution.c

CMakeFiles/Project.dir/cilk/cilk_solution.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project.dir/cilk/cilk_solution.c.i"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cilk/cilk_solution.c > CMakeFiles/Project.dir/cilk/cilk_solution.c.i

CMakeFiles/Project.dir/cilk/cilk_solution.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project.dir/cilk/cilk_solution.c.s"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cilk/cilk_solution.c -o CMakeFiles/Project.dir/cilk/cilk_solution.c.s

CMakeFiles/Project.dir/cilk/cilk_solution.c.o.requires:

.PHONY : CMakeFiles/Project.dir/cilk/cilk_solution.c.o.requires

CMakeFiles/Project.dir/cilk/cilk_solution.c.o.provides: CMakeFiles/Project.dir/cilk/cilk_solution.c.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/cilk/cilk_solution.c.o.provides.build
.PHONY : CMakeFiles/Project.dir/cilk/cilk_solution.c.o.provides

CMakeFiles/Project.dir/cilk/cilk_solution.c.o.provides.build: CMakeFiles/Project.dir/cilk/cilk_solution.c.o


CMakeFiles/Project.dir/tests/test_generator.c.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/tests/test_generator.c.o: ../tests/test_generator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Project.dir/tests/test_generator.c.o"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project.dir/tests/test_generator.c.o   -c /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/tests/test_generator.c

CMakeFiles/Project.dir/tests/test_generator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project.dir/tests/test_generator.c.i"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/tests/test_generator.c > CMakeFiles/Project.dir/tests/test_generator.c.i

CMakeFiles/Project.dir/tests/test_generator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project.dir/tests/test_generator.c.s"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/tests/test_generator.c -o CMakeFiles/Project.dir/tests/test_generator.c.s

CMakeFiles/Project.dir/tests/test_generator.c.o.requires:

.PHONY : CMakeFiles/Project.dir/tests/test_generator.c.o.requires

CMakeFiles/Project.dir/tests/test_generator.c.o.provides: CMakeFiles/Project.dir/tests/test_generator.c.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/tests/test_generator.c.o.provides.build
.PHONY : CMakeFiles/Project.dir/tests/test_generator.c.o.provides

CMakeFiles/Project.dir/tests/test_generator.c.o.provides.build: CMakeFiles/Project.dir/tests/test_generator.c.o


CMakeFiles/Project.dir/tests/test_stencil.c.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/tests/test_stencil.c.o: ../tests/test_stencil.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/Project.dir/tests/test_stencil.c.o"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project.dir/tests/test_stencil.c.o   -c /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/tests/test_stencil.c

CMakeFiles/Project.dir/tests/test_stencil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project.dir/tests/test_stencil.c.i"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/tests/test_stencil.c > CMakeFiles/Project.dir/tests/test_stencil.c.i

CMakeFiles/Project.dir/tests/test_stencil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project.dir/tests/test_stencil.c.s"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/tests/test_stencil.c -o CMakeFiles/Project.dir/tests/test_stencil.c.s

CMakeFiles/Project.dir/tests/test_stencil.c.o.requires:

.PHONY : CMakeFiles/Project.dir/tests/test_stencil.c.o.requires

CMakeFiles/Project.dir/tests/test_stencil.c.o.provides: CMakeFiles/Project.dir/tests/test_stencil.c.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/tests/test_stencil.c.o.provides.build
.PHONY : CMakeFiles/Project.dir/tests/test_stencil.c.o.provides

CMakeFiles/Project.dir/tests/test_stencil.c.o.provides.build: CMakeFiles/Project.dir/tests/test_stencil.c.o


CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o: ../pthread/pthread_barrier_osx.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o   -c /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/pthread/pthread_barrier_osx.c

CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.i"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/pthread/pthread_barrier_osx.c > CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.i

CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.s"
	/usr/local/bin/gcc-6  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/pthread/pthread_barrier_osx.c -o CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.s

CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o.requires:

.PHONY : CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o.requires

CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o.provides: CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o.requires
	$(MAKE) -f CMakeFiles/Project.dir/build.make CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o.provides.build
.PHONY : CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o.provides

CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o.provides.build: CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o


# Object files for target Project
Project_OBJECTS = \
"CMakeFiles/Project.dir/tests/benchmark_runner.c.o" \
"CMakeFiles/Project.dir/sequential/sequential_solution.c.o" \
"CMakeFiles/Project.dir/pthread/pthread_solution.c.o" \
"CMakeFiles/Project.dir/definitions/shared.c.o" \
"CMakeFiles/Project.dir/openmp/openmp_solution.c.o" \
"CMakeFiles/Project.dir/cilk/cilk_solution.c.o" \
"CMakeFiles/Project.dir/tests/test_generator.c.o" \
"CMakeFiles/Project.dir/tests/test_stencil.c.o" \
"CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o"

# External object files for target Project
Project_EXTERNAL_OBJECTS =

Project: CMakeFiles/Project.dir/tests/benchmark_runner.c.o
Project: CMakeFiles/Project.dir/sequential/sequential_solution.c.o
Project: CMakeFiles/Project.dir/pthread/pthread_solution.c.o
Project: CMakeFiles/Project.dir/definitions/shared.c.o
Project: CMakeFiles/Project.dir/openmp/openmp_solution.c.o
Project: CMakeFiles/Project.dir/cilk/cilk_solution.c.o
Project: CMakeFiles/Project.dir/tests/test_generator.c.o
Project: CMakeFiles/Project.dir/tests/test_stencil.c.o
Project: CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o
Project: CMakeFiles/Project.dir/build.make
Project: CMakeFiles/Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project.dir/build: Project

.PHONY : CMakeFiles/Project.dir/build

CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/tests/benchmark_runner.c.o.requires
CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/sequential/sequential_solution.c.o.requires
CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/pthread/pthread_solution.c.o.requires
CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/definitions/shared.c.o.requires
CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/openmp/openmp_solution.c.o.requires
CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/cilk/cilk_solution.c.o.requires
CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/tests/test_generator.c.o.requires
CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/tests/test_stencil.c.o.requires
CMakeFiles/Project.dir/requires: CMakeFiles/Project.dir/pthread/pthread_barrier_osx.c.o.requires

.PHONY : CMakeFiles/Project.dir/requires

CMakeFiles/Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project.dir/clean

CMakeFiles/Project.dir/depend:
	cd /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rfischer/Dropbox/Studium_Sem5/PC/Project /Users/rfischer/Dropbox/Studium_Sem5/PC/Project /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/cmake-build-debug/CMakeFiles/Project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project.dir/depend

