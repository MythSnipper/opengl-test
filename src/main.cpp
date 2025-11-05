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
        -0.9f, -0.9f, 0.0f, //lower left corner
        -0.5f, 0.0f, 0.0f,  //left
        0.0f, 0.0f, 0.0f,   //middle
        0.5f, 0.0f, 0.0f,   //right
        0.9f, -0.9f, 0.0f,  //lower right corner
        -0.9f, 0.9f, 0.0f,  //upper left corner
        0.9f, 0.9f, 0.0f,   //upper right corner
    };
    unsigned int indices[] = { // note that we start from 0! //didn't ask
        0, 1, 2,
        4, 3, 2,
        5, 1, 2,
        6, 3, 2,
    };

    nuck::VAO VAO;
    VAO.bind();

    nuck::VBO VBO(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
    VBO.bind();

    //vertex attribute position 0 in vertex shader
    //size of vertex attribute(number of values)
    //data type
    //normalize data?
    //stride(how many bytes to skip to go next attribute)
    //offset(how many bytes to skip before reading first attribute)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    nuck::EBO EBO(indices, sizeof(indices), GL_STATIC_DRAW);
    EBO.bind();

    nuck::GL GL;
    GL.wireframe_mode(false);

    float speed = 0.02f;
    //Main loop
    while(!WindowManager.window_should_exit()){
        //input
        InputManager.process_input();
        if(InputManager.key_down(GLFW_KEY_A)){
            vertices[6] -= speed;
        }
        if(InputManager.key_down(GLFW_KEY_D)){
            vertices[6] += speed;
        }
        if(InputManager.key_down(GLFW_KEY_W)){
            vertices[7] += speed;
        }
        if(InputManager.key_down(GLFW_KEY_S)){
            vertices[7] -= speed;
        }
        if(vertices[6] < -1){
            vertices[6] = -1.0f;
        }
        if(vertices[6] > 1){
            vertices[6] = 1.0f;
        }
        if(vertices[7] < -0.99){
            vertices[7] = -0.99f;
        }
        if(vertices[7] > 0.99){
            vertices[7] = 0.99f;
        }

        VBO.fill(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);



        //rendering
        //clear screen
        glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ShaderProgram.activate();
        VAO.bind();
        EBO.bind();
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


        WindowManager.refresh();
    }

    return 0;
}


