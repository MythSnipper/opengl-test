#include "main.hpp"

int main(int argc, char* argv[]){

    nuck::WindowManager WindowManager(3, 3, 1024, 1024, "nuckGL");

    nuck::InputManager InputManager(WindowManager.window);

    nuck::ShaderProgram ShaderProgram("shaders/nuck.vert", "shaders/nuck.frag");
    
    ShaderProgram.activate();
    

    //data
    float vertices[] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    int numOfVertices = 3;
    uint32_t indices[] = {
        0, 1, 2
    };

    nuck::VAO VAO;
    VAO.bind();

    nuck::VBO VBO(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
    VBO.bind();

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

    nuck::EBO EBO(indices, sizeof(indices), GL_STATIC_DRAW);
    EBO.bind();



    nuck::GL GL;
    GL.set_wireframe_mode(false);
    GL.set_background_color(0x104C7E);

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
        
        //restrain the values like putting the black man in handcuffs
        nuck::clamp(&vertices[12], -1.0f, 1.0f);
        nuck::clamp(&vertices[13], -0.99f, 0.99f);
        nuck::clamp(&spd, 0.01f, 100000.0f);

        VBO.fill(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);

        //rendering
        //clear screen
        glClearColor(GL.background_color.r, GL.background_color.g, GL.background_color.b, GL.background_color.a);
        glClear(GL_COLOR_BUFFER_BIT);

        ShaderProgram.activate();
        
        VAO.bind();
        VBO.bind();
        EBO.bind();
        glDrawElements(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, 0);
        
        WindowManager.refresh();
    }

    return 0;
}


