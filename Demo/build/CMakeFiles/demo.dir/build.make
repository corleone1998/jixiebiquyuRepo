# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\vscode\jixiebiquyu\Demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\vscode\jixiebiquyu\Demo\build

# Include any dependencies generated for this target.
include CMakeFiles/demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/demo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo.dir/flags.make

CMakeFiles/demo.dir/demo.cpp.obj: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/demo.cpp.obj: E:/vscode/jixiebiquyu/Demo/demo.cpp
CMakeFiles/demo.dir/demo.cpp.obj: CMakeFiles/demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\vscode\jixiebiquyu\Demo\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo.dir/demo.cpp.obj"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/demo.dir/demo.cpp.obj -MF CMakeFiles\demo.dir\demo.cpp.obj.d -o CMakeFiles\demo.dir\demo.cpp.obj -c E:\vscode\jixiebiquyu\Demo\demo.cpp

CMakeFiles/demo.dir/demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/demo.dir/demo.cpp.i"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\vscode\jixiebiquyu\Demo\demo.cpp > CMakeFiles\demo.dir\demo.cpp.i

CMakeFiles/demo.dir/demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/demo.dir/demo.cpp.s"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\vscode\jixiebiquyu\Demo\demo.cpp -o CMakeFiles\demo.dir\demo.cpp.s

# Object files for target demo
demo_OBJECTS = \
"CMakeFiles/demo.dir/demo.cpp.obj"

# External object files for target demo
demo_EXTERNAL_OBJECTS =

E:/vscode/jixiebiquyu/Demo/bin/demo.exe: CMakeFiles/demo.dir/demo.cpp.obj
E:/vscode/jixiebiquyu/Demo/bin/demo.exe: CMakeFiles/demo.dir/build.make
E:/vscode/jixiebiquyu/Demo/bin/demo.exe: E:/vscode/jixiebiquyu/Demo/ku/libCalcu.a
E:/vscode/jixiebiquyu/Demo/bin/demo.exe: CMakeFiles/demo.dir/linkLibs.rsp
E:/vscode/jixiebiquyu/Demo/bin/demo.exe: CMakeFiles/demo.dir/objects1.rsp
E:/vscode/jixiebiquyu/Demo/bin/demo.exe: CMakeFiles/demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=E:\vscode\jixiebiquyu\Demo\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable E:\vscode\jixiebiquyu\Demo\bin\demo.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\demo.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo.dir/build: E:/vscode/jixiebiquyu/Demo/bin/demo.exe
.PHONY : CMakeFiles/demo.dir/build

CMakeFiles/demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\demo.dir\cmake_clean.cmake
.PHONY : CMakeFiles/demo.dir/clean

CMakeFiles/demo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\vscode\jixiebiquyu\Demo E:\vscode\jixiebiquyu\Demo E:\vscode\jixiebiquyu\Demo\build E:\vscode\jixiebiquyu\Demo\build E:\vscode\jixiebiquyu\Demo\build\CMakeFiles\demo.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/demo.dir/depend

