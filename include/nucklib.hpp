#ifndef NUCKLIB_HPP
#define NUCKLIB_HPP

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <iostream>
#include <fstream>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace nuck{
    struct Color{
        float r;
        float g;
        float b;
        float a = 1.0f;
    };
    struct ColorRGBA{
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    struct Complex{
        double real = 0.0;
        double imaginary = 0.0;
    };
    struct Vertex{
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoords;
    };
    typedef int UniformID;


    class WindowManager{
        public:
        GLFWwindow* window;
        uint32_t window_width;
        uint32_t window_height;
        float aspect_ratio;

        WindowManager(uint8_t opengl_context_version_major, uint8_t opengl_context_version_minor, uint32_t window_width, uint32_t window_height, char* window_title);
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

        InputManager(GLFWwindow* window);
        void process_input();
        bool key_down(uint32_t key_code);

        private:
        GLFWwindow* window;

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
        void set_bool(char* name, std::initializer_list<int> values);
        void set_bool(UniformID uid, std::initializer_list<int> values);
        void set_int(char* name, std::initializer_list<int> values);
        void set_int(UniformID uid, std::initializer_list<int> values);
        void set_float(char* name, std::initializer_list<float> values);
        void set_float(UniformID uid, std::initializer_list<float> values);
        void set_mat4(char* name, bool transpose, glm::mat4 matrix);
        void set_mat4(UniformID uid, bool transpose, glm::mat4 matrix);
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
    class Texture2D{
        public:
        uint32_t id;

        Texture2D(char* file_path, GLenum internal_format);
        Texture2D(uint8_t* data, uint32_t width, uint32_t height, GLenum image_format, GLenum internal_format);
        void fill(char* file_path, GLenum internal_format);
        void fill(uint8_t* data, uint32_t width, uint32_t height, GLenum image_format, GLenum internal_format);
        void bind();
        void bind_texture_unit(GLenum texture_unit);

        private:
        int texture_width;
        int texture_height;
        int color_channels_count;
    };
    class GL{
        public:
        bool wireframe_mode = false;
        Color background_color;
        bool depth_test = false;
        bool vsync = true;

        void set_wireframe_mode(bool enable);
        void set_background_color(uint8_t r, uint8_t g, uint8_t b);
        void set_background_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void set_background_color(float r, float g, float b);
        void set_background_color(float r, float g, float b, float a);
        void set_background_color(uint32_t color);
        void set_depth_test(bool enable);
        void set_vsync(bool enable);
        void info();
        private:


    };





    //Engine
    class Mesh{
        public:
        VAO vao;
        VBO vbo;
        EBO ebo;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        
        Mesh(const std::vector<Vertex>& verts, const std::vector<uint32_t>& inds);
        void draw();

        private:



    };





    
    class Component{
        public:
        GameObject* parent = nullptr;

        virtual void Init(){

        }
        virtual void Update(){

        }
        virtual void Draw(){

        }
        private:

    };










    //GL related




    //others
    char* read_file(const char* filename);
    template<typename T> T clamp(T num, T min, T max);
    template<typename T> void clamp(T* num, T min, T max);
    template<typename T> T abs(T num);
    Complex operator+(const Complex& num1, const Complex& num2);
    Complex operator-(const Complex& num1, const Complex& num2);
    Complex operator*(const Complex& num1, const Complex& num2);
    uint32_t mandelbrot(const Complex& num, uint32_t iterations, uint32_t limit);





    
}




#endif