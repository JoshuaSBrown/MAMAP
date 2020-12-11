cmake_minimum_required (VERSION 3.14)
project (mamap VERSION 1.0.0)

##############################################################################
# Defining options 
##############################################################################
option(ENABLE_TESTING "Enable tests" ON)
option(ENABLE_UNIT_TESTING "Enable tests" ${ENABLE_TESTING})
option(ENABLE_PROFILING "Enable profiling" OFF)
option(CODE_COVERAGE "Enable coverage reporting" OFF)

##############################################################################
# Defining settings 
##############################################################################
set(SOVERSION 1)
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

###########################
# Setup relative includes #
###########################
include_directories(${mamap_SOURCE_DIR}/include)
include_directories(${mamap_BINARY_DIR}/include)

############################
# Add source files
############################

file(GLOB MAP_SOURCE_FILES 
  ${mamap_SOURCE_DIR}/src/libmamap/argumentparser.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/argumentfile.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/argumentnumerical.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/argumentstring.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/argumentswitch.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/argumenttypes.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertystringchoice.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertyfileexist.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertyfileext.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertynumeric.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertysisterfile.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertystring.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertyswitch.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertyobject.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertyoptions.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/arguments/properties/propertytypes.cpp
  ${mamap_SOURCE_DIR}/src/libmamap/string_support.cpp 
  )

add_library(mamap ${MAP_SOURCE_FILES})
set_property(TARGET mamap PROPERTY CXX_STANDARD 17)

##############################################################################
# Compiling build tree/paths 
##############################################################################
add_subdirectory("${mamap_SOURCE_DIR}/include/mamap")

include(${mamap_SOURCE_DIR}/cmake/MAMAPInstall.cmake)
