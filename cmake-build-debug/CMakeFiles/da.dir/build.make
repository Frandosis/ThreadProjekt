# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/da.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/da.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/da.dir/flags.make

CMakeFiles/da.dir/dynamicarray.c.o: CMakeFiles/da.dir/flags.make
CMakeFiles/da.dir/dynamicarray.c.o: ../dynamicarray.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/da.dir/dynamicarray.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/da.dir/dynamicarray.c.o   -c /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/dynamicarray.c

CMakeFiles/da.dir/dynamicarray.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/da.dir/dynamicarray.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/dynamicarray.c > CMakeFiles/da.dir/dynamicarray.c.i

CMakeFiles/da.dir/dynamicarray.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/da.dir/dynamicarray.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/dynamicarray.c -o CMakeFiles/da.dir/dynamicarray.c.s

# Object files for target da
da_OBJECTS = \
"CMakeFiles/da.dir/dynamicarray.c.o"

# External object files for target da
da_EXTERNAL_OBJECTS =

libda.a: CMakeFiles/da.dir/dynamicarray.c.o
libda.a: CMakeFiles/da.dir/build.make
libda.a: CMakeFiles/da.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libda.a"
	$(CMAKE_COMMAND) -P CMakeFiles/da.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/da.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/da.dir/build: libda.a

.PHONY : CMakeFiles/da.dir/build

CMakeFiles/da.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/da.dir/cmake_clean.cmake
.PHONY : CMakeFiles/da.dir/clean

CMakeFiles/da.dir/depend:
	cd /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/cmake-build-debug /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/cmake-build-debug /mnt/c/Users/s184805/CLionProjects/OperativSystemer/ThreadProjekt/cmake-build-debug/CMakeFiles/da.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/da.dir/depend
