# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = /home/morgan/Programmation/Projects/qt-pong

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/morgan/Programmation/Projects/qt-pong

# Include any dependencies generated for this target.
include CMakeFiles/qt-pong.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/qt-pong.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qt-pong.dir/flags.make

CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.o: CMakeFiles/qt-pong.dir/flags.make
CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.o: qt-pong_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.o -c /home/morgan/Programmation/Projects/qt-pong/qt-pong_autogen/mocs_compilation.cpp

CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/morgan/Programmation/Projects/qt-pong/qt-pong_autogen/mocs_compilation.cpp > CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.i

CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/morgan/Programmation/Projects/qt-pong/qt-pong_autogen/mocs_compilation.cpp -o CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.s

CMakeFiles/qt-pong.dir/src/main.cpp.o: CMakeFiles/qt-pong.dir/flags.make
CMakeFiles/qt-pong.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/qt-pong.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt-pong.dir/src/main.cpp.o -c /home/morgan/Programmation/Projects/qt-pong/src/main.cpp

CMakeFiles/qt-pong.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-pong.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/morgan/Programmation/Projects/qt-pong/src/main.cpp > CMakeFiles/qt-pong.dir/src/main.cpp.i

CMakeFiles/qt-pong.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-pong.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/morgan/Programmation/Projects/qt-pong/src/main.cpp -o CMakeFiles/qt-pong.dir/src/main.cpp.s

CMakeFiles/qt-pong.dir/src/main_window.cpp.o: CMakeFiles/qt-pong.dir/flags.make
CMakeFiles/qt-pong.dir/src/main_window.cpp.o: src/main_window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/qt-pong.dir/src/main_window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt-pong.dir/src/main_window.cpp.o -c /home/morgan/Programmation/Projects/qt-pong/src/main_window.cpp

CMakeFiles/qt-pong.dir/src/main_window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-pong.dir/src/main_window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/morgan/Programmation/Projects/qt-pong/src/main_window.cpp > CMakeFiles/qt-pong.dir/src/main_window.cpp.i

CMakeFiles/qt-pong.dir/src/main_window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-pong.dir/src/main_window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/morgan/Programmation/Projects/qt-pong/src/main_window.cpp -o CMakeFiles/qt-pong.dir/src/main_window.cpp.s

CMakeFiles/qt-pong.dir/src/scene.cpp.o: CMakeFiles/qt-pong.dir/flags.make
CMakeFiles/qt-pong.dir/src/scene.cpp.o: src/scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/qt-pong.dir/src/scene.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt-pong.dir/src/scene.cpp.o -c /home/morgan/Programmation/Projects/qt-pong/src/scene.cpp

CMakeFiles/qt-pong.dir/src/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-pong.dir/src/scene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/morgan/Programmation/Projects/qt-pong/src/scene.cpp > CMakeFiles/qt-pong.dir/src/scene.cpp.i

CMakeFiles/qt-pong.dir/src/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-pong.dir/src/scene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/morgan/Programmation/Projects/qt-pong/src/scene.cpp -o CMakeFiles/qt-pong.dir/src/scene.cpp.s

CMakeFiles/qt-pong.dir/src/ball.cpp.o: CMakeFiles/qt-pong.dir/flags.make
CMakeFiles/qt-pong.dir/src/ball.cpp.o: src/ball.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/qt-pong.dir/src/ball.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt-pong.dir/src/ball.cpp.o -c /home/morgan/Programmation/Projects/qt-pong/src/ball.cpp

CMakeFiles/qt-pong.dir/src/ball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-pong.dir/src/ball.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/morgan/Programmation/Projects/qt-pong/src/ball.cpp > CMakeFiles/qt-pong.dir/src/ball.cpp.i

CMakeFiles/qt-pong.dir/src/ball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-pong.dir/src/ball.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/morgan/Programmation/Projects/qt-pong/src/ball.cpp -o CMakeFiles/qt-pong.dir/src/ball.cpp.s

CMakeFiles/qt-pong.dir/src/config.cpp.o: CMakeFiles/qt-pong.dir/flags.make
CMakeFiles/qt-pong.dir/src/config.cpp.o: src/config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/qt-pong.dir/src/config.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt-pong.dir/src/config.cpp.o -c /home/morgan/Programmation/Projects/qt-pong/src/config.cpp

CMakeFiles/qt-pong.dir/src/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-pong.dir/src/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/morgan/Programmation/Projects/qt-pong/src/config.cpp > CMakeFiles/qt-pong.dir/src/config.cpp.i

CMakeFiles/qt-pong.dir/src/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-pong.dir/src/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/morgan/Programmation/Projects/qt-pong/src/config.cpp -o CMakeFiles/qt-pong.dir/src/config.cpp.s

CMakeFiles/qt-pong.dir/src/paddle.cpp.o: CMakeFiles/qt-pong.dir/flags.make
CMakeFiles/qt-pong.dir/src/paddle.cpp.o: src/paddle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/qt-pong.dir/src/paddle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt-pong.dir/src/paddle.cpp.o -c /home/morgan/Programmation/Projects/qt-pong/src/paddle.cpp

CMakeFiles/qt-pong.dir/src/paddle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-pong.dir/src/paddle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/morgan/Programmation/Projects/qt-pong/src/paddle.cpp > CMakeFiles/qt-pong.dir/src/paddle.cpp.i

CMakeFiles/qt-pong.dir/src/paddle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-pong.dir/src/paddle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/morgan/Programmation/Projects/qt-pong/src/paddle.cpp -o CMakeFiles/qt-pong.dir/src/paddle.cpp.s

CMakeFiles/qt-pong.dir/src/view.cpp.o: CMakeFiles/qt-pong.dir/flags.make
CMakeFiles/qt-pong.dir/src/view.cpp.o: src/view.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/qt-pong.dir/src/view.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt-pong.dir/src/view.cpp.o -c /home/morgan/Programmation/Projects/qt-pong/src/view.cpp

CMakeFiles/qt-pong.dir/src/view.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-pong.dir/src/view.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/morgan/Programmation/Projects/qt-pong/src/view.cpp > CMakeFiles/qt-pong.dir/src/view.cpp.i

CMakeFiles/qt-pong.dir/src/view.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-pong.dir/src/view.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/morgan/Programmation/Projects/qt-pong/src/view.cpp -o CMakeFiles/qt-pong.dir/src/view.cpp.s

CMakeFiles/qt-pong.dir/src/player.cpp.o: CMakeFiles/qt-pong.dir/flags.make
CMakeFiles/qt-pong.dir/src/player.cpp.o: src/player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/qt-pong.dir/src/player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt-pong.dir/src/player.cpp.o -c /home/morgan/Programmation/Projects/qt-pong/src/player.cpp

CMakeFiles/qt-pong.dir/src/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-pong.dir/src/player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/morgan/Programmation/Projects/qt-pong/src/player.cpp > CMakeFiles/qt-pong.dir/src/player.cpp.i

CMakeFiles/qt-pong.dir/src/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-pong.dir/src/player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/morgan/Programmation/Projects/qt-pong/src/player.cpp -o CMakeFiles/qt-pong.dir/src/player.cpp.s

# Object files for target qt-pong
qt__pong_OBJECTS = \
"CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/qt-pong.dir/src/main.cpp.o" \
"CMakeFiles/qt-pong.dir/src/main_window.cpp.o" \
"CMakeFiles/qt-pong.dir/src/scene.cpp.o" \
"CMakeFiles/qt-pong.dir/src/ball.cpp.o" \
"CMakeFiles/qt-pong.dir/src/config.cpp.o" \
"CMakeFiles/qt-pong.dir/src/paddle.cpp.o" \
"CMakeFiles/qt-pong.dir/src/view.cpp.o" \
"CMakeFiles/qt-pong.dir/src/player.cpp.o"

# External object files for target qt-pong
qt__pong_EXTERNAL_OBJECTS =

qt-pong: CMakeFiles/qt-pong.dir/qt-pong_autogen/mocs_compilation.cpp.o
qt-pong: CMakeFiles/qt-pong.dir/src/main.cpp.o
qt-pong: CMakeFiles/qt-pong.dir/src/main_window.cpp.o
qt-pong: CMakeFiles/qt-pong.dir/src/scene.cpp.o
qt-pong: CMakeFiles/qt-pong.dir/src/ball.cpp.o
qt-pong: CMakeFiles/qt-pong.dir/src/config.cpp.o
qt-pong: CMakeFiles/qt-pong.dir/src/paddle.cpp.o
qt-pong: CMakeFiles/qt-pong.dir/src/view.cpp.o
qt-pong: CMakeFiles/qt-pong.dir/src/player.cpp.o
qt-pong: CMakeFiles/qt-pong.dir/build.make
qt-pong: /usr/lib/libQt5Widgets.so.5.15.2
qt-pong: /usr/lib/libQt5Gui.so.5.15.2
qt-pong: /usr/lib/libQt5Core.so.5.15.2
qt-pong: CMakeFiles/qt-pong.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/morgan/Programmation/Projects/qt-pong/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable qt-pong"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qt-pong.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qt-pong.dir/build: qt-pong

.PHONY : CMakeFiles/qt-pong.dir/build

CMakeFiles/qt-pong.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qt-pong.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qt-pong.dir/clean

CMakeFiles/qt-pong.dir/depend:
	cd /home/morgan/Programmation/Projects/qt-pong && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/morgan/Programmation/Projects/qt-pong /home/morgan/Programmation/Projects/qt-pong /home/morgan/Programmation/Projects/qt-pong /home/morgan/Programmation/Projects/qt-pong /home/morgan/Programmation/Projects/qt-pong/CMakeFiles/qt-pong.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qt-pong.dir/depend

