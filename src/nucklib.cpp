#include "nucklib.hpp"

namespace nuck{
    WindowManager::WindowManager(int opengl_context_version_major, int opengl_context_version_minor, int window_width, int window_height, char* window_title){
        glfwInit();
        killGLFW = true;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_context_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_context_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
        if(!window){
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            throw std::runtime_error("Failed to initialize GLAD");
        }
        glViewport(0, 0, window_width, window_height);
        glfwSetFramebufferSizeCallback(window, window_framebuffer_size_callback);
    }
    WindowManager::~WindowManager(){
        puts("Killing WindowManager");
        if(killGLFW){
            glfwTerminate();
        }
    }
    void WindowManager::window_framebuffer_size_callback(GLFWwindow* window, int window_width, int window_height){
        printf("Framebuffer size changed to: %dx%d!\n", window_width, window_height);
        glViewport(0, 0, window_width, window_height);
    }
    int WindowManager::window_should_exit(){
        return glfwWindowShouldClose(window);
    }
    void WindowManager::refresh(){
        glfwPollEvents();
        glfwSwapBuffers(window);
    }



    InputManager::InputManager(GLFWwindow* window){
        this->window = window;
    }
    void InputManager::process_input(){
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
    }



    VertexShader::VertexShader(char** shader_source_addr){
        shaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shaderID, 1, shader_source_addr, NULL);
        glCompileShader(shaderID);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
                printf("VERTEX SHADER COMPILATION FAILED! \n%s\n", infoLog);
            }
            else{
                puts("VERTEX SHADER COMPILED SUCCESSFULLY");
            }
        }
    }
    VertexShader::VertexShader(char* filename){
        char* shader_source = read_file(filename);
        shaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shaderID, 1, &shader_source, NULL);
        glCompileShader(shaderID);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
                printf("VERTEX SHADER COMPILATION FAILED! \n%s\n", infoLog);
            }
            else{
                puts("VERTEX SHADER COMPILED SUCCESSFULLY");
            }
        }
    }
    VertexShader::~VertexShader(){
        if(shaderID != 0){
            puts("Killing VertexShader");
            glDeleteShader(shaderID);
            shaderID = 0
        }
    }



    FragmentShader::FragmentShader(char** shader_source_addr){
        shaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shaderID, 1, shader_source_addr, NULL);
        glCompileShader(shaderID);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
                printf("FRAGMENT SHADER COMPILATION FAILED! \n%s\n", infoLog);
            }
            else{
                puts("FRAGMENT SHADER COMPILED SUCCESSFULLY");
            }
        }
    }
    FragmentShader::FragmentShader(char* filename){
        char* shader_source = read_file(filename);
        shaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shaderID, 1, &shader_source, NULL);
        glCompileShader(shaderID);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
                printf("FRAGMENT SHADER COMPILATION FAILED! \n%s\n", infoLog);
            }
            else{
                puts("FRAGMENT SHADER COMPILED SUCCESSFULLY");
            }
        }
    }
    FragmentShader::~FragmentShader(){
        if(shaderID != 0){
            puts("Killing FragmentShader");
            glDeleteShader(shaderID);
            shaderID = 0
        }
    }



    ShaderProgram::ShaderProgram(VertexShader* vertex_shader, FragmentShader* fragment_shader){
        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertex_shader->shaderID);
        glAttachShader(shaderProgramID, fragment_shader->shaderID);
        glLinkProgram(shaderProgramID);
        {
            int success;
            char infoLog[512];
            glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
            if(!success){
                glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
                printf("SHADER PROGRAM LINK FAILED! \n%s\n", infoLog);
            }
            else{
                puts("SHADER PROGRAM LINKED SUCCESSFULLY");
            }
        }
    }
    void ShaderProgram::activate(){
        glUseProgram(shaderProgramID);
    }





















    char* read_file(const char* filename){
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if(!file){
            throw std::runtime_error("Failed to open file for reading");
        }
        int size = file.tellg();
        file.seekg(0, std::ios::beg);

        char* buf = new char[size + 1];
        file.read(buf, size);
        buf[size] = '\0';

        return buf;
    }


}