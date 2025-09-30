#include <main.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    std::cout << "framebuffer size changed to: " << width << "x" << height << "!\n";
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char* argv[]){
    #ifdef _WIN32
        std::cout << "Running on windows\n";
    #else
        std::cout << "Running on linux\n";
    #endif

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,  3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,  3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "nuck OpenGL test", NULL, NULL);
    if(!window){
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD\n";
        return 1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";
    uint32_t vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    {
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "VERTEX SHADER COMPILATION FAILED! \n" << infoLog << "\n";
        }
        else{
            std::cout << "VERTEX SHADER COMPILED SUCCESSFULLY\n";
        }
    }

    char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(0.96078f, 0.67058f, 0.72549f, 1.0f);\n"
    "}\n";
    uint32_t fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    {
        int success;
        char infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "FRAGMENT SHADER COMPILATION FAILED! \n" << infoLog << "\n";
        }
        else{
            std::cout << "FRAGMENT SHADER COMPILED SUCCESSFULLY\n";
        }
    }

    uint32_t shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    {
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "SHADER PROGRAM LINK FAILED! \n" << infoLog << "\n";
        }
        else{
            std::cout << "SHADER PROGRAM LINKED SUCCESSFULLY\n";
        }
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //data
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    uint32_t VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)){
        //input
        processInput(window);

        //rendering
        glClearColor(0.35686f, 0.80784f, 0.98431f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}