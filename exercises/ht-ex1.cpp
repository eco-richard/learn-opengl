/* 
 * Hello Triangle 
 * Exercise 1
 * Try to draw 2 triangles next to each other using glDrawArrays 
 * by adding more vertices to your data
 * 
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
  auto fsSrc = parseShader("../shaders/fragmentShader.glsl");

  const char* vertSrc = vsSrc.c_str();
  const char* fragSrc = fsSrc.c_str();

  // Creating the vertex shader
  uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertSrc, NULL);
  glCompileShader(vertexShader);

  // check for errors compiling the shaders
  if (!printShaderError(vertexShader)) {
    std::exit(1);
  }

  // Creating a fragment shader
  uint32_t fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fragSrc, NULL);
  glCompileShader(fragShader);

  // check for errors compiling the shaders
  if (!printShaderError(fragShader)) {
    std::exit(1);
  }

  // Link shaders to a program on the GPU
  uint32_t program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  // Check for errors while linking
  if (!printProgramError(program)) {
    std::exit(1);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  float verticies[] = {
    // first triangle
    -0.9f, -0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
    -0.45f, 0.5f, 0.0f,
    // second triangle
    0.0f, -0.5f, 0.0f,
    0.9f, -0.5f, 0.0f,
    0.45f, 0.5f, 0.0f
  };

  // Generate the vertex array and the buffer
  uint32_t vbo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  // bind the vertex array object
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
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
    glUseProgram(program);
    glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteProgram(program);

  glfwTerminate();

  return 0;
}