# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /snap/cmake/1210/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1210/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/max/Documents/GitHub/Texture/TP_texture

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/max/Documents/GitHub/Texture/TP_texture/build

# Include any dependencies generated for this target.
include external/glfw-3.1.2/tests/CMakeFiles/title.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/glfw-3.1.2/tests/CMakeFiles/title.dir/compiler_depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/tests/CMakeFiles/title.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/tests/CMakeFiles/title.dir/flags.make

external/glfw-3.1.2/tests/CMakeFiles/title.dir/title.c.o: external/glfw-3.1.2/tests/CMakeFiles/title.dir/flags.make
external/glfw-3.1.2/tests/CMakeFiles/title.dir/title.c.o: /home/max/Documents/GitHub/Texture/TP_texture/external/glfw-3.1.2/tests/title.c
external/glfw-3.1.2/tests/CMakeFiles/title.dir/title.c.o: external/glfw-3.1.2/tests/CMakeFiles/title.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/max/Documents/GitHub/Texture/TP_texture/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/tests/CMakeFiles/title.dir/title.c.o"
	cd /home/max/Documents/GitHub/Texture/TP_texture/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/tests/CMakeFiles/title.dir/title.c.o -MF CMakeFiles/title.dir/title.c.o.d -o CMakeFiles/title.dir/title.c.o -c /home/max/Documents/GitHub/Texture/TP_texture/external/glfw-3.1.2/tests/title.c

external/glfw-3.1.2/tests/CMakeFiles/title.dir/title.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/title.dir/title.c.i"
	cd /home/max/Documents/GitHub/Texture/TP_texture/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/max/Documents/GitHub/Texture/TP_texture/external/glfw-3.1.2/tests/title.c > CMakeFiles/title.dir/title.c.i

external/glfw-3.1.2/tests/CMakeFiles/title.dir/title.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/title.dir/title.c.s"
	cd /home/max/Documents/GitHub/Texture/TP_texture/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/max/Documents/GitHub/Texture/TP_texture/external/glfw-3.1.2/tests/title.c -o CMakeFiles/title.dir/title.c.s

# Object files for target title
title_OBJECTS = \
"CMakeFiles/title.dir/title.c.o"

# External object files for target title
title_EXTERNAL_OBJECTS =

external/glfw-3.1.2/tests/title: external/glfw-3.1.2/tests/CMakeFiles/title.dir/title.c.o
external/glfw-3.1.2/tests/title: external/glfw-3.1.2/tests/CMakeFiles/title.dir/build.make
external/glfw-3.1.2/tests/title: external/glfw-3.1.2/src/libglfw3.a
external/glfw-3.1.2/tests/title: /usr/lib/x86_64-linux-gnu/librt.a
external/glfw-3.1.2/tests/title: /usr/lib/x86_64-linux-gnu/libm.so
external/glfw-3.1.2/tests/title: /usr/lib/x86_64-linux-gnu/libX11.so
external/glfw-3.1.2/tests/title: /usr/lib/x86_64-linux-gnu/libXrandr.so
external/glfw-3.1.2/tests/title: /usr/lib/x86_64-linux-gnu/libXinerama.so
external/glfw-3.1.2/tests/title: /usr/lib/x86_64-linux-gnu/libXi.so
external/glfw-3.1.2/tests/title: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
external/glfw-3.1.2/tests/title: /usr/lib/x86_64-linux-gnu/libXcursor.so
external/glfw-3.1.2/tests/title: /usr/lib/x86_64-linux-gnu/libGL.so
external/glfw-3.1.2/tests/title: external/glfw-3.1.2/tests/CMakeFiles/title.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/max/Documents/GitHub/Texture/TP_texture/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable title"
	cd /home/max/Documents/GitHub/Texture/TP_texture/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/title.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/tests/CMakeFiles/title.dir/build: external/glfw-3.1.2/tests/title
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/title.dir/build

external/glfw-3.1.2/tests/CMakeFiles/title.dir/clean:
	cd /home/max/Documents/GitHub/Texture/TP_texture/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -P CMakeFiles/title.dir/cmake_clean.cmake
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/title.dir/clean

external/glfw-3.1.2/tests/CMakeFiles/title.dir/depend:
	cd /home/max/Documents/GitHub/Texture/TP_texture/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/max/Documents/GitHub/Texture/TP_texture /home/max/Documents/GitHub/Texture/TP_texture/external/glfw-3.1.2/tests /home/max/Documents/GitHub/Texture/TP_texture/build /home/max/Documents/GitHub/Texture/TP_texture/build/external/glfw-3.1.2/tests /home/max/Documents/GitHub/Texture/TP_texture/build/external/glfw-3.1.2/tests/CMakeFiles/title.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/title.dir/depend

