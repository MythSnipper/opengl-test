#define STB_IMAGE_IMPLEMENTATION
#include "nucklib.hpp"

namespace nuck{
    WindowManager::WindowManager(uint8_t opengl_context_version_major, uint8_t opengl_context_version_minor, uint32_t window_width, uint32_t window_height, char* window_title){
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
        this->window_width = window_width;
        this->window_height = window_height;
        aspect_ratio = (float)window_width/(float)window_height;
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, window_framebuffer_size_callback);
    }
    WindowManager::~WindowManager(){
        puts("Killing WindowManager");
        if(killGLFW){
            glfwTerminate();
        }
    }
    void WindowManager::window_framebuffer_size_callback(GLFWwindow* window, int new_width, int new_height){
        WindowManager* vel = (WindowManager*)glfwGetWindowUserPointer(window);
        printf("Framebuffer size changed to: %dx%d!\n", new_width, new_height);
        glViewport(0, 0, new_width, new_height);
        vel->window_width = new_width;
        vel->window_height = new_height;
        vel->aspect_ratio = (float)new_width/(float)new_height;
    }
    int WindowManager::window_should_exit(){
        return glfwWindowShouldClose(window);
    }
    void WindowManager::refresh(){
        glfwSwapBuffers(window);
    }
    void WindowManager::close_window(){
        glfwSetWindowShouldClose(window, true);
    }



    InputManager::InputManager(GLFWwindow* window){
        this->window = window;
    }
    void InputManager::process_input(){
        glfwPollEvents();
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
        const int* vel = values.begin();
        switch(values.size()){
            case 1:
                glUniform1i(uid, vel[0]);
            break;
            case 2:
                glUniform2i(uid, vel[0], vel[1]);
            break;
            case 3:
                glUniform3i(uid, vel[0], vel[1], vel[2]);
            break;
            case 4:
                glUniform4i(uid, vel[0], vel[1], vel[2], vel[3]);
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
        const float* vel = values.begin();
        switch(values.size()){
            case 1:
                glUniform1f(uid, vel[0]);
            break;
            case 2:
                glUniform2f(uid, vel[0], vel[1]);
            break;
            case 3:
                glUniform3f(uid, vel[0], vel[1], vel[2]);
            break;
            case 4:
                glUniform4f(uid, vel[0], vel[1], vel[2], vel[3]);
            break;
            default:
                printf("Invalid number of values to set uniform\nExpected 1-4, got %d\n", values.size());
                throw std::runtime_error(" ^ ^");
        }
    }
    void ShaderProgram::set_mat4(char* name, bool transpose, glm::mat4 matrix){
        set_mat4(glGetUniformLocation(id, name), transpose, matrix);
    }
    void ShaderProgram::set_mat4(UniformID uid, bool transpose, glm::mat4 matrix){
        glUniformMatrix4fv(uid, 1, (transpose) ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix));
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



    Texture2D::Texture2D(char* file_path, GLenum internal_format){
        glGenTextures(1, &id);
        fill(file_path, internal_format);
    }
    Texture2D::Texture2D(uint8_t* data, uint32_t width, uint32_t height, GLenum image_format, GLenum internal_format){
        glGenTextures(1, &id);
        fill(data, width, height, image_format, internal_format);
    }
    void Texture2D::fill(char* file_path, GLenum internal_format){
        //load texture
        uint8_t* data = stbi_load(file_path, &texture_width, &texture_height, &color_channels_count, 0);
        if(!data){
            printf("Failed to load texture image %s\n", file_path);
            throw std::runtime_error(" ^ ^");
        }
        if(color_channels_count != 3 && color_channels_count != 4){
            printf("Invalid color channels count for texture image: %d\n", color_channels_count);
            throw std::runtime_error(" ^ ^");
        }
        fill(data, texture_width, texture_height, (color_channels_count == 4) ? GL_RGBA : GL_RGB, internal_format);
        stbi_image_free(data);
    }
    void Texture2D::fill(uint8_t* data, uint32_t width, uint32_t height, GLenum image_format, GLenum internal_format){
        if(internal_format == 0){
            internal_format = image_format;
        }
        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    void Texture2D::bind(){
        glBindTexture(GL_TEXTURE_2D, id);
    }
    void Texture2D::bind_texture_unit(GLenum texture_unit){
        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, id);
    }



    void GL::set_wireframe_mode(bool enable){
        wireframe_mode = enable;
        glPolygonMode(GL_FRONT_AND_BACK, (enable) ? GL_LINE : GL_FILL);
    }
    void GL::set_background_color(uint8_t r, uint8_t g, uint8_t b){
        background_color = {r/255.0f, g/255.0f, b/255.0f, 1.0f};
        glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
    }
    void GL::set_background_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
        background_color = {r/255.0f, g/255.0f, b/255.0f, a/255.0f};
        glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
    }
    void GL::set_background_color(float r, float g, float b){
        background_color = {r, g, b};
        glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
    }
    void GL::set_background_color(float r, float g, float b, float a){
        background_color = {r, g, b, a};
        glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
    }
    void GL::set_background_color(uint32_t color){
        background_color = {((color >> 16) & 0xFF)/255.0f, ((color >> 8) & 0xFF)/255.0f, (color & 0xFF)/255.0f, 1.0f};
        glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
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
        printf("Wireframe mode: %s\n", (wireframe_mode) ? "On" : "Off");
        printf("background color: (%f, %f, %f, %f)\n", background_color.r, background_color.g, background_color.b, background_color.a);
        printf("Depth testing: %s\n", (depth_test) ? "On" : "Off");

        int nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        printf("Number of vertex attributes available: %d\n", nrAttributes);
    }
    void GL::set_depth_test(bool enable){
        depth_test = enable;
        glEnable(GL_DEPTH_TEST);
    }
    void GL::set_vsync(bool enable){
        vsync = enable;
        glfwSwapInterval(enable);
    }


    //Engine
    class GameObject{
        public:
        std::string name = NULL;
        GameObject* parent = NULL;
        std::vector<GameObject*> children;

        std::vector<void*> Components;

        private:




    };
    class Mesh{
        public:
        VAO VAO;
        VBO VBO;
        EBO EBO;

        Mesh(){
            
        }


        private:



    };









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
    template double clamp<double>(double, double, double);
    template long double clamp<long double>(long double, long double, long double);

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
    template void clamp<double>(double*, double, double);
    template void clamp<long double>(long double*, long double, long double);
    
    template<typename T> T abs(T num){
        return (num > 0) ? num : -num;
    }
    template int abs<int>(int);
    template float abs<float>(float);
    template double abs<double>(double);
    template long double abs<long double>(long double);

    Complex operator+(const Complex& num1, const Complex& num2){
        return Complex(num1.real + num2.real, num1.imaginary + num2.imaginary);
    }
    Complex operator-(const Complex& num1, const Complex& num2){
        return Complex(num1.real - num2.real, num1.imaginary - num2.imaginary);
    }
    Complex operator*(const Complex& num1, const Complex& num2){
        return Complex((num1.real * num2.real) - (num1.imaginary * num2.imaginary), (num1.real * num2.imaginary) + (num2.real * num1.imaginary));
    }
    uint32_t mandelbrot(const Complex& num, uint32_t iterations, uint32_t limit){
        double zr = 0.0f, zi = 0.0f;
        double zr2 = 0.0f, zi2 = 0.0f;
    
        for(uint32_t i = 0; i < iterations; ++i){
            double temp = zr2 - zi2 + (double)num.real;
            zi = 2.0f * zr * zi + (double)num.imaginary;
            zr = temp;
    
            zr2 = zr * zr;
            zi2 = zi * zi;
    
            if(zr2 + zi2 > limit)
                return i;
        }
        return iterations;
    }
    


}