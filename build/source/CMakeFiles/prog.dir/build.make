# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build

# Include any dependencies generated for this target.
include source/CMakeFiles/prog.dir/depend.make

# Include the progress variables for this target.
include source/CMakeFiles/prog.dir/progress.make

# Include the compile flags for this target's objects.
include source/CMakeFiles/prog.dir/flags.make

source/CMakeFiles/prog.dir/prog.cpp.o: source/CMakeFiles/prog.dir/flags.make
source/CMakeFiles/prog.dir/prog.cpp.o: ../source/prog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/CMakeFiles/prog.dir/prog.cpp.o"
	cd /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prog.dir/prog.cpp.o -c /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/source/prog.cpp

source/CMakeFiles/prog.dir/prog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prog.dir/prog.cpp.i"
	cd /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/source/prog.cpp > CMakeFiles/prog.dir/prog.cpp.i

source/CMakeFiles/prog.dir/prog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prog.dir/prog.cpp.s"
	cd /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/source/prog.cpp -o CMakeFiles/prog.dir/prog.cpp.s

source/CMakeFiles/prog.dir/prog.cpp.o.requires:

.PHONY : source/CMakeFiles/prog.dir/prog.cpp.o.requires

source/CMakeFiles/prog.dir/prog.cpp.o.provides: source/CMakeFiles/prog.dir/prog.cpp.o.requires
	$(MAKE) -f source/CMakeFiles/prog.dir/build.make source/CMakeFiles/prog.dir/prog.cpp.o.provides.build
.PHONY : source/CMakeFiles/prog.dir/prog.cpp.o.provides

source/CMakeFiles/prog.dir/prog.cpp.o.provides.build: source/CMakeFiles/prog.dir/prog.cpp.o


# Object files for target prog
prog_OBJECTS = \
"CMakeFiles/prog.dir/prog.cpp.o"

# External object files for target prog
prog_EXTERNAL_OBJECTS =

source/prog: source/CMakeFiles/prog.dir/prog.cpp.o
source/prog: source/CMakeFiles/prog.dir/build.make
source/prog: framework/libframework.a
source/prog: external/glfw-3.2.1/src/libglfw3.a
source/prog: external/glfw-3.2.1/src/libglfw3.a
source/prog: /usr/lib/x86_64-linux-gnu/libGLU.so
source/prog: /usr/lib/x86_64-linux-gnu/libGL.so
source/prog: /usr/lib/x86_64-linux-gnu/librt.so
source/prog: /usr/lib/x86_64-linux-gnu/libm.so
source/prog: /usr/lib/x86_64-linux-gnu/libX11.so
source/prog: /usr/lib/x86_64-linux-gnu/libXrandr.so
source/prog: /usr/lib/x86_64-linux-gnu/libXinerama.so
source/prog: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
source/prog: /usr/lib/x86_64-linux-gnu/libXcursor.so
source/prog: source/CMakeFiles/prog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable prog"
	cd /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build/source && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/CMakeFiles/prog.dir/build: source/prog

.PHONY : source/CMakeFiles/prog.dir/build

source/CMakeFiles/prog.dir/requires: source/CMakeFiles/prog.dir/prog.cpp.o.requires

.PHONY : source/CMakeFiles/prog.dir/requires

source/CMakeFiles/prog.dir/clean:
	cd /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build/source && $(CMAKE_COMMAND) -P CMakeFiles/prog.dir/cmake_clean.cmake
.PHONY : source/CMakeFiles/prog.dir/clean

source/CMakeFiles/prog.dir/depend:
	cd /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/source /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build/source /media/mapotoufu/DATA/Documents/00lesson/Universitaet/MI/Programiersprachen/Coorp/build/source/CMakeFiles/prog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/CMakeFiles/prog.dir/depend

