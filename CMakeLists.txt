cmake_minimum_required(VERSION 4.0)
project(Outside)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(libs)

set(FILES_CORE
        src/core/Windows.cpp
        include/core/Windows.h
)

set(FILES_EDITOR
        src/editor/ImguiRender.cpp
        include/editor/ImguiRender.h
        include/editor/PerformanceMonitor.h
        src/editor/PerformanceMonitor.cpp
)

add_executable(Outside
        src/Outside.cpp
        include/Outside.h
        ${FILES_CORE}
        ${FILES_EDITOR}
)

find_package(OpenGL REQUIRED)

if(MSVC) # MSVC (Visual Studio)
    target_compile_options(Outside PRIVATE /W0 /O2 /std:c++23 /RTC1) # /W0 .. /W4 - Info by error and warning
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Outside PRIVATE -w -O2 -Wall -Wextra -std=c++23 -march=native -fcolor-diagnostics)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Outside PRIVATE -w -O2 -Wall -Wextra -std=c++23 -march=native -fdiagnostics-color=always)
endif()

target_include_directories(Outside PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Outside PRIVATE OpenGL::GL glfw glad imgui)