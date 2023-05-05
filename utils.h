#ifndef LEARN_OPENGL_UTILS_H
#define LEARN_OPENGL_UTILS_H

#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window);
std::string parseShader(const char* filepath);
bool printShaderError(uint32_t shader);
bool printProgramError(uint32_t program);

#endif // LEARN_OPENGL_UTILS_H