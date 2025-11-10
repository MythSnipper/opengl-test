#include "main.hpp"

int main(int argc, char* argv[]){

    nuck::WindowManager WindowManager(3, 3, 1280, 720, "nuckGL");

    nuck::InputManager InputManager(WindowManager.window);

    //must do configs
    nuck::GL GL;
    GL.set_wireframe_mode(false);
    GL.set_background_color(0x104C7E);
    GL.set_depth_test(true);
    GL.set_vsync(true);

    stbi_set_flip_vertically_on_load(true);

    nuck::ShaderProgram ShaderProgram("shaders/nuck.vert", "shaders/nuck.frag");
    ShaderProgram.activate();

    //data
    float vertices[] = {
        //pos                color               texpos
        -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, //front face 0
        0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, //back face 4
        0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,

        -0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, //left 8
        -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,

        0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, //right 12
        0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, //top 16
        0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, //bottom 20
        0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f, //23

    };
    uint32_t indices[] = {
        0, 1, 2,
        1, 2, 3,

        4, 5, 6,
        5, 6, 7,

        8, 9, 10,
        9, 10, 11,

        12, 13, 14,
        13, 14, 15,

        16, 17, 18,
        17, 18, 19,

        20, 21, 22,
        21, 22, 23,
        
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

    //load textures
    nuck::Texture2D texture0("textures/niko.png", GL_RGBA);
    texture0.bind();

    nuck::Texture2D texture1("textures/grass.png", GL_RGBA);
    texture1.bind();

    double lastTime = glfwGetTime();
    double time = glfwGetTime();
    double dt, fps;

    float angleX = 0.0f;
    float angleY = 0.0f;
    float angleZ = 0.0f;

    float angularVelX = 0.0f;
    float angularVelY = 0.0f;
    float angularVelZ = 0.0f;

    float accel = 0.3f;
    float damping = 0.95f;
    //Main loop
    while(!WindowManager.window_should_exit()){
        
        //input
        InputManager.process_input();
        if(InputManager.key_down(GLFW_KEY_W)){
            angularVelZ -= accel;
        }
        if(InputManager.key_down(GLFW_KEY_S)){
            angularVelZ += accel;
        }
        if(InputManager.key_down(GLFW_KEY_A)){
            angularVelX -= accel;
        }
        if(InputManager.key_down(GLFW_KEY_D)){
            angularVelX += accel;
        }
        if(InputManager.key_down(GLFW_KEY_E)){
            angularVelY -= accel;
        }
        if(InputManager.key_down(GLFW_KEY_Q)){
            angularVelY += accel;
        }

        angularVelX *= damping;
        angularVelY *= damping;
        angularVelZ *= damping;

        printf("angles: %f %f %f\n", angleX, angleY, angleZ);
        printf("angular velocities: %f %f %f\n", angularVelX, angularVelY, angularVelZ);

        angleX += angularVelX;
        angleY += angularVelY;
        angleZ += angularVelZ;
        
        //restrain the values like putting the black man in handcuffs
        angleX = fmod(angleX, 360.0f);
        angleY = fmod(angleY, 360.0f);
        angleZ = fmod(angleZ, 360.0f);


        //Vclip = Mprojection * Mview * Mmodel * Vlocal
        //fov, aspect ratio, near field, far field
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(angleZ), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(angleY), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(angleX), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), WindowManager.aspect_ratio, 0.1f, 100.0f);
        

        //rendering
        //clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ShaderProgram.activate();

        //set uniforms
        ShaderProgram.set_int("texture0", {0});
        ShaderProgram.set_int("texture1", {1});
        ShaderProgram.set_mat4("aModel", false, model);
        ShaderProgram.set_mat4("aView", false, view);
        ShaderProgram.set_mat4("aProjection", false, projection);

        texture0.bind_texture_unit(GL_TEXTURE0);
        texture1.bind_texture_unit(GL_TEXTURE1);
        VAO.bind();
        VBO.bind();
        EBO.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);
        
        WindowManager.refresh();
        time = glfwGetTime();
        dt = time - lastTime;
        fps = 1 / dt;
        lastTime = time;

        printf("dt: %lf fps: %lf\n", dt, fps);
    }

    return 0;
}


