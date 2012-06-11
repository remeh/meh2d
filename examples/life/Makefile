CC = g++
OBJ  = life.o
ROOT = ../../src

LIBS = -lallegro -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_font -lallegro_ttf 
INCS = -I/usr/include -I../../include/
CFLAGS = -g -Wall -O3 $(INCS) -D_REENTRANT -DDEBUG -std=c++0x

all: life 

clean:
	rm -rf life $(OBJ) 

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

life: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS) ../../libmeh.so

