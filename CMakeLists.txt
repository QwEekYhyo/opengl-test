cmake_minimum_required(VERSION 3.10)

project(epic-game LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
    set_source_files_properties(
        src/glad.c
        PROPERTIES
        COMPILE_OPTIONS "-Wno-pedantic"
    )
endif()

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(epic-game ${SOURCES})
target_include_directories(epic-game PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_custom_command(TARGET epic-game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:epic-game>/assets
)

target_link_libraries(epic-game PRIVATE
    OpenGL::GL
    glfw
)

install(TARGETS epic-game)
