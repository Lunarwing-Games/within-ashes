cmake_minimum_required(VERSION 3.20)
project(within_ashes LANGUAGES C CXX)

file(GLOB_RECURSE WA_SRC CONFIGURE_DEPENDS "src/*.cpp")

add_executable(within_ashes ${WA_SRC})

target_include_directories(within_ashes
    PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    "C:/raylib55/include"
    "C:/steamworks/sdk/public"
)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

if(MSVC)
    add_compile_options(/MP /utf-8 /permissive-)
    add_compile_options(/W3)
else()
    # Okay this looks like a lot but it's still easier than ISO C++!
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

if(WIN32)
    set(RAYLIB_LIB_DIR "C:/raylib55")
    set(STEAMWORKS_LIB_DIR "C:/steamworks/sdk/redistributable_bin/win64")
    set(RAYLIB_LIB raylib.lib)
    set(STEAMWORKS_LIB steam_api64.lib)

    target_link_directories(within_ashes PRIVATE ${RAYLIB_LIB_DIR})
    target_link_directories(within_ashes PRIVATE ${STEAMWORKS_LIB_DIR})
    target_link_libraries(within_ashes PRIVATE ${RAYLIB_LIB})
    target_link_libraries(within_ashes PRIVATE ${STEAMWORKS_LIB})

    target_link_libraries(within_ashes PRIVATE
        winmm.lib
        kernel32.lib
        user32.lib
        gdi32.lib
        shell32.lib
    )
elseif(UNIX)
    # Unix linkage...
endif()

message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")