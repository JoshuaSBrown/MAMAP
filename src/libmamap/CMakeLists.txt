
file(GLOB MAP_SOURCE_FILES 
  arguments/properties/propertystringchoice.cpp
  string_support.cpp 
  )

add_library(libmap ${MAP_SOURCE_FILES})
set_property(TARGET libmap PROPERTY CXX_STANDARD 17)
target_include_directories(libmap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
