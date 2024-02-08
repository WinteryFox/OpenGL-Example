/**
 * Going into this, I expect you to have basic knowledge of computer graphics. You should already know what vertices and
 * indices are, as these are the absolute fundamentals for computer graphics. Since these are common concepts talked
 * about in Unity and among game developers in general, this is something you should already be familiar with.
 * If you are not sure what these are, please Google them first!
 */

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Util.h"

constexpr uint32_t width = 720;

constexpr uint32_t height = 480;

int main() {
    GLFWwindow* window = createWindow(width, height);

    initGlew();

    // Highly recommend you use sRGB, it has been the standard color format
    // for at least a decade.
    glEnable(GL_FRAMEBUFFER_SRGB);

    // These two calls should be fairly obvious ;^)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // The viewport is the area we are rendering to within the image/window.
    glViewport(0, 0, width, height);

    // I don't know how familiar you are with shaders, but we can just gloss over this part for now.
    const GLuint vertexShader = createShaderModule(GL_VERTEX_SHADER, R"(
#version 450 core

layout(location = 0) in vec3 position;

void main() {
    gl_Position = vec4(position, 1.0);
}
)");
    const GLuint fragmentShader = createShaderModule(GL_FRAGMENT_SHADER, R"(
#version 450 core

layout(location = 0) out vec4 color;

void main() {
    color = vec4(1.0, 0.0, 0.0, 1.0);
}
)");

    // This creates a shader program and links the modules we just created to it.
    const GLuint shaderProgram = linkModules(vertexShader, fragmentShader);

    // You can destroy the shader modules after linking a shader program, they are no longer needed unless you plan to
    // re-use them when linking other shader programs.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    const std::vector<glm::vec3> vertices{
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.0f, 0.5f, 0.0f}
    };

    GLuint vertexBuffer;
    glCreateBuffers(
        1, // the amount of buffers to create
        &vertexBuffer // the array (in this case just a pointer to our single buffer) to write said buffer indices to
    );

    // Uploads our vertex data to the buffer we just created.
    glNamedBufferStorage(
        vertexBuffer, // the buffer to upload to
        3 * sizeof(glm::vec3), // size
        vertices.data(), // data pointer
        0 // the flags, just leave blank usually
    );

    // This part is something that trips up beginners quite often. A vertex array object is an object that describes
    // what data and what layout that data is in within our buffer. We first create one of these VAOs.
    //
    // For more details you should reference the LearnOpenGL tutorial chapter, under the Vertex Array Object header.
    // https://learnopengl.com/Getting-started/Hello-Triangle
    GLuint vertexArrayObject;
    glCreateVertexArrays(1, &vertexArrayObject);

    // This call binds a buffer, in this case our vertex buffer, to a vertex array object.
    // The binding, which is NOT the same as a location. A binding specifies the input rate, offset and stride.
    // Input rate can be per vertex or per object. The offset is the offset into the buffer in bytes where our
    // data starts. The stride is the size of each element in our buffer in bytes.
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexBuffer.xhtml
    glVertexArrayVertexBuffer(
        vertexArrayObject, // Vertex array object
        0, // Binding
        vertexBuffer, // Buffer
        0, // Offset in bytes
        sizeof(glm::vec3) // Stride in bytes
    );

    // This call defines the format for our vertex array object attribute. This will tell OpenGL what type, size and
    // offset to use to access this attribute in our buffer.
    glVertexArrayAttribFormat(
        vertexArrayObject, // vao
        0, // attribute index
        3, // size in whatever type you specify as the next argument.
        GL_FLOAT, // type of element, float in this case
        GL_FALSE, // is the element normalized?
        0 // The offset within this attribute in bytes
    );

    // Enables the vertex array object attribute which we have been setting up at location 0.
    glEnableVertexArrayAttrib(
        vertexArrayObject, // vao
        0 // index
    );

    // This call couples our attribute index to our binding index.
    glVertexArrayAttribBinding(
        vertexArrayObject, // vao
        0, // attribute index
        0 // binding index
    );

    while (!glfwWindowShouldClose(window)) {
        // Checks and processes window, keyboard, mouse, etc. events.
        glfwPollEvents();

        // Clears the backbuffer, which is the window surface we are rendering to. This clears to whatever color you
        // specified as clear color in the glClearColor call. You may always change the clear color by calling it again.
        glClear(GL_COLOR_BUFFER_BIT);

        // Binds the shader program to our pipeline.
        glUseProgram(shaderProgram);

        // Binds our vertex array object, so OpenGL knows the structure of what is in our vertex buffer.
        glBindVertexArray(vertexArrayObject);

        // This is our most basic form of draw calls. This draws the triangle WITHOUT USING AN INDEX BUFFER.
        // Index buffers are extremely important since they save us memory and are much faster performance wise.
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // This swaps the back buffer to the window surface, essentially copying the image we were rendering to
        // to our window so we have an actual output that is on our screen instead of just on the GPU.
        glfwSwapBuffers(window);
    }

    // DON'T FORGET TO DELETE ANY RESOURCES YOU HAVE CREATED!!!!
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteProgram(shaderProgram);
    destroyWindow(window);

    return 0;
}
