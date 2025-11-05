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
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };
    unsigned int indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    nuck::VBO VBO(vertices, sizeof(vertices), GL_STATIC_DRAW);

    nuck::VAO VAO;
    VAO.bind();

    nuck::EBO EBO(indices, sizeof(indices), GL_STATIC_DRAW);


    //vertex attribute position 0 in vertex shader
    //size of vertex attribute(number of values)
    //data type
    //normalize data?
    //stride(how many bytes to skip to go next attribute)
    //offset(how many bytes to skip before reading first attribute)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Main loop
    while(!WindowManager.window_should_exit()){
        //input
        InputManager.process_input();

        //rendering
        //clear screen
        glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        VAO.bind();
        EBO.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        WindowManager.refresh();
    }

    return 0;
}








