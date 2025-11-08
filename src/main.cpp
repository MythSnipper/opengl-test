#include "main.hpp"

int main(int argc, char* argv[]){

    nuck::WindowManager WindowManager(3, 3, 1280, 720, "nuckGL");

    nuck::InputManager InputManager(WindowManager.window);

    nuck::ShaderProgram ShaderProgram("shaders/nuck.vert", "shaders/nuck.frag");
    ShaderProgram.activate();

    //data
    float vertices[] = {
        -0.7f, 0.7f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f, //top left
        0.7f, 0.7f, 0.0f,     0.0f, 1.0f, 0.0f,    1.0f, 1.0f, //top right
        0.7f, -0.7f, 0.0f,   0.0f, 1.0f, 1.0f,    1.0f, 0.0f, //bottom right
        -0.7f, -0.7f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, //bottom left
    };
    uint32_t indices[] = {
        0, 1, 2,
        0, 3, 2,
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    nuck::EBO EBO(indices, sizeof(indices), GL_STATIC_DRAW);
    EBO.bind();


    //texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //only useful if clamp to border
    float borderColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    //texture filtering method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //linear bitmap, nearest filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //linear filtering

    nuck::Texture2D texture1("textures/niko.png");
    texture1.bind();

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
            vertices[0] -= speed;
        }
        if(InputManager.key_down(GLFW_KEY_D)){
            vertices[0] += speed;
        }
        if(InputManager.key_down(GLFW_KEY_W)){
            vertices[1] += speed;
        }
        if(InputManager.key_down(GLFW_KEY_S)){
            vertices[1] -= speed;
        }
        if(InputManager.key_down(GLFW_KEY_E)){
            spd += 0.02;
        }
        if(InputManager.key_down(GLFW_KEY_Q)){
            spd -= 0.02;
        }
        
        //restrain the values like putting the black man in handcuffs
        nuck::clamp(&vertices[0], -1.0f, 1.0f);
        nuck::clamp(&vertices[1], -0.99f, 0.99f);
        nuck::clamp(&spd, 0.01f, 100000.0f);

        VBO.fill(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);

        //rendering
        //clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        ShaderProgram.activate();
        texture1.bind_texture_unit(GL_TEXTURE0);
        VAO.bind();
        VBO.bind();
        EBO.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);
        
        WindowManager.refresh();
    }

    return 0;
}


