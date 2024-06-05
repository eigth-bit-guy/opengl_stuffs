#include <stdio.h>
#include "common.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

int main(void)
{
  glfwSetErrorCallback(error_callback);

  if(!glfwInit())
    return -1; //error code

  //glfw hint
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int width = 640;
  int height = 840;
  GLFWwindow *window = glfwCreateWindow(width, height, "glfw demo", NULL, NULL);
  if(!window){
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  while(!glfwWindowShouldClose(window)){
    glfwSetKeyCallback(window, key_callback);

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwSwapInterval(1);
    
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
