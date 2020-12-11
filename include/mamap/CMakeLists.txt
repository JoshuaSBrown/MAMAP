configure_file(mamap_config.hpp.in mamap_config.hpp @ONLY)
# Maintain directory structure in installed include files
install(DIRECTORY . DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/mamap" FILES_MATCHING PATTERN "*.hpp")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mamap_config.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/mamap")
