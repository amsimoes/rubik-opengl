set (PROJECT_NAME "rubik-cg")

if (APPLE)
  set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -g -framework OpenGl -lglfw3 -lsfml-audio -framework Cocoa -framework IOKit -framework CoreVideo")
ELSE (NOT APPLE)
  set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -g -lGLEW -lGL -lGLU -lglut -lglfw -lsfml-audio")
ENDIF (APPLE)

project (${PROJECT_NAME})
cmake_minimum_required(VERSION 3.0.2)

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries (${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
