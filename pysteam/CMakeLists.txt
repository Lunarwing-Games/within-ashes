# PySteam library CMake file
# (c) 2025 Lunarwing Games
#

project(pysteam)
cmake_minimum_required(VERSION 3.20)

# C99 because it just works everywhere
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(pysteam SHARED pysteam.c)

target_include_directories(pysteam
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# versioning and public header
set_target_properties(pysteam PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER "pysteam.h"
)

# install rules (library + public header + export)
install(TARGETS pysteam
  EXPORT PySteamTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION include
)

install(EXPORT PySteamTargets
  FILE PySteamTargets.cmake
  NAMESPACE PySteam::
  DESTINATION lib/cmake/PySteam
)
