# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thomas/Documents/arcade_2048/2048

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/Documents/arcade_2048/2048/build

# Include any dependencies generated for this target.
include CMakeFiles/2048.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/2048.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/2048.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2048.dir/flags.make

CMakeFiles/2048.dir/src/main.cpp.o: CMakeFiles/2048.dir/flags.make
CMakeFiles/2048.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/2048.dir/src/main.cpp.o: CMakeFiles/2048.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thomas/Documents/arcade_2048/2048/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2048.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2048.dir/src/main.cpp.o -MF CMakeFiles/2048.dir/src/main.cpp.o.d -o CMakeFiles/2048.dir/src/main.cpp.o -c /home/thomas/Documents/arcade_2048/2048/src/main.cpp

CMakeFiles/2048.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2048.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas/Documents/arcade_2048/2048/src/main.cpp > CMakeFiles/2048.dir/src/main.cpp.i

CMakeFiles/2048.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2048.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas/Documents/arcade_2048/2048/src/main.cpp -o CMakeFiles/2048.dir/src/main.cpp.s

# Object files for target 2048
2048_OBJECTS = \
"CMakeFiles/2048.dir/src/main.cpp.o"

# External object files for target 2048
2048_EXTERNAL_OBJECTS =

2048: CMakeFiles/2048.dir/src/main.cpp.o
2048: CMakeFiles/2048.dir/build.make
2048: _deps/raylib-build/raylib/libraylib.a
2048: /usr/lib64/libGL.so
2048: _deps/raylib-build/raylib/external/glfw/src/libglfw3.a
2048: /usr/lib64/librt.a
2048: /usr/lib64/libm.so
2048: CMakeFiles/2048.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thomas/Documents/arcade_2048/2048/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 2048"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2048.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2048.dir/build: 2048
.PHONY : CMakeFiles/2048.dir/build

CMakeFiles/2048.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2048.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2048.dir/clean

CMakeFiles/2048.dir/depend:
	cd /home/thomas/Documents/arcade_2048/2048/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas/Documents/arcade_2048/2048 /home/thomas/Documents/arcade_2048/2048 /home/thomas/Documents/arcade_2048/2048/build /home/thomas/Documents/arcade_2048/2048/build /home/thomas/Documents/arcade_2048/2048/build/CMakeFiles/2048.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2048.dir/depend

