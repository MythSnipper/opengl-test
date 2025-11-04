#ifndef NUCKLIB_HPP
#define NUCKLIB_HPP

#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace nuck{

    class glfw{
        bool killGLFW;

        GLFW(const int opengl_context_version_major, const int opengl_context_version_minor, const int window_width, const int window_height, const char* window_title);
        ~GLFW();
        


    }





}




#endif