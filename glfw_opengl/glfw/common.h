#ifndef __COMMON_H__
#define __COMMON_H__
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void error_callback(int error, const char *description);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif //__COMMON_H__
