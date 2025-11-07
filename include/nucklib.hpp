#ifndef NUCKLIB_HPP
#define NUCKLIB_HPP


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fstream>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace nuck{
    class WindowManager{
        public:
        GLFWwindow* window;
    
        WindowManager(int opengl_context_version_major, int opengl_context_version_minor, int window_width, int window_height, char* window_title);
        ~WindowManager();
        static void window_framebuffer_size_callback(GLFWwindow* window, int window_width, int window_height);
        int window_should_exit();
        void refresh();
        void close_window();

        private:
        bool killGLFW = false;

        
    };
    class InputManager{
        public:
        GLFWwindow* window;

        InputManager(GLFWwindow* window);
        void process_input();
        bool key_down(uint32_t key_code);

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
        ShaderProgram(char** vert_source, char** frag_source);
        ShaderProgram(char* vert_file, char* frag_file);
        void activate();
        private:
        

    };
    class VBO{
        public:
        uint32_t id;

        VBO();
        VBO(float vertices[], size_t vertices_size, GLenum usage);
        void bind();
        void unbind();
        void fill(float vertices[], size_t vertices_size, GLenum usage);
        private:


    };
    class VAO{
        public:
        uint32_t id;

        VAO();
        void bind();
        void unbind();
        private:


    };
    class EBO{
        public:
        uint32_t id;

        EBO();
        EBO(uint32_t indices[], size_t indices_size, GLenum usage);
        void bind();
        void unbind();
        void fill(uint32_t indices[], size_t indices_size, GLenum usage);
        private:


    };
    class GL{
        public:
        void wireframe_mode(bool enable);
        void info();

    };






    
    char* read_file(const char* filename);





}




#endif