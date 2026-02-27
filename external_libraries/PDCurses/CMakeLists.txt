# Minimum CMake verion.
cmake_minimum_required(VERSION 3.20)

# Starting Project.
project(pdcurses VERSION 3.9)

set(CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

target_link_libraries(pdcurses PRIVATE "${PROJECT_SOURCE_DIR}/wincon/pdcurses.lib")

# add directories to compiler include path.  ####################################################
target_include_directories(pdcurses PUBLIC "${PROJECT_SOURCE_DIR}")
# add directories to compiler include path.  ####################################################


