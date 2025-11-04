#include "nucklib.hpp"


namespace nuck{

    class GLFW{
        bool killGLFW = false;


        GLFW(const int opengl_context_version_major, const int opengl_context_version_minor, const int window_width, const int window_height, const char* window_title){
            glfwInit();
            killGLFW = true;
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_context_version_major);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_context_version_minor);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
            if(!window){
                throw std::runtime_error("Failed to create GLFW window\n");
                
            }
            glfwMakeContextCurrent(window);
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
                throw std::runtime_error("Failed to initialize GLAD\n");
                
            }
            glViewport(0, 0, window_width, window_height);
            glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
        }
        ~GLFW(){
            std::cout << "Killing GLFW\n";
            if(killGLFW){
                glfwTerminate();
            }
        }



    };











}





