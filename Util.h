#pragma once

#include <stdexcept>
#include <glfw/glfw3.h>

#include "Debug.h"

/**
* \brief Initializes GLEW, without this your program would segfault and crash when you try to call OpenGL functions.
 */
inline void initGlew() {
    // Remember to first initialize GLEW. You must always set glewExperimental to true for usage with modern OpenGL.
    glewExperimental = GL_TRUE;
    if (const auto& result = glewInit(); GLEW_OK != result)
        throw std::runtime_error("Failed to initialize GLEW");

    // Setup debug messages for OpenGL, this will tell you whenever you fucked up.
    if (GLEW_ARB_debug_output) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}

/**
 * \brief Creates a new window using GLFW3. This should be put into a class with a destructor for actual projects.
 * \param width The window's width
 * \param height The window's height
 * \return Returns a new GLFWwindow* instance
 */
inline GLFWwindow* createWindow(const uint32_t width, const uint32_t height) {
    // Remember to first initialize GLFW.
    if (GLFW_TRUE != glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    // Standard set of window hints, I recommend you use at least OpenGL 4.0+ core.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    // For modern OpenGL, you always want to use a core profile.
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Technically only needed for Apple.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    // Highly recommend you use this.
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // Creates the window and checks if it succeeded by checking if window is not a nullptr.
    GLFWwindow* window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), "OpenGL Example", nullptr,
                                          nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // This is needed for OpenGL, this will make the current OpenGL context (which contains the state) the target for
    // any operations we perform using OpenGL.
    glfwMakeContextCurrent(window);

    return window;
}

/**
 * \brief Destroys the window and terminates GLFW3.
 * \param window The window to destroy
 */
inline void destroyWindow(GLFWwindow* window) {
    glfwDestroyWindow(window);
    // Don't forget to call this, it destroys any resources GLFW made.
    glfwTerminate();
}

/**
 * \brief Creates a new shader program and links a vertex and fragment shader to it.
 * \param vertexModule The vertex shader to link to.
 * \param fragmentModule The fragment shader to link to.
 * \return Returns a shader program with vertex and fragment shader modules linked. The modules may now be destroyed.
 */
inline GLuint linkModules(const GLuint vertexModule, const GLuint fragmentModule) {
    // Creates a new shader program.
    const GLuint program = glCreateProgram();

    // These calls attach shader modules to a shader program which will be used when linking.
    glAttachShader(program, vertexModule);
    glAttachShader(program, fragmentModule);

    // Links the shader modules together to create a shader program.
    glLinkProgram(program);

    // Same as the code in createShaderModule but checks for linking errors this time.
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint size;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
        char log[size];
        glGetProgramInfoLog(program, size, nullptr, log);
        throw std::runtime_error("Failed to link GL shader program.\n" + std::string(log));
    }

    return program;
}

/**
 * \brief Creates and compiles a shader module.
 * \param type The type of shader to create, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
 * \param source The source code for the shader.
 * \return Returns a newly created shader module which can be used to link a program.
 */
inline GLuint createShaderModule(const GLenum type, const std::string& source) {
    // Creates a new shader module.
    const GLuint module = glCreateShader(type);

    const auto& src = source.c_str();
    // This call sets the source code for a shader module.
    glShaderSource(module, 1, &src, nullptr);
    // This call actually compiles the shader module.
    glCompileShader(module);

    // This code checks for compilation errors. If there were errors, runtime error is thrown with the error message.
    GLint status;
    glGetShaderiv(module, GL_COMPILE_STATUS, &status);
    if (!status) {
        GLint size;
        glGetShaderiv(module, GL_INFO_LOG_LENGTH, &size);
        char log[size];
        glGetShaderInfoLog(module, size, nullptr, log);
        throw std::runtime_error("Failed to compile GL shader module.\n" + std::string(log));
    }

    return module;
}
