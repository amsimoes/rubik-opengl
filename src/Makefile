UNAME := $(shell uname)

CXX = g++
CXXFLAGS = -Wall -g 
LIBFLAGS = -Wall

ifeq ($(UNAME), Linux)
  LIBFLAGS += -lGL -lGLU -lglut
endif
ifeq ($(UNAME), Darwin)
  LIBFLAGS += -Wno-deprecated -framework GLUT -framework OpenGL
endif

rubik: *.cpp
	g++ $(LIBFLAGS) *.cpp -o rubik
