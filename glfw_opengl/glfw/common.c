#include <stdio.h>
#include "common.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
    printf("Space press, window close\n");
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}
