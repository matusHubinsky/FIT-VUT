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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build"

# Include any dependencies generated for this target.
include SDL/CMakeFiles/SDL2main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include SDL/CMakeFiles/SDL2main.dir/compiler_depend.make

# Include the progress variables for this target.
include SDL/CMakeFiles/SDL2main.dir/progress.make

# Include the compile flags for this target's objects.
include SDL/CMakeFiles/SDL2main.dir/flags.make

SDL/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o: SDL/CMakeFiles/SDL2main.dir/flags.make
SDL/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o: /home/leviathan/Documents/VUT/1BIT/2.\ semester/IZG/ex/izg_lab_01/SDL/src/main/dummy/SDL_dummy_main.c
SDL/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o: SDL/CMakeFiles/SDL2main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object SDL/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o"
	cd "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/SDL" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT SDL/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o -MF CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o.d -o CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o -c "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/SDL/src/main/dummy/SDL_dummy_main.c"

SDL/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.i"
	cd "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/SDL" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/SDL/src/main/dummy/SDL_dummy_main.c" > CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.i

SDL/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.s"
	cd "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/SDL" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/SDL/src/main/dummy/SDL_dummy_main.c" -o CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.s

# Object files for target SDL2main
SDL2main_OBJECTS = \
"CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o"

# External object files for target SDL2main
SDL2main_EXTERNAL_OBJECTS =

SDL/libSDL2main.a: SDL/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o
SDL/libSDL2main.a: SDL/CMakeFiles/SDL2main.dir/build.make
SDL/libSDL2main.a: SDL/CMakeFiles/SDL2main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libSDL2main.a"
	cd "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/SDL" && $(CMAKE_COMMAND) -P CMakeFiles/SDL2main.dir/cmake_clean_target.cmake
	cd "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/SDL" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SDL2main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SDL/CMakeFiles/SDL2main.dir/build: SDL/libSDL2main.a
.PHONY : SDL/CMakeFiles/SDL2main.dir/build

SDL/CMakeFiles/SDL2main.dir/clean:
	cd "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/SDL" && $(CMAKE_COMMAND) -P CMakeFiles/SDL2main.dir/cmake_clean.cmake
.PHONY : SDL/CMakeFiles/SDL2main.dir/clean

SDL/CMakeFiles/SDL2main.dir/depend:
	cd "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01" "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/SDL" "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build" "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/SDL" "/home/leviathan/Documents/VUT/1BIT/2. semester/IZG/ex/izg_lab_01/build/SDL/CMakeFiles/SDL2main.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : SDL/CMakeFiles/SDL2main.dir/depend

