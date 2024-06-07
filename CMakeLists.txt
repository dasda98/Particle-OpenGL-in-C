cmake_minimum_required(VERSION 3.28)
project(YoutubeOpenGL C)

set(CMAKE_C_STANDARD 17)

set(INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include)

set(SOURCES
        ${PROJECT_SOURCE_DIR}/main.c
        ${PROJECT_SOURCE_DIR}/src/glad.c
        ${PROJECT_SOURCE_DIR}/src/shader.c)

add_executable(YoutubeOpenGL ${SOURCES})

target_include_directories(YoutubeOpenGL PRIVATE ${INCLUDE_DIRS})

# GLFW
find_package(glfw3 3.4 REQUIRED)
if (glfw3_FOUND)
    message("Linking GLFW...")
    target_link_libraries(YoutubeOpenGL glfw)
else ()
    message("GLFW not found!")
endif ()

# OpenGL
find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    message("Linking OpenGL...")
    target_link_libraries(YoutubeOpenGL OpenGL::GL)
else ()
    message("OpenGL not found!")
endif ()


# C_GLM
find_package(cglm REQUIRED)
if (cglm_FOUND)
    message("Linking cGLM...")
    target_link_libraries(YoutubeOpenGL cglm::cglm -lm)
else ()
    message("GLFW not found!")
endif ()

