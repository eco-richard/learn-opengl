cmake_minimum_required(VERSION 3.20)

project(learn-opengl)

set(CMAKE_CXX_STANDARD 20)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(main main.cpp utils.cpp)

add_executable(triangle triangle.cpp utils.cpp)
add_executable(rectangle rectangle.cpp utils.cpp)

target_link_libraries(main
  PRIVATE
  glad::glad
  glfw
)

target_link_libraries(triangle
  PRIVATE
  glad::glad
  glfw
)


target_link_libraries(rectangle
  PRIVATE
  glad::glad
  glfw
)

# Exercises
# add_executable(ht-ex1 exercises/ht-ex1.cpp utils.cpp)

# target_link_libraries(ht-ex1
#   PRIVATE
#   glad::glad
#   glfw
# )

# add_executable(ht-ex2 exercises/ht-ex2.cpp utils.cpp)

# target_link_libraries(ht-ex2
#   PRIVATE
#   glad::glad
#   glfw
# )


# add_executable(ht-ex3 exercises/ht-ex3.cpp utils.cpp)

# target_link_libraries(ht-ex3
#   PRIVATE
#   glad::glad
#   glfw
# )