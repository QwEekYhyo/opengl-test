cmake_minimum_required(VERSION 3.10)

project(epic-game LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(epic-game ${SOURCES})
target_include_directories(epic-game PRIVATE ${PROJECT_SOURCE_DIR}/include)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(epic-game PRIVATE
    OpenGL::GL
    glfw
)

install(TARGETS epic-game)
