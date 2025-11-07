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
    void WindowManager::close_window(){
        glfwSetWindowShouldClose(window, true);
    }



    InputManager::InputManager(GLFWwindow* window){
        this->window = window;
    }
    void InputManager::process_input(){
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
    }
    bool InputManager::key_down(uint32_t key_code){
        if(glfwGetKey(window, key_code) == GLFW_PRESS){
            return true;
        }
        return false;
    }



    VertexShader::VertexShader(char** shader_source_addr){
        id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(id, 1, shader_source_addr, NULL);
        glCompileShader(id);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(id, 512, NULL, infoLog);
                printf("VERTEX SHADER COMPILATION FAILED! \n%s\n", infoLog);
            }
            else{
                puts("VERTEX SHADER COMPILED SUCCESSFULLY");
            }
        }
    }
    VertexShader::VertexShader(char* filename){
        char* shader_source = read_file(filename);
        id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(id, 1, &shader_source, NULL);
        glCompileShader(id);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(id, 512, NULL, infoLog);
                printf("VERTEX SHADER COMPILATION FAILED! \n%s\n", infoLog);
            }
            else{
                puts("VERTEX SHADER COMPILED SUCCESSFULLY");
            }
        }
    }
    VertexShader::~VertexShader(){
        if(id != 0){
            puts("Killing VertexShader");
            glDeleteShader(id);
            id = 0;
        }
    }



    FragmentShader::FragmentShader(char** shader_source_addr){
        id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(id, 1, shader_source_addr, NULL);
        glCompileShader(id);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(id, 512, NULL, infoLog);
                printf("FRAGMENT SHADER COMPILATION FAILED! \n%s\n", infoLog);
            }
            else{
                puts("FRAGMENT SHADER COMPILED SUCCESSFULLY");
            }
        }
    }
    FragmentShader::FragmentShader(char* filename){
        char* shader_source = read_file(filename);
        id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(id, 1, &shader_source, NULL);
        glCompileShader(id);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(id, 512, NULL, infoLog);
                printf("FRAGMENT SHADER COMPILATION FAILED! \n%s\n", infoLog);
            }
            else{
                puts("FRAGMENT SHADER COMPILED SUCCESSFULLY");
            }
        }
    }
    FragmentShader::~FragmentShader(){
        if(id != 0){
            puts("Killing FragmentShader");
            glDeleteShader(id);
            id = 0;
        }
    }



    ShaderProgram::ShaderProgram(VertexShader* vertex_shader, FragmentShader* fragment_shader){
        id = glCreateProgram();
        glAttachShader(id, vertex_shader->id);
        glAttachShader(id, fragment_shader->id);
        glLinkProgram(id);
        {
            int success;
            char infoLog[512];
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if(!success){
                glGetProgramInfoLog(id, 512, NULL, infoLog);
                printf("SHADER PROGRAM LINK FAILED! \n%s\n", infoLog);
            }
            else{
                puts("SHADER PROGRAM LINKED SUCCESSFULLY");
            }
        }
    }
    ShaderProgram::ShaderProgram(char** vert_source, char** frag_source){
        VertexShader VertexShader(vert_source);
        FragmentShader FragmentShader(frag_source);
        ShaderProgram(&VertexShader, &FragmentShader);

    }
    ShaderProgram::ShaderProgram(char* vert_file, char* frag_file){
        VertexShader VertexShader(vert_file);
        FragmentShader FragmentShader(frag_file);
        ShaderProgram(&VertexShader, &FragmentShader);
    }
    void ShaderProgram::activate(){
        glUseProgram(id);
    }



    VBO::VBO(){
        glGenBuffers(1, &id);
    }
    VBO::VBO(float vertices[], size_t vertices_size, GLenum usage){
        glGenBuffers(1, &id);
        fill(vertices, vertices_size, usage);
    }
    void VBO::bind(){
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }
    void VBO::unbind(){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void VBO::fill(float vertices[], size_t vertices_size, GLenum usage){
        bind();
        glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, usage);
    }

    VAO::VAO(){
        glGenVertexArrays(1, &id);
    }
    void VAO::bind(){
        glBindVertexArray(id);
    }
    void VAO::unbind(){
        glBindVertexArray(0);
    }

    EBO::EBO(){
        glGenBuffers(1, &id);
    }
    EBO::EBO(uint32_t indices[], size_t indices_size, GLenum usage){
        glGenBuffers(1, &id);
        fill(indices, indices_size, usage);
    }
    void EBO::bind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }
    void EBO::unbind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    void EBO::fill(uint32_t indices[], size_t indices_size, GLenum usage){
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, usage);
    }



    void GL::wireframe_mode(bool enable){
        glPolygonMode(GL_FRONT_AND_BACK, (enable) ? GL_LINE : GL_FILL);
    }
    void GL::info(){
        int nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        printf("Number of vertex attributes available: %d\n", nrAttributes);
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