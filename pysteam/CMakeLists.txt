# PySteam library CMake file
# (c) 2025 Lunarwing Games
#
cmake_minimum_required(VERSION 3.20)

project(pysteam VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
    set(STEAMWORKS_SDK "C:/steamworks/sdk")
elseif(APPLE OR LINUX)
    set(STEAMWORKS_SDK "~/steamworks/sdk")
else()
    message(FATAL_ERROR "Unknown OS!")
endif()

add_library(pysteam SHARED pysteam.cpp)

target_include_directories(pysteam
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        ${STEAMWORKS_SDK}/public
)

# versioning and public header
set_target_properties(pysteam PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "pysteam.h"
)

if(WIN32)
    target_link_directories(pysteam PRIVATE
        ${STEAMWORKS_SDK}/redistributable_bin
    )
    target_link_libraries(pysteam PRIVATE steam_api.lib)
elseif(APPLE)
    target_link_directories(pysteam PRIVATE
        ${STEAMWORKS_SDK}/redistributable_bin/osx
    )
    target_link_libraries(pysteam PRIVATE steam_api)
else() # Linux
    target_link_directories(pysteam PRIVATE
        ${STEAMWORKS_SDK}/redistributable_bin/linux64
    )
    target_link_libraries(pysteam PRIVATE steam_api64)
endif()

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
