#include "main.hpp"

int main(int argc, char* argv[]){
    #ifdef _WIN32
        std::cout << "Running on windows\n";
    #else
        std::cout << "Running on linux\n";
    #endif

    nuck::WindowManager WindowManager(3, 3, 800, 600, "nuckGL");

    nuck::InputManager InputManager(WindowManager.window);

    nuck::VertexShader VertexShader("shaders/nuck.vert");
    nuck::FragmentShader FragmentShader("shaders/nuck.frag");
    nuck::ShaderProgram ShaderProgram(&VertexShader, &FragmentShader);
    
    ShaderProgram.activate();
    VertexShader.~VertexShader();
    FragmentShader.~FragmentShader();

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

    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Main loop
    while(!WindowManager.window_should_exit()){
        //input
        InputManager.process_input();

        //rendering
        glClearColor(0.35686f, 0.80784f, 0.98431f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        WindowManager.refresh();
    }

    return 0;
}








