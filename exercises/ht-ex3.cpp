/* 
 * Hello Triangle 
 * Exercise 2
 * Now create the same 2 triangles using two different VAOs 
 * and VBOs for their data
 */


#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../utils.h"

int main(void) {
  // Initialize glfw
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    std::exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Create a glfw window
  GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);

  if (window == NULL) {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    std::exit(1);
  }

  glfwMakeContextCurrent(window);

  // Start GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize G:AD" << std::endl;
    glfwTerminate();
    std::exit(1);
  }

  // Where the magic happens

  auto vsSrc = parseShader("../shaders/vertexShader.glsl");
  auto fs1Src = parseShader("../shaders/fragmentShader.glsl");
  auto fs2Src = parseShader("../shaders/ht-ex3-fragShader.glsl");

  const char* vertSrc = vsSrc.c_str();
  const char* frag1Src = fs1Src.c_str();
  const char* frag2Src = fs2Src.c_str();

  // Creating the vertex shader
  uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertSrc, NULL);
  glCompileShader(vertexShader);

  // check for errors compiling the shaders
  if (!printShaderError(vertexShader)) {
    std::exit(1);
  }

  // Creating a fragment shader
  uint32_t frag1Shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag1Shader, 1, &frag1Src, NULL);
  glCompileShader(frag1Shader);

  // check for errors compiling the shaders
  if (!printShaderError(frag1Shader)) {
    std::exit(1);
  }

  // Creating the second fragment shader
  uint32_t frag2Shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag2Shader, 1, &frag2Src, NULL);
  glCompileShader(frag2Shader);

  if (!printShaderError(frag2Shader)) {
    std::exit(1);
  }

  // Link shaders to a program on the GPU
  uint32_t program1 = glCreateProgram();
  glAttachShader(program1, vertexShader);
  glAttachShader(program1, frag1Shader);
  glLinkProgram(program1);

  uint32_t program2 = glCreateProgram();
  glAttachShader(program2, vertexShader);
  glAttachShader(program2, frag2Shader);
  glLinkProgram(program2);

  // Check for errors while linking
  if (!printProgramError(program1)) {
    std::exit(1);
  }
  if (!printProgramError(program2)) {
    std::exit(1);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(frag1Shader);
  glDeleteShader(frag2Shader);

  float verticies[] = {
    // first triangle
    -0.9f, -0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
    -0.45f, 0.5f, 0.0f,
  };

  float verticies2[] = {
    0.0f, -0.5f, 0.0f,
    0.9f, -0.5f, 0.0f,
    0.45f, 0.5f, 0.0f
  };

  // Generate the vertex array and the buffer
  uint32_t vbos[2], vaos[2];
  glGenVertexArrays(2, vaos);
  glGenBuffers(2, vbos);

  // bind the first vertex array object
  glBindVertexArray(vaos[0]);
  glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  // bind the second vertex array object
  glBindVertexArray(vaos[1]);
  glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies2), verticies2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Setup render loop
  while (!glfwWindowShouldClose(window)) {
    // Process input
    processInput(window);

    // Render a colored background
    glClearColor(0.3f, 0.7f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    glUseProgram(program1);
    glBindVertexArray(vaos[0]);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUseProgram(program2);
    glBindVertexArray(vaos[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(2, vaos);
  glDeleteBuffers(2, vbos);
  glDeleteProgram(program1);
  glDeleteProgram(program2);

  glfwTerminate();

  return 0;
}