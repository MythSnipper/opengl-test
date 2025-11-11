#include <nucklib.hpp>

float xmin_lim = -3.6f;
float xmax_lim = 3.6f;
float ymin_lim = -2.4f;
float ymax_lim = 2.4f;


float xmin = xmin_lim;
float xmax = xmax_lim;
float ymin = ymin_lim;
float ymax = ymax_lim;

int iterations = 1000;
int limit = 4;
bool vsync = true;
char* fragShader = "shaders/mandelbrot.frag";


void scroll_zoom(GLFWwindow* window, double zoomAmount) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // normalized mouse coordinates (0..1)
    double nx = mouseX / double(width);
    double ny = 1.0 - mouseY / double(height);

    double zoomFactor = 1.0 + zoomAmount * 0.1; // adjust speed
    if (zoomFactor < 0.1) zoomFactor = 0.1;     // prevent negative/zero scale

    // compute current view size
    double xRange = xmax - xmin;
    double yRange = ymax - ymin;

    // point under mouse in complex plane
    double mouseRe = xmin + nx * xRange;
    double mouseIm = ymin + (1.0 - ny) * yRange;

    // scale view around mouse
    xmin = mouseRe + (xmin - mouseRe) / zoomFactor;
    xmax = mouseRe + (xmax - mouseRe) / zoomFactor;
    ymin = mouseIm + (ymin - mouseIm) / zoomFactor;
    ymax = mouseIm + (ymax - mouseIm) / zoomFactor;
}

// GLFW scroll callback just calls the function
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    scroll_zoom(window, yoffset);
}


int main(int argc, char* argv[]){

    nuck::WindowManager WindowManager(3, 3, 1280, 720, "nuckGL");
    glfwSetScrollCallback(WindowManager.window, scroll_callback);

    nuck::InputManager InputManager(WindowManager.window);

    //must do configs
    nuck::GL GL;
    GL.set_wireframe_mode(false);
    GL.set_background_color(0x104C7E);
    GL.set_depth_test(true);
    GL.set_vsync(vsync);

    stbi_set_flip_vertically_on_load(true);

    nuck::ShaderProgram ShaderProgram("shaders/mandelbrot.vert", fragShader);
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
    
    double lastTime = glfwGetTime();
    double time = glfwGetTime();
    double dt, fps;

    uint32_t ctr = 0;

    //Main loop
    while(!WindowManager.window_should_exit()){
        //input
        
        InputManager.process_input();
        if(InputManager.key_down(GLFW_KEY_Z)){
            scroll_zoom(WindowManager.window, 1.05);
        }
        if(InputManager.key_down(GLFW_KEY_X)){
            scroll_zoom(WindowManager.window, -1.05);
        }



        //clamps
        nuck::clamp(&xmin, xmin_lim, xmax_lim);
        nuck::clamp(&xmax, xmin_lim, xmax_lim);
        nuck::clamp(&ymin, ymin_lim, ymax_lim);
        nuck::clamp(&ymax, ymin_lim, ymax_lim);

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
        ctr++;
        if(ctr > 30){
            printf("FPS: %lf\n", fps);
            ctr = 0;
        }
    }

    return 0;
}


