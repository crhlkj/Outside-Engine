cmake_minimum_required(VERSION 4.0)
project(Outside)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(libs)

file(GLOB FILES_OUTSIDE
    ${PROJECT_SOURCE_DIR}/src/core/*.cpp
    ${PROJECT_SOURCE_DIR}/src/editor/*.cpp
)

add_executable(Outside
        src/Outside.cpp
        include/Outside.h
        ${FILES_OUTSIDE}
)

find_package(OpenGL REQUIRED)

if(MSVC) # MSVC (Visual Studio)
    target_compile_options(Outside PRIVATE /W4 /O2 /std:c++23 /RTC1) # /W0 .. /W4 - Info by error and warning
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Outside PRIVATE
            -w -Wall -Wextra
            -O2 -std=c++23
            -march=native -fcolor-diagnostics
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Outside PRIVATE
            -w -Wall -Wextra
            -O2 -std=c++23
            -march=native -fdiagnostics-color=always
    )
endif()

target_include_directories(Outside PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Outside PRIVATE OpenGL::GL glfw glad imgui)