# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /usr/local/igl/libigl/external/embree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/local/igl/libigl/external/embree/bin

# Include any dependencies generated for this target.
include common/image/CMakeFiles/image.dir/depend.make

# Include the progress variables for this target.
include common/image/CMakeFiles/image.dir/progress.make

# Include the compile flags for this target's objects.
include common/image/CMakeFiles/image.dir/flags.make

common/image/CMakeFiles/image.dir/image.o: common/image/CMakeFiles/image.dir/flags.make
common/image/CMakeFiles/image.dir/image.o: ../common/image/image.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/igl/libigl/external/embree/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/image/CMakeFiles/image.dir/image.o"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/image.dir/image.o -c /usr/local/igl/libigl/external/embree/common/image/image.cpp

common/image/CMakeFiles/image.dir/image.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/image.i"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/igl/libigl/external/embree/common/image/image.cpp > CMakeFiles/image.dir/image.i

common/image/CMakeFiles/image.dir/image.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/image.s"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/igl/libigl/external/embree/common/image/image.cpp -o CMakeFiles/image.dir/image.s

common/image/CMakeFiles/image.dir/image.o.requires:
.PHONY : common/image/CMakeFiles/image.dir/image.o.requires

common/image/CMakeFiles/image.dir/image.o.provides: common/image/CMakeFiles/image.dir/image.o.requires
	$(MAKE) -f common/image/CMakeFiles/image.dir/build.make common/image/CMakeFiles/image.dir/image.o.provides.build
.PHONY : common/image/CMakeFiles/image.dir/image.o.provides

common/image/CMakeFiles/image.dir/image.o.provides.build: common/image/CMakeFiles/image.dir/image.o

common/image/CMakeFiles/image.dir/ppm.o: common/image/CMakeFiles/image.dir/flags.make
common/image/CMakeFiles/image.dir/ppm.o: ../common/image/ppm.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/igl/libigl/external/embree/bin/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/image/CMakeFiles/image.dir/ppm.o"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/image.dir/ppm.o -c /usr/local/igl/libigl/external/embree/common/image/ppm.cpp

common/image/CMakeFiles/image.dir/ppm.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/ppm.i"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/igl/libigl/external/embree/common/image/ppm.cpp > CMakeFiles/image.dir/ppm.i

common/image/CMakeFiles/image.dir/ppm.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/ppm.s"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/igl/libigl/external/embree/common/image/ppm.cpp -o CMakeFiles/image.dir/ppm.s

common/image/CMakeFiles/image.dir/ppm.o.requires:
.PHONY : common/image/CMakeFiles/image.dir/ppm.o.requires

common/image/CMakeFiles/image.dir/ppm.o.provides: common/image/CMakeFiles/image.dir/ppm.o.requires
	$(MAKE) -f common/image/CMakeFiles/image.dir/build.make common/image/CMakeFiles/image.dir/ppm.o.provides.build
.PHONY : common/image/CMakeFiles/image.dir/ppm.o.provides

common/image/CMakeFiles/image.dir/ppm.o.provides.build: common/image/CMakeFiles/image.dir/ppm.o

common/image/CMakeFiles/image.dir/pfm.o: common/image/CMakeFiles/image.dir/flags.make
common/image/CMakeFiles/image.dir/pfm.o: ../common/image/pfm.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/igl/libigl/external/embree/bin/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/image/CMakeFiles/image.dir/pfm.o"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/image.dir/pfm.o -c /usr/local/igl/libigl/external/embree/common/image/pfm.cpp

common/image/CMakeFiles/image.dir/pfm.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/pfm.i"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/igl/libigl/external/embree/common/image/pfm.cpp > CMakeFiles/image.dir/pfm.i

common/image/CMakeFiles/image.dir/pfm.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/pfm.s"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/igl/libigl/external/embree/common/image/pfm.cpp -o CMakeFiles/image.dir/pfm.s

common/image/CMakeFiles/image.dir/pfm.o.requires:
.PHONY : common/image/CMakeFiles/image.dir/pfm.o.requires

common/image/CMakeFiles/image.dir/pfm.o.provides: common/image/CMakeFiles/image.dir/pfm.o.requires
	$(MAKE) -f common/image/CMakeFiles/image.dir/build.make common/image/CMakeFiles/image.dir/pfm.o.provides.build
.PHONY : common/image/CMakeFiles/image.dir/pfm.o.provides

common/image/CMakeFiles/image.dir/pfm.o.provides.build: common/image/CMakeFiles/image.dir/pfm.o

common/image/CMakeFiles/image.dir/tga.o: common/image/CMakeFiles/image.dir/flags.make
common/image/CMakeFiles/image.dir/tga.o: ../common/image/tga.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/igl/libigl/external/embree/bin/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/image/CMakeFiles/image.dir/tga.o"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/image.dir/tga.o -c /usr/local/igl/libigl/external/embree/common/image/tga.cpp

common/image/CMakeFiles/image.dir/tga.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/tga.i"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/igl/libigl/external/embree/common/image/tga.cpp > CMakeFiles/image.dir/tga.i

common/image/CMakeFiles/image.dir/tga.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/tga.s"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/igl/libigl/external/embree/common/image/tga.cpp -o CMakeFiles/image.dir/tga.s

common/image/CMakeFiles/image.dir/tga.o.requires:
.PHONY : common/image/CMakeFiles/image.dir/tga.o.requires

common/image/CMakeFiles/image.dir/tga.o.provides: common/image/CMakeFiles/image.dir/tga.o.requires
	$(MAKE) -f common/image/CMakeFiles/image.dir/build.make common/image/CMakeFiles/image.dir/tga.o.provides.build
.PHONY : common/image/CMakeFiles/image.dir/tga.o.provides

common/image/CMakeFiles/image.dir/tga.o.provides.build: common/image/CMakeFiles/image.dir/tga.o

common/image/CMakeFiles/image.dir/exr.o: common/image/CMakeFiles/image.dir/flags.make
common/image/CMakeFiles/image.dir/exr.o: ../common/image/exr.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/igl/libigl/external/embree/bin/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/image/CMakeFiles/image.dir/exr.o"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/image.dir/exr.o -c /usr/local/igl/libigl/external/embree/common/image/exr.cpp

common/image/CMakeFiles/image.dir/exr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/exr.i"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/igl/libigl/external/embree/common/image/exr.cpp > CMakeFiles/image.dir/exr.i

common/image/CMakeFiles/image.dir/exr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/exr.s"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/igl/libigl/external/embree/common/image/exr.cpp -o CMakeFiles/image.dir/exr.s

common/image/CMakeFiles/image.dir/exr.o.requires:
.PHONY : common/image/CMakeFiles/image.dir/exr.o.requires

common/image/CMakeFiles/image.dir/exr.o.provides: common/image/CMakeFiles/image.dir/exr.o.requires
	$(MAKE) -f common/image/CMakeFiles/image.dir/build.make common/image/CMakeFiles/image.dir/exr.o.provides.build
.PHONY : common/image/CMakeFiles/image.dir/exr.o.provides

common/image/CMakeFiles/image.dir/exr.o.provides.build: common/image/CMakeFiles/image.dir/exr.o

common/image/CMakeFiles/image.dir/magick.o: common/image/CMakeFiles/image.dir/flags.make
common/image/CMakeFiles/image.dir/magick.o: ../common/image/magick.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/igl/libigl/external/embree/bin/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object common/image/CMakeFiles/image.dir/magick.o"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/image.dir/magick.o -c /usr/local/igl/libigl/external/embree/common/image/magick.cpp

common/image/CMakeFiles/image.dir/magick.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/magick.i"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/igl/libigl/external/embree/common/image/magick.cpp > CMakeFiles/image.dir/magick.i

common/image/CMakeFiles/image.dir/magick.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/magick.s"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/igl/libigl/external/embree/common/image/magick.cpp -o CMakeFiles/image.dir/magick.s

common/image/CMakeFiles/image.dir/magick.o.requires:
.PHONY : common/image/CMakeFiles/image.dir/magick.o.requires

common/image/CMakeFiles/image.dir/magick.o.provides: common/image/CMakeFiles/image.dir/magick.o.requires
	$(MAKE) -f common/image/CMakeFiles/image.dir/build.make common/image/CMakeFiles/image.dir/magick.o.provides.build
.PHONY : common/image/CMakeFiles/image.dir/magick.o.provides

common/image/CMakeFiles/image.dir/magick.o.provides.build: common/image/CMakeFiles/image.dir/magick.o

# Object files for target image
image_OBJECTS = \
"CMakeFiles/image.dir/image.o" \
"CMakeFiles/image.dir/ppm.o" \
"CMakeFiles/image.dir/pfm.o" \
"CMakeFiles/image.dir/tga.o" \
"CMakeFiles/image.dir/exr.o" \
"CMakeFiles/image.dir/magick.o"

# External object files for target image
image_EXTERNAL_OBJECTS =

libimage.a: common/image/CMakeFiles/image.dir/image.o
libimage.a: common/image/CMakeFiles/image.dir/ppm.o
libimage.a: common/image/CMakeFiles/image.dir/pfm.o
libimage.a: common/image/CMakeFiles/image.dir/tga.o
libimage.a: common/image/CMakeFiles/image.dir/exr.o
libimage.a: common/image/CMakeFiles/image.dir/magick.o
libimage.a: common/image/CMakeFiles/image.dir/build.make
libimage.a: common/image/CMakeFiles/image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../libimage.a"
	cd /usr/local/igl/libigl/external/embree/bin/common/image && $(CMAKE_COMMAND) -P CMakeFiles/image.dir/cmake_clean_target.cmake
	cd /usr/local/igl/libigl/external/embree/bin/common/image && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
common/image/CMakeFiles/image.dir/build: libimage.a
.PHONY : common/image/CMakeFiles/image.dir/build

common/image/CMakeFiles/image.dir/requires: common/image/CMakeFiles/image.dir/image.o.requires
common/image/CMakeFiles/image.dir/requires: common/image/CMakeFiles/image.dir/ppm.o.requires
common/image/CMakeFiles/image.dir/requires: common/image/CMakeFiles/image.dir/pfm.o.requires
common/image/CMakeFiles/image.dir/requires: common/image/CMakeFiles/image.dir/tga.o.requires
common/image/CMakeFiles/image.dir/requires: common/image/CMakeFiles/image.dir/exr.o.requires
common/image/CMakeFiles/image.dir/requires: common/image/CMakeFiles/image.dir/magick.o.requires
.PHONY : common/image/CMakeFiles/image.dir/requires

common/image/CMakeFiles/image.dir/clean:
	cd /usr/local/igl/libigl/external/embree/bin/common/image && $(CMAKE_COMMAND) -P CMakeFiles/image.dir/cmake_clean.cmake
.PHONY : common/image/CMakeFiles/image.dir/clean

common/image/CMakeFiles/image.dir/depend:
	cd /usr/local/igl/libigl/external/embree/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/local/igl/libigl/external/embree /usr/local/igl/libigl/external/embree/common/image /usr/local/igl/libigl/external/embree/bin /usr/local/igl/libigl/external/embree/bin/common/image /usr/local/igl/libigl/external/embree/bin/common/image/CMakeFiles/image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : common/image/CMakeFiles/image.dir/depend

