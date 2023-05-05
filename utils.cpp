#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util.h"
#include "utils.h"

void processInput(GLFWwindow* window) {
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    std::cout << "Pressed ESCAPE" << std::endl;
    glfwSetWindowShouldClose(window, true);
   }
} 

std::string parseShader(const char *filepath) {
  std::ifstream stream(filepath);

  std::stringstream ss;
  std::string line;
  while(std::getline(stream, line)) {
    ss << line << '\n';
  }

  auto shader = ss.str();
  return shader.c_str();
}

bool printShaderError(uint32_t shader) {
  int success;
  char infoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR: Shader Compilation failed: " << infoLog << std::endl;
    return false;
  }
  return true;
}

bool printProgramError(uint32_t program) {
  int success;
  char infoLog[512];

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cout << "Error: Program linking failed: " << infoLog << std::endl;
    return false;
  }
  return true;
}
