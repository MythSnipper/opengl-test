#include "main.hpp"

int main(int argc, char* argv[]){
    #ifdef _WIN32
        std::cout << "Running on windows\n";
    #else
        std::cout << "Running on linux\n";
    #endif

    nuck::WindowManager WindowManager(3, 3, 1920, 1080, "nuckGL");

    nuck::InputManager InputManager(WindowManager.window);

    nuck::ShaderProgram ShaderProgram("shaders/nuck.vert", "shaders/nuck.frag");
    ShaderProgram.activate();
    

    //data
    float vertices[] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    uint32_t indices[] = {
        0, 1, 2
    };

    nuck::VAO VAO;
    VAO.bind();


    nuck::VBO VBO(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
    VBO.bind();

    nuck::EBO EBO(indices, sizeof(indices), GL_STATIC_DRAW);
    EBO.bind();

    //vertex attribute position in vertex shader
    //size of vertex attribute(number of values)
    //data type
    //normalize data?
    //stride(how many bytes to skip to go next attribute)
    //offset(how many bytes to skip before reading first attribute)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    nuck::GL GL;
    GL.wireframe_mode(false);
    GL.info();



    float speed = 0.01f;
    float spd = 1;
    //Main loop
    while(!WindowManager.window_should_exit()){
        //input
        InputManager.process_input();
        if(InputManager.key_down(GLFW_KEY_A)){
            vertices[12] -= speed;
        }
        if(InputManager.key_down(GLFW_KEY_D)){
            vertices[12] += speed;
        }
        if(InputManager.key_down(GLFW_KEY_W)){
            vertices[13] += speed;
        }
        if(InputManager.key_down(GLFW_KEY_S)){
            vertices[13] -= speed;
        }
        if(InputManager.key_down(GLFW_KEY_E)){
            spd += 0.02;
        }
        if(InputManager.key_down(GLFW_KEY_Q)){
            spd -= 0.02;
        }
        if(vertices[12] < -1){
            vertices[12] = -1.0f;
        }
        if(vertices[12] > 1){
            vertices[12] = 1.0f;
        }
        if(vertices[13] < -0.99){
            vertices[13] = -0.99f;
        }
        if(vertices[13] > 0.99){
            vertices[13] = 0.99f;
        }
        if(spd > 100000){
            spd = 100000.0f;
        }
        if(spd < 0.01){
            spd = 0.01f;
        }
        VBO.fill(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);


        //rendering
        //clear screen
        glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //set rendering color using uniform
        ShaderProgram.activate();
        GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "\n\n\n\n\n\nOpenGL error: " << err << std::endl;
    }
        VAO.bind();
        VBO.bind();
        EBO.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        WindowManager.refresh();
        while(true);
    }

    return 0;
}


