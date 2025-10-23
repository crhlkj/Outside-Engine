# ===== GLFW =====
include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
)

FetchContent_MakeAvailable(glfw)
message(STATUS "Fetched GLFW from repository")

# ===== GLAD =====
add_library(glad STATIC ${PROJECT_SOURCE_DIR}/libs/glad/src/glad.c)
target_include_directories(glad PUBLIC "${PROJECT_SOURCE_DIR}/libs/glad/include")
message(STATUS "Using local GLAD source")

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG master
)

# ===== IMGUI =====
file(GLOB IMGUI_FILES
        ${PROJECT_SOURCE_DIR}/libs/imgui/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/imgui/backends/*.cpp
)

add_library(imgui STATIC ${IMGUI_FILES})
target_include_directories(imgui PUBLIC
        ${PROJECT_SOURCE_DIR}/libs/imgui
        ${PROJECT_SOURCE_DIR}/libs/imgui/backends
        ${GLFW_SOURCE_DIR}/include
)