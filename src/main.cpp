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
    std::vector<nuck::Vertex> vertices = {
        //pos                color               texpos
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, //front face 0
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

        {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, //back face 4
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

        {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, //left 8
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, //right 12
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

        {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, //top 16
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, //bottom 20
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, //23
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

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, -1.5f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
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

    nuck::Texture2D texture1("textures/fabric.png", GL_RGBA);
    texture1.bind();


    //test
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(WindowManager.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    double lastTime = glfwGetTime();
    double time = glfwGetTime();
    double dt, fps;

    float camera_speed = 0.2f;
    //Main loop
    while(!WindowManager.window_should_exit()){
        time = glfwGetTime();
        dt = time - lastTime;
        fps = 1 / dt;
        lastTime = time;
        printf("dt: %lf FPS: %lf\n", dt, fps);

        //input
        InputManager.process_input();
        if(InputManager.key_down(GLFW_KEY_W)){
            cameraPos += (camera_speed * dt) * cameraFront;
        }
        if(InputManager.key_down(GLFW_KEY_S)){
            cameraPos -= (camera_speed * dt) * cameraFront;
        }
        if(InputManager.key_down(GLFW_KEY_A)){
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (camera_speed * dt);
        }
        if(InputManager.key_down(GLFW_KEY_D)){
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (camera_speed * dt);
        }
        /*
        if(InputManager.key_down(GLFW_KEY_SPACE)){
            cameraPos += cameraUp * camera_speed;
        }
        if(InputManager.key_down(GLFW_KEY_LEFT_SHIFT)){
            cameraPos -= cameraUp * camera_speed;
        }

        if(InputManager.key_down(GLFW_KEY_UP)){
            cameraFront = glm::rotate(cameraFront, glm::radians(camera_speed * dt), cameraUp);
        }
        if(InputManager.key_down(GLFW_KEY_DOWN)){
            cameraFront = glm::rotate(cameraFront, glm::radians(-camera_speed * dt), cameraUp);
        }
        if(InputManager.key_down(GLFW_KEY_LEFT)){
            cameraFront = glm::rotate(cameraFront, glm::radians(camera_speed * dt), glm::cross(cameraFront, cameraUp));
        }
        if(InputManager.key_down(GLFW_KEY_RIGHT)){
            cameraFront = glm::rotate(cameraFront, glm::radians(-camera_speed * dt), glm::cross(cameraFront, cameraUp));
        }
        if(InputManager.key_down(GLFW_KEY_PAGE_DOWN)){
            cameraFront = glm::rotate(cameraFront, glm::radians(camera_speed * dt), glm::cross(cameraFront, cameraUp));
        }
        if(InputManager.key_down(GLFW_KEY_PAGE_UP)){
            cameraFront = glm::rotate(cameraFront, glm::radians(-camera_speed * dt), glm::cross(cameraFront, cameraUp));
        }
        */


        //Matrices
        //Vclip = Mprojection * Mview * Mmodel * Vlocal
        //fov, aspect ratio, near field, far field
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), WindowManager.aspect_ratio, 0.1f, 100.0f);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        //rendering
        //clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ShaderProgram.activate();

        VAO.bind();
        VBO.bind();
        EBO.bind();

        //set uniforms
        ShaderProgram.set_mat4("aProjection", false, projection);
        ShaderProgram.set_mat4("aView", false, view);
        //ShaderProgram.set_mat4("aModel", false, model);

        ShaderProgram.set_int("texture0", {0});
        ShaderProgram.set_int("texture1", {1});
        texture0.bind_texture_unit(GL_TEXTURE0);
        texture1.bind_texture_unit(GL_TEXTURE1);

        for(uint32_t i=0;i<10;i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ShaderProgram.set_mat4("aModel", false, model);
            glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);
        }
        
        
        
        WindowManager.refresh();
    }

    return 0;
}


