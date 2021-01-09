
set_target_properties(mamap PROPERTIES VERSION ${mamap_VERSION} SOVERSION ${SOVERSION})

target_include_directories(mamap PUBLIC
  $<BUILD_INTERFACE:${mamap_SOURCE_DIR}/include/mamap>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/mamap>
  )

install(TARGETS mamap EXPORT mamapTargets
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  )

# Install config files
install(FILES ${PROJECT_SOURCE_DIR}/cmake/mamapConfig.cmake DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/mamap")

install(EXPORT mamapTargets
  FILE mamapTargets.cmake
  NAMESPACE mamap::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/mamap"
  )
