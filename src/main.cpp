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

    float quadVertices[] = {
        // positions   // texcoords
        -1.0f,  1.0f,  0.0f, 1.0f, // top-left
        -1.0f, -1.0f,  0.0f, 0.0f, // bottom-left
         1.0f, -1.0f,  1.0f, 0.0f, // bottom-right
         1.0f,  1.0f,  1.0f, 1.0f  // top-right
    };
    
    uint32_t quadIndices[] = {
        0, 1, 2,
        0, 2, 3
    };

    nuck::VAO VAO;
    VAO.bind();

    nuck::VBO VBO(quadVertices, sizeof(quadVertices), GL_STATIC_DRAW);
    VBO.bind();

    //vertex attribute position in vertex shader
    //size of vertex attribute(number of values)
    //data type
    //normalize data?
    //stride(how many bytes to skip to go next attribute)
    //offset(how many bytes to skip before reading first attribute)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    nuck::EBO EBO(quadIndices, sizeof(quadIndices), GL_STATIC_DRAW);
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


    //test
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(WindowManager.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    int iterations = 10000;
    int limit = 4;
    
    float xmin = -2.5f;
    float xmax = 1.0f;
    float ymin = -1.0f;
    float ymax = 1.0f;






    double lastTime = glfwGetTime();
    double time = glfwGetTime();
    double dt, fps;

    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 2.0f;

    float angleX = 0.0f;
    float angleY = 0.0f;
    float angleZ = 0.0f;

    float angularVelX = 0.0f;
    float angularVelY = 0.0f;
    float angularVelZ = 0.0f;

    float accel = 0.3f;
    float pos_speed = 0.1f;
    float damping = 0.98f;
    //Main loop
    while(!WindowManager.window_should_exit()){
        //input
        
        InputManager.process_input();
        if(InputManager.key_down(GLFW_KEY_W)){
            posZ -= pos_speed;
        }
        if(InputManager.key_down(GLFW_KEY_S)){
            posZ += pos_speed;
        }
        if(InputManager.key_down(GLFW_KEY_A)){
            posX += pos_speed;
        }
        if(InputManager.key_down(GLFW_KEY_D)){
            posX -= pos_speed;
        }
        if(InputManager.key_down(GLFW_KEY_SPACE)){
            posY -= pos_speed;
        }
        if(InputManager.key_down(GLFW_KEY_LEFT_SHIFT)){
            posY += pos_speed;
        }

        if(InputManager.key_down(GLFW_KEY_UP)){
            angularVelZ -= accel;
        }
        if(InputManager.key_down(GLFW_KEY_DOWN)){
            angularVelZ += accel;
        }
        if(InputManager.key_down(GLFW_KEY_LEFT)){
            angularVelX -= accel;
        }
        if(InputManager.key_down(GLFW_KEY_RIGHT)){
            angularVelX += accel;
        }
        if(InputManager.key_down(GLFW_KEY_PAGE_DOWN)){
            angularVelY -= accel;
        }
        if(InputManager.key_down(GLFW_KEY_PAGE_UP)){
            angularVelY += accel;
        }

        angularVelX *= damping;
        angularVelY *= damping;
        angularVelZ *= damping;

        //printf("angles: %f %f %f\n", angleX, angleY, angleZ);
        //printf("angular velocities: %f %f %f\n", angularVelX, angularVelY, angularVelZ);

        angleX += angularVelX;
        angleY += angularVelY;
        angleZ += angularVelZ;
        
        //restrain the values like putting the black man in handcuffs
        angleX = fmod(angleX, 360.0f);
        angleY = fmod(angleY, 360.0f);
        angleZ = fmod(angleZ, 360.0f);


        //rendering
        //clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ShaderProgram.activate();

        //set uniforms
        ShaderProgram.set_float("xmin", {xmin});
        ShaderProgram.set_float("xmax", {xmax});
        ShaderProgram.set_float("ymin", {ymin});
        ShaderProgram.set_float("ymax", {ymax});
        ShaderProgram.set_int("maxIterations", {iterations});

        
        VAO.bind();
        VBO.bind();
        EBO.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        

        WindowManager.refresh();
        time = glfwGetTime();
        dt = time - lastTime;
        fps = 1 / dt;
        lastTime = time;

        printf("dt: %lf fps: %lf\n", dt, fps);
    }

    return 0;
}


