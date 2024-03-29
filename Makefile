# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/danmunro/projects/csaw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/danmunro/projects/csaw

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.15.4/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/usr/local/Cellar/cmake/3.15.4/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.15.4/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/danmunro/projects/csaw/CMakeFiles /Users/danmunro/projects/csaw/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/danmunro/projects/csaw/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named test_main

# Build rule for target.
test_main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_main
.PHONY : test_main

# fast build rule for target.
test_main/fast:
	$(MAKE) -f CMakeFiles/test_main.dir/build.make CMakeFiles/test_main.dir/build
.PHONY : test_main/fast

#=============================================================================
# Target rules for targets named show-coverage

# Build rule for target.
show-coverage: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 show-coverage
.PHONY : show-coverage

# fast build rule for target.
show-coverage/fast:
	$(MAKE) -f CMakeFiles/show-coverage.dir/build.make CMakeFiles/show-coverage.dir/build
.PHONY : show-coverage/fast

#=============================================================================
# Target rules for targets named create-coverage

# Build rule for target.
create-coverage: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 create-coverage
.PHONY : create-coverage

# fast build rule for target.
create-coverage/fast:
	$(MAKE) -f CMakeFiles/create-coverage.dir/build.make CMakeFiles/create-coverage.dir/build
.PHONY : create-coverage/fast

#=============================================================================
# Target rules for targets named csaw

# Build rule for target.
csaw: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 csaw
.PHONY : csaw

# fast build rule for target.
csaw/fast:
	$(MAKE) -f CMakeFiles/csaw.dir/build.make CMakeFiles/csaw.dir/build
.PHONY : csaw/fast

src/main.o: src/main.c.o

.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) -f CMakeFiles/csaw.dir/build.make CMakeFiles/csaw.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) -f CMakeFiles/csaw.dir/build.make CMakeFiles/csaw.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) -f CMakeFiles/csaw.dir/build.make CMakeFiles/csaw.dir/src/main.c.s
.PHONY : src/main.c.s

tests/test_main.o: tests/test_main.c.o

.PHONY : tests/test_main.o

# target to build an object file
tests/test_main.c.o:
	$(MAKE) -f CMakeFiles/test_main.dir/build.make CMakeFiles/test_main.dir/tests/test_main.c.o
.PHONY : tests/test_main.c.o

tests/test_main.i: tests/test_main.c.i

.PHONY : tests/test_main.i

# target to preprocess a source file
tests/test_main.c.i:
	$(MAKE) -f CMakeFiles/test_main.dir/build.make CMakeFiles/test_main.dir/tests/test_main.c.i
.PHONY : tests/test_main.c.i

tests/test_main.s: tests/test_main.c.s

.PHONY : tests/test_main.s

# target to generate assembly for a file
tests/test_main.c.s:
	$(MAKE) -f CMakeFiles/test_main.dir/build.make CMakeFiles/test_main.dir/tests/test_main.c.s
.PHONY : tests/test_main.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... test"
	@echo "... test_main"
	@echo "... edit_cache"
	@echo "... show-coverage"
	@echo "... create-coverage"
	@echo "... csaw"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... tests/test_main.o"
	@echo "... tests/test_main.i"
	@echo "... tests/test_main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

