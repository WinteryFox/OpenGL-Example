This is a small OpenGL sample I set up for a friend who was interested in getting into computer graphics.
The sample will teach you to set up a project with CMake that uses [GLFW](https://github.com/glfw/glfw),
[GLM](https://github.com/g-truc/glm) and [glew](https://github.com/nigels-com/glew).
You should start by reading through the [CMakeLists.txt](CMakeLists.txt), which will teach you how CMake works
and how to include dependencies in your project. There's a lot more depth to CMake, but this will teach you
the fundamentals. Once you've done that, move on to the [main.cpp](main.cpp) file. Here we will create
a window with GLFW, load OpenGL function pointers using glew and then render a triangle to the window
with OpenGL using glm to store our vertices. I've left comments on pretty much everything. I hope they're easy
to understand, if you struggle to understand something feel free to create an issue.
