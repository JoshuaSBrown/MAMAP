file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testfile.pun
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/testfile.pun)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dir/file.jpg
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/dir/file.jpg)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dir/file.jp
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/dir/file.jp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Dir2/file.png
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Dir2/file.png)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Dir2/file.gjf
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Dir2/file.gjf)

list( APPEND UNIT_TEST_SOURCE_FILES
  test_propertyfileexist
  test_propertyfileext
  test_propertynumerical
  test_propertystringchoice
  test_propertystring
  test_propertyswitch
)

if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")    
  find_library (GCOV gcov)
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")    

if(${ENABLE_UNIT_TESTING})
  foreach(PROG IN LISTS UNIT_TEST_SOURCE_FILES)
    message(STATUS "Generating test for ${PROG}")
    add_executable(unit_${PROG} ${PROG}.cpp)
    if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")    
      set_source_files_properties( ${PROG}.cpp PROPERTIES COMPILE_FLAGS ${COVERAGE_FLAGS} )
    endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")    
    target_link_libraries(unit_${PROG} libmap Catch2::Catch2)
    ParseAndAddCatchTests(unit_${PROG})
  endforeach(PROG)
endif()


