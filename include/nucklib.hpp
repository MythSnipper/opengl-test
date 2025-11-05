#ifndef NUCKLIB_HPP
#define NUCKLIB_HPP


#include <cstdio>
#include <cstdlib>

#include <fstream>

#include <glad/glad.h>
#include <glfw/glfw3.h>



namespace nuck{
    class WindowManager{
        public:
        GLFWwindow* window;
    
        WindowManager(int opengl_context_version_major, int opengl_context_version_minor, int window_width, int window_height, char* window_title);
        ~WindowManager();
        static void window_framebuffer_size_callback(GLFWwindow* window, int window_width, int window_height);
        int window_should_exit();
        void refresh();

        private:
        bool killGLFW = false;

        
    };
    class InputManager{
        public:

        InputManager(GLFWwindow* window);
        void process_input();
    
        private:
        GLFWwindow* window;

    };
    class VertexShader{
        public:
        uint32_t shaderID;

        VertexShader(char** shader_source_addr);
        VertexShader(char* filename);
        ~VertexShader();
        private:
        

    };
    class FragmentShader{
        public:
        uint32_t shaderID;

        FragmentShader(char** shader_source_addr);
        FragmentShader(char* filename);
        ~FragmentShader();
        private:
        

    };
    class ShaderProgram{
        public:
        uint32_t shaderProgramID;

        ShaderProgram(VertexShader* vertex_shader, FragmentShader* fragment_shader);
        void activate();
        private:
        

    };


    
    char* read_file(const char* filename);





}




#endif