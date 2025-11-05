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
        GLFWwindow* window;

        InputManager(GLFWwindow* window);
        void process_input();
    
        private:


    };
    class VertexShader{
        public:
        uint32_t id;

        VertexShader(char** shader_source_addr);
        VertexShader(char* filename);
        ~VertexShader();
        private:
        

    };
    class FragmentShader{
        public:
        uint32_t id;

        FragmentShader(char** shader_source_addr);
        FragmentShader(char* filename);
        ~FragmentShader();
        private:
        

    };
    class ShaderProgram{
        public:
        uint32_t id;

        ShaderProgram(VertexShader* vertex_shader, FragmentShader* fragment_shader);
        void activate();
        private:
        

    };
    class VBO{
        public:
        uint32_t id;

        VBO();
        VBO(float vertices[], size_t vertices_size, GLenum usage);
        void bind();
        void fill(float vertices[], size_t vertices_size, GLenum usage);
        private:


    };
    class VAO{
        public:
        uint32_t id;

        VAO();
        void bind();
        private:


    };
    class EBO{
        public:
        uint32_t id;

        EBO();
        EBO(uint32_t indices[], size_t indices_size, GLenum usage);
        void bind();
        void fill(uint32_t indices[], size_t indices_size, GLenum usage);
        private:

        
    };






    
    char* read_file(const char* filename);





}




#endif