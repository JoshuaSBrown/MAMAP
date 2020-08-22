add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libmamap")
if(${ENABLE_UNIT_TESTING})
  message(STATUS "adding test directory")
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
endif()


