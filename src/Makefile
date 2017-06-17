UNAME := $(shell uname)

CXX = g++
CXXFLAGS = -Wall -g 
LIBFLAGS = -lGL -lGLU

ifeq ($(UNAME), Linux)
  LIBFLAGS += -lglut
endif
ifeq ($(UNAME), Darwin)
  LIBFLAGS += ...
endif

rubik: *.cpp
	g++ -Wall $(LIBFLAGS) *.cpp -o rubik
