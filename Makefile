SRC_DIR = src
OBJ_DIR = obj

INCLUDES = include

CXX = clang++
CFLAGS = --std=c++14

all:
	$(CXX) $(CFLAGS) -I$(INCLUDES) src/*.cpp

clean:
	rm -f a.out
