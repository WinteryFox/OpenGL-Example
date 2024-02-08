#pragma once
#include <iostream>

static void debugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
) {
    std::string src;
    switch (source) {
    case GL_DEBUG_SOURCE_API:
        src = "API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        src = "Window";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        src = "Shader";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        src = "Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        src = "Application";
        break;
    default:
        src = "Unknown";
        break;
    }

    std::string typ;
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        typ = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        typ = "DEPRECATED BEHAVIOUR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        typ = "UNDEFINED BEHAVIOUR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        typ = "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        typ = "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_MARKER:
        typ = "MARKER";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        typ = "PUSH GROUP";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        typ = "POP GROUP";
        break;
    case GL_DEBUG_TYPE_OTHER:
        typ = "OTHER";
        break;
    default:
        typ = "UNKNOWN";
        break;
    }

    std::string level;
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        level = "HIGH";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        level = "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        level = "LOW";
        break;
    default:
        level = "UNKNOWN";
        break;
    }

    std::cout << "[" << level << "] " << "(" << typ << ") " << "<" << src << "> " << message << std::endl;
}
