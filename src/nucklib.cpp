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
                throw std::runtime_error(" ^ ^");
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
                throw std::runtime_error(" ^ ^");
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
                throw std::runtime_error(" ^ ^");
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
                throw std::runtime_error(" ^ ^");
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
                throw std::runtime_error(" ^ ^");
            }
            else{
                puts("SHADER PROGRAM LINKED SUCCESSFULLY");
            }
        }
    }
    ShaderProgram::ShaderProgram(char** vert_source, char** frag_source){
        VertexShader vert(vert_source);
        FragmentShader frag(frag_source);

        id = glCreateProgram();
        glAttachShader(id, vert.id);
        glAttachShader(id, frag.id);
        glLinkProgram(id);
        {
            int success;
            char infoLog[512];
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if(!success){
                glGetProgramInfoLog(id, 512, NULL, infoLog);
                printf("SHADER PROGRAM LINK FAILED! \n%s\n", infoLog);
                throw std::runtime_error(" ^ ^");
            }
            else{
                puts("SHADER PROGRAM LINKED SUCCESSFULLY");
            }
        }
        vert.~VertexShader();
        frag.~FragmentShader();
    }
    ShaderProgram::ShaderProgram(char* vert_file, char* frag_file){
        VertexShader vert(vert_file);
        FragmentShader frag(frag_file);

        id = glCreateProgram();
        glAttachShader(id, vert.id);
        glAttachShader(id, frag.id);
        glLinkProgram(id);
        {
            int success;
            char infoLog[512];
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if(!success){
                glGetProgramInfoLog(id, 512, NULL, infoLog);
                printf("SHADER PROGRAM LINK FAILED! \n%s\n", infoLog);
                throw std::runtime_error(" ^ ^");
            }
            else{
                puts("SHADER PROGRAM LINKED SUCCESSFULLY");
            }
        }
        vert.~VertexShader();
        frag.~FragmentShader();
    }
    void ShaderProgram::set_bool(char* name, std::initializer_list<int> values){
        set_int(name, values);
    }
    void ShaderProgram::set_bool(UniformID uid, std::initializer_list<int> values){
        set_int(uid, values);
    }
    void ShaderProgram::set_int(char* name, std::initializer_list<int> values){
        set_int(glGetUniformLocation(id, name), values);
    }
    void ShaderProgram::set_int(UniformID uid, std::initializer_list<int> values){
        const int* veeronica = values.begin();
        switch(values.size()){
            case 1:
                glUniform1i(uid, veeronica[0]);
            break;
            case 2:
                glUniform2i(uid, veeronica[0], veeronica[1]);
            break;
            case 3:
                glUniform3i(uid, veeronica[0], veeronica[1], veeronica[2]);
            break;
            case 4:
                glUniform4i(uid, veeronica[0], veeronica[1], veeronica[2], veeronica[3]);
            break;
            default:
                printf("Invalid number of values to set uniform\nExpected 1-4, got %d\n", values.size());
                throw std::runtime_error(" ^ ^");
        }
    }
    void ShaderProgram::set_float(char* name, std::initializer_list<float> values){
        set_float(glGetUniformLocation(id, name), values);
    }
    void ShaderProgram::set_float(UniformID uid, std::initializer_list<float> values){
        const float* veeronica = values.begin();
        switch(values.size()){
            case 1:
                glUniform1f(uid, veeronica[0]);
            break;
            case 2:
                glUniform2f(uid, veeronica[0], veeronica[1]);
            break;
            case 3:
                glUniform3f(uid, veeronica[0], veeronica[1], veeronica[2]);
            break;
            case 4:
                glUniform4f(uid, veeronica[0], veeronica[1], veeronica[2], veeronica[3]);
            break;
            default:
                printf("Invalid number of values to set uniform\nExpected 1-4, got %d\n", values.size());
                throw std::runtime_error(" ^ ^");
        }
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



    void GL::set_wireframe_mode(bool enable){
        wireframe_mode = enable;
        glPolygonMode(GL_FRONT_AND_BACK, (enable) ? GL_LINE : GL_FILL);
    }
    void GL::set_background_color(uint8_t r, uint8_t g, uint8_t b){
        background_color = {r/255.0f, g/255.0f, b/255.0f, 1.0f};
    }
    void GL::set_background_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
        background_color = {r/255.0f, g/255.0f, b/255.0f, a/255.0f};
    }
    void GL::set_background_color(float r, float g, float b){
        background_color = {r, g, b};
    }
    void GL::set_background_color(float r, float g, float b, float a){
        background_color = {r, g, b, a};
    }
    void GL::set_background_color(uint32_t color){
        background_color = {((color >> 16) & 0xFF)/255.0f, ((color >> 8) & 0xFF)/255.0f, (color & 0xFF)/255.0f, 1.0f};
    }
    void GL::info(){
        for(int i=0;i<20;i++)printf("-");
        puts("");
        printf("OS: ");
        #ifdef _WIN32
            printf("windows\n");
        #else
            printf("linux\n");
        #endif
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
    template<typename T> T clamp(T num, T min, T max){
        if(num < min){
            return min;
        }
        else if(num > max){
            return max;
        }
        return num;
    }
    template int clamp<int>(int, int, int);
    template float clamp<float>(float, float, float);

    template<typename T> void clamp(T* num, T min, T max){
        if(*num < min){
            *num = min;
        }
        else if(*num > max){
            *num = max;
        }
    }
    template void clamp<int>(int*, int, int);
    template void clamp<float>(float*, float, float);


}