CC = g++
OBJ  = main.o mouse.o
ROOT = ../..

LIBS = -lallegro -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_font -lallegro_ttf ../../libmeh.so
INCS = -I/usr/include -I$(ROOT)/include/
CFLAGS = -g -Wall -O3 $(INCS) -D_REENTRANT -DDEBUG -std=c++0x

all: mouse 

clean:
	rm -rf mouse $(OBJ) 

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

mouse: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

