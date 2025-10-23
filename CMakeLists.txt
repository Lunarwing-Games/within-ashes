# Within Ashes CMake
# Streamlined build configuration for a compact project.
# (c) 2025 Lunarwing Games

cmake_minimum_required(VERSION 3.20)
project(within_ashes LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE WA_SRC CONFIGURE_DEPENDS "src/*.cpp")
add_executable(within_ashes ${WA_SRC})

if(WIN32)
    set(TARGET_PLATFORM "Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(TARGET_PLATFORM "macOS")
elseif(UNIX)
    set(TARGET_PLATFORM "Linux")
else()
    message(FATAL_ERROR "Unknown OS: ${CMAKE_SYSTEM_NAME}")
endif()

message(STATUS "Detected platform: ${TARGET_PLATFORM}")

if(TARGET_PLATFORM STREQUAL "Windows")
    target_include_directories(within_ashes
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "C:/raylib55/include"
        "C:/steamworks/sdk/public"
    )

elseif(TARGET_PLATFORM STREQUAL "macOS")
    # Detect Raylib via Homebrew
    execute_process(
        COMMAND brew --prefix raylib
        OUTPUT_VARIABLE RAYLIB_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    message(STATUS "Raylib located at: ${RAYLIB_PREFIX}")

    # Include directories
    target_include_directories(within_ashes
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "${RAYLIB_PREFIX}/include"
        "$ENV{HOME}/sdk/public"
    )

elseif(TARGET_PLATFORM STREQUAL "Linux")
    # Linux includes (adjust as needed)
    target_include_directories(within_ashes
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "/usr/include"
        "$ENV{HOME}/sdk/public"
    )
endif()

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(/O2 /SUBSYSTEM:WINDOWS)
    endif()

    add_compile_options(/MP /utf-8 /permissive- /W3)

else()
    # Common Clang/GCC warnings
    add_compile_options(
        -Wall -Wextra -Wconversion -Wshadow -Wformat=2 
        -Wno-unused-parameter -Wundef -Wpointer-arith
        -Wswitch-enum -Wcast-align -Wmissing-declarations
        -Wlogical-op -Wredundant-decls -Wformat-strings
        -Wnull-dereference
    )

    target_compile_options(within_ashes PRIVATE -fno-rtti -fno-exceptions)
    add_compile_options(-fdiagnostics-color=always)
endif()

if(TARGET_PLATFORM STREQUAL "Windows")

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(within_ashes PROPERTIES WIN32_EXECUTABLE TRUE)
    endif()

    set(RAYLIB_LIB_DIR "C:/raylib55")
    set(STEAMWORKS_LIB_DIR "C:/steamworks/sdk/redistributable_bin/win64")
    set(RAYLIB_LIB raylib.lib)
    set(STEAMWORKS_LIB steam_api64.lib)

    target_link_directories(within_ashes PRIVATE
        ${RAYLIB_LIB_DIR}
        ${STEAMWORKS_LIB_DIR}
    )

    target_link_libraries(within_ashes PRIVATE
        ${RAYLIB_LIB}
        ${STEAMWORKS_LIB}
        winmm.lib
        kernel32.lib
        user32.lib
        gdi32.lib
        shell32.lib
    )
elseif(TARGET_PLATFORM STREQUAL "macOS")

    set(RAYLIB_LIB_DIR "${RAYLIB_PREFIX}/lib")
    set(STEAMWORKS_LIB_DIR "$ENV{HOME}/sdk/redistributable_bin/osx")
    set(RAYLIB_LIB raylib)
    set(STEAMWORKS_LIB steam_api)

    target_link_directories(within_ashes PRIVATE
        ${RAYLIB_LIB_DIR}
        ${STEAMWORKS_LIB_DIR}
    )

    target_link_libraries(within_ashes PRIVATE
        ${RAYLIB_LIB}
        ${STEAMWORKS_LIB}
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework CoreVideo"
        "-framework CoreAudio"
        "-framework AudioToolbox"
    )

    add_custom_command(TARGET within_ashes POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${STEAMWORKS_LIB_DIR}/libsteam_api.dylib"
            $<TARGET_FILE_DIR:within_ashes>
        COMMENT "Copying libsteam_api.dylib to output directory"
    )
elseif(TARGET_PLATFORM STREQUAL "Linux")

    set(RAYLIB_LIB_DIR "/usr/lib")
    set(STEAMWORKS_LIB_DIR "$ENV{HOME}/sdk/redistributable_bin/linux64")
    set(RAYLIB_LIB raylib)
    set(STEAMWORKS_LIB steam_api)

    target_link_directories(within_ashes PRIVATE
        ${RAYLIB_LIB_DIR}
        ${STEAMWORKS_LIB_DIR}
    )

    target_link_libraries(within_ashes PRIVATE
        ${RAYLIB_LIB}
        ${STEAMWORKS_LIB}
        pthread
        dl
        m
    )
endif()

message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

if(TARGET_PLATFORM STREQUAL "Windows")
    add_custom_command(TARGET within_ashes POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${RAYLIB_LIB_DIR}/raylib.dll"
            $<TARGET_FILE_DIR:within_ashes>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${STEAMWORKS_LIB_DIR}/steam_api64.dll"
            $<TARGET_FILE_DIR:within_ashes>
        COMMENT "Copying raylib.dll and steam_api64.dll to output directory"
    )
endif()
