CC = g++
OBJ = 
INCS = -I/usr/include -I../../include/

CFLAGS = -g -Wall -O2 $(INCS) -D_REENTRANT -DDEBUG -std=c++0x

LIBS = `pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_primitives-5.0 allegro_ttf-5.0` ../../libmeh.so
all: basic 

clean:
	rm -rf basic $(OBJ) 

%.o: %.cpp
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

basic: main.cpp
	$(CC) -o main $(OBJ) main.cpp $(LIBS) $(CFLAGS) $(INCS)

