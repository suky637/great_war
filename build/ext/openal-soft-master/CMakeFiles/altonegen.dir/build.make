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
CMAKE_SOURCE_DIR = /home/suky/dev/ww1_game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/suky/dev/ww1_game/build

# Include any dependencies generated for this target.
include ext/openal-soft-master/CMakeFiles/altonegen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ext/openal-soft-master/CMakeFiles/altonegen.dir/compiler_depend.make

# Include the progress variables for this target.
include ext/openal-soft-master/CMakeFiles/altonegen.dir/progress.make

# Include the compile flags for this target's objects.
include ext/openal-soft-master/CMakeFiles/altonegen.dir/flags.make

ext/openal-soft-master/CMakeFiles/altonegen.dir/examples/altonegen.c.o: ext/openal-soft-master/CMakeFiles/altonegen.dir/flags.make
ext/openal-soft-master/CMakeFiles/altonegen.dir/examples/altonegen.c.o: ../ext/openal-soft-master/examples/altonegen.c
ext/openal-soft-master/CMakeFiles/altonegen.dir/examples/altonegen.c.o: ext/openal-soft-master/CMakeFiles/altonegen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suky/dev/ww1_game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object ext/openal-soft-master/CMakeFiles/altonegen.dir/examples/altonegen.c.o"
	cd /home/suky/dev/ww1_game/build/ext/openal-soft-master && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT ext/openal-soft-master/CMakeFiles/altonegen.dir/examples/altonegen.c.o -MF CMakeFiles/altonegen.dir/examples/altonegen.c.o.d -o CMakeFiles/altonegen.dir/examples/altonegen.c.o -c /home/suky/dev/ww1_game/ext/openal-soft-master/examples/altonegen.c

ext/openal-soft-master/CMakeFiles/altonegen.dir/examples/altonegen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/altonegen.dir/examples/altonegen.c.i"
	cd /home/suky/dev/ww1_game/build/ext/openal-soft-master && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/suky/dev/ww1_game/ext/openal-soft-master/examples/altonegen.c > CMakeFiles/altonegen.dir/examples/altonegen.c.i

ext/openal-soft-master/CMakeFiles/altonegen.dir/examples/altonegen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/altonegen.dir/examples/altonegen.c.s"
	cd /home/suky/dev/ww1_game/build/ext/openal-soft-master && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/suky/dev/ww1_game/ext/openal-soft-master/examples/altonegen.c -o CMakeFiles/altonegen.dir/examples/altonegen.c.s

# Object files for target altonegen
altonegen_OBJECTS = \
"CMakeFiles/altonegen.dir/examples/altonegen.c.o"

# External object files for target altonegen
altonegen_EXTERNAL_OBJECTS =

ext/openal-soft-master/altonegen: ext/openal-soft-master/CMakeFiles/altonegen.dir/examples/altonegen.c.o
ext/openal-soft-master/altonegen: ext/openal-soft-master/CMakeFiles/altonegen.dir/build.make
ext/openal-soft-master/altonegen: ext/openal-soft-master/libalsoft.excommon.a
ext/openal-soft-master/altonegen: ext/openal-soft-master/libopenal.so.1.24.1
ext/openal-soft-master/altonegen: ext/openal-soft-master/CMakeFiles/altonegen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/suky/dev/ww1_game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable altonegen"
	cd /home/suky/dev/ww1_game/build/ext/openal-soft-master && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/altonegen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ext/openal-soft-master/CMakeFiles/altonegen.dir/build: ext/openal-soft-master/altonegen
.PHONY : ext/openal-soft-master/CMakeFiles/altonegen.dir/build

ext/openal-soft-master/CMakeFiles/altonegen.dir/clean:
	cd /home/suky/dev/ww1_game/build/ext/openal-soft-master && $(CMAKE_COMMAND) -P CMakeFiles/altonegen.dir/cmake_clean.cmake
.PHONY : ext/openal-soft-master/CMakeFiles/altonegen.dir/clean

ext/openal-soft-master/CMakeFiles/altonegen.dir/depend:
	cd /home/suky/dev/ww1_game/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/suky/dev/ww1_game /home/suky/dev/ww1_game/ext/openal-soft-master /home/suky/dev/ww1_game/build /home/suky/dev/ww1_game/build/ext/openal-soft-master /home/suky/dev/ww1_game/build/ext/openal-soft-master/CMakeFiles/altonegen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ext/openal-soft-master/CMakeFiles/altonegen.dir/depend
