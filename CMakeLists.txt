cmake_minimum_required(VERSION 3.5)
project(mmath VERSION 1.0.0 LANGUAGES C)

##############################################
# Create target and set properties

add_library(mmath
  src/mmath/common.c
  src/mmath/mat2.c
  src/mmath/mat2d.c
  src/mmath/mat3.c
  src/mmath/mat4.c
  src/mmath/quat.c
  src/mmath/quat2.c
  src/mmath/vec2.c
  src/mmath/vec3.c
  src/mmath/vec4.c
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(MMath::mmath ALIAS mmath)

#Set target properties
target_include_directories(mmath
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(mmath PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/MMath)

install(TARGETS mmath
  EXPORT mmath-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name MMath and not mmath
set_target_properties(mmath PROPERTIES EXPORT_NAME MMath)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT mmath-targets
  FILE
    MMathTargets.cmake
  NAMESPACE
    MMath::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/MMathConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/MMathConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/MMathConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/MMathConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/MMathConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
export(EXPORT mmath-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/MMathTargets.cmake NAMESPACE MMath::)

#Register package in user's package registry
export(PACKAGE MMath)
