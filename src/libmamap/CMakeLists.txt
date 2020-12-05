
file(GLOB MAP_SOURCE_FILES 
  arguments/argumentfile.cpp
  arguments/argumentobject.cpp
  arguments/argumentnumerical.cpp
  arguments/argumentstring.cpp
  arguments/argumentswitch.cpp
  arguments/properties/propertystringchoice.cpp
  arguments/properties/propertyfileexist.cpp
  arguments/properties/propertyfileext.cpp
  arguments/properties/propertynumeric.cpp
  arguments/properties/propertysisterfile.cpp
  arguments/properties/propertystring.cpp
  arguments/properties/propertyswitch.cpp
  arguments/properties/propertyobject.cpp
  string_support.cpp 
  )

add_library(libmap ${MAP_SOURCE_FILES})
set_property(TARGET libmap PROPERTY CXX_STANDARD 17)
target_include_directories(libmap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
