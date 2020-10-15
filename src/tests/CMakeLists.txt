list( APPEND UNIT_TEST_SOURCE_FILES
  test_propertystringchoice
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


