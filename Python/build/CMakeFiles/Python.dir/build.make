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
CMAKE_SOURCE_DIR = /home/frozen/Документы/Python/Python

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frozen/Документы/Python/Python/build

# Include any dependencies generated for this target.
include CMakeFiles/Python.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Python.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Python.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Python.dir/flags.make

CMakeFiles/Python.dir/src/Python.cpp.o: CMakeFiles/Python.dir/flags.make
CMakeFiles/Python.dir/src/Python.cpp.o: ../src/Python.cpp
CMakeFiles/Python.dir/src/Python.cpp.o: CMakeFiles/Python.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/frozen/Документы/Python/Python/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Python.dir/src/Python.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Python.dir/src/Python.cpp.o -MF CMakeFiles/Python.dir/src/Python.cpp.o.d -o CMakeFiles/Python.dir/src/Python.cpp.o -c /home/frozen/Документы/Python/Python/src/Python.cpp

CMakeFiles/Python.dir/src/Python.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Python.dir/src/Python.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frozen/Документы/Python/Python/src/Python.cpp > CMakeFiles/Python.dir/src/Python.cpp.i

CMakeFiles/Python.dir/src/Python.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Python.dir/src/Python.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frozen/Документы/Python/Python/src/Python.cpp -o CMakeFiles/Python.dir/src/Python.cpp.s

# Object files for target Python
Python_OBJECTS = \
"CMakeFiles/Python.dir/src/Python.cpp.o"

# External object files for target Python
Python_EXTERNAL_OBJECTS =

Python: CMakeFiles/Python.dir/src/Python.cpp.o
Python: CMakeFiles/Python.dir/build.make
Python: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
Python: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
Python: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
Python: CMakeFiles/Python.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/frozen/Документы/Python/Python/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Python"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Python.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Python.dir/build: Python
.PHONY : CMakeFiles/Python.dir/build

CMakeFiles/Python.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Python.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Python.dir/clean

CMakeFiles/Python.dir/depend:
	cd /home/frozen/Документы/Python/Python/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frozen/Документы/Python/Python /home/frozen/Документы/Python/Python /home/frozen/Документы/Python/Python/build /home/frozen/Документы/Python/Python/build /home/frozen/Документы/Python/Python/build/CMakeFiles/Python.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Python.dir/depend

