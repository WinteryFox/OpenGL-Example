# This defines the minimum required CMake version to build this project.
cmake_minimum_required(VERSION 3.28)

# This is your project (or module, for modular projects) name.
project(OpenGL_Example)

# Instructs the compiler that we are using the C++ 23 standard.
set(CMAKE_CXX_STANDARD 23)

# This attempts to find the OpenGL library and include directories, so that you can link against and include them.
# https://cmake.org/cmake/help/latest/module/FindOpenGL.html
find_package(OpenGL REQUIRED)

# Same as above but for glew.
# https://cmake.org/cmake/help/latest/module/FindGLEW.html
find_package(GLEW REQUIRED)

# Same as above but for GLFW
find_package(GLFW3 3.3 REQUIRED)

# Same as above but for glm.
find_package(glm REQUIRED)

# This command adds a build target (executable or library, use add_library for libraries).
# The first word is the name of the executable and everything after that is the source files you want to include in
# this new target.
add_executable(OpenGL_Example main.cpp
        Util.h
        Debug.h)

# This links libraries against a target, the target being the executable we just added.
target_link_libraries(OpenGL_Example OpenGL::GL GLEW::glew glfw glm::glm)

