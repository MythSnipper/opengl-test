#include <main.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  std::cout << "framebuffer size changed to: " << width << "x" << height << "!\n";
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }
}

int main(int argc, char* argv[]){
  #ifdef _WIN32
  std::cout << "Running on windows\n";
  #else
  std::cout << "Running on linux\n";
  #endif


  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,  3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,  3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "nuck OpenGL test", NULL, NULL);
  if(!window){
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD\n";
    return 1;
  }
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while(!glfwWindowShouldClose(window)){
    //input
    processInput(window);

    //rendering


    //check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();


  return 0;
}


