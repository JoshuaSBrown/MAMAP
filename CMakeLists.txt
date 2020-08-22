cmake_minimum_required (VERSION 3.14)
project (mamap)

##############################################################################
# Defining options 
##############################################################################
option(ENABLE_TESTS "Enable testing" OFF)
option(ENABLE_UNIT_TESTING "Enable tests" ${ENABLE_TESTS})
option(ENABLE_PROFILING "Enable profiling" OFF)
option(CODE_COVERAGE "Enable coverage reporting" OFF)

##############################################################################
# Defining settings 
##############################################################################
set(mamap_VERSION_MAJOR 1 )
set(mamap_VERSION_MINOR 0 )
set(mamap_YEAR_PUBLISHED 2020 )
set(mamap_AUTHOR_SURNAME "\"Brown\"" )
set(mamap_AUTHOR_INITIALS "\"J. S.\"" )
set(mamap_TITLE "\"MAMAP\"")
set(mamap_URL "\"https://github.com/JoshuaSBrown/MAMAP\"" )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COVERAGE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
set(COMMON_LIBRARIES stdc++ m)
set(LOG_LEVEL 0 CACHE STRING "Choose the log level" )
# Prevents multiple file extensions from being appended one after the other
# important for using gcov .o.gcno or .cpp.gcno now will be .gcno
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -Werror")
##############################################################################
# Configuring header file with cmake variables 
##############################################################################
# Configure header file to pass some of the CMake settings to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/src/libmamap/mamap_config.hpp.in"
  "${PROJECT_SOURCE_DIR}/src/libmamap/mamap_config.hpp"
  )

##############################################################################
# Finding dependencies 
##############################################################################
# Find bash it is important for testing using scripts
find_library (GCOV gcov)

##############################################################################
# Setting up profiling 
##############################################################################
if(ENABLE_PROFILING)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()
##############################################################################
# Setting up testing 
##############################################################################
if(ENABLE_UNIT_TESTING )
  find_package(Catch2 2.11.1)
  if( NOT Catch2 )
    include(${PROJECT_SOURCE_DIR}/cmake/InstallCatch2.cmake)
  else()
    message(STATUS "found system installed Catch2 will not download")
  endif()
  enable_testing()
  include(ParseAndAddCatchTests)
endif()
##############################################################################
# Compiling build tree/paths 
##############################################################################
add_subdirectory("${PROJECT_SOURCE_DIR}/src")

