CC = g++
OBJ =  ./src/ui/view.o ./src/ui/drawablerectangle.o ./src/ui/spriteanimation.o ./src/ui/sprite.o ./src/ui/drawableroundedrectangle.o ./src/ui/drawabletriangle.o ./src/ui/drawabletext.o ./src/ui/canvas.o ./src/ui/particle.o ./src/ui/drawableellipse.o ./src/ui/particlesmanager.o ./src/ui/bitmap.o ./src/ui/drawableline.o ./src/core/sample.o ./src/core/system.o ./src/core/keyboardhandler.o ./src/core/timer.o ./src/core/font.o ./src/core/resourcesmanager.o ./src/core/fileconfig.o ./src/core/mousehandler.o
INCS = -I/usr/include -I./include/

CFLAGS = -g -Wall -O2 $(INCS) -D_REENTRANT -DDEBUG -std=c++0x

LIBS = `pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
all: libmeh.so

clean:
	rm -rf meh $(OBJ) libmeh.so

%.o: %.cpp
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

libmeh.so: $(OBJ)
	$(CC) -shared $(OBJ) -o $@ $(LIBS)

main: libmeh.so main.cpp
	$(CC) -o main $(OBJ) main.cpp $(LIBS) $(CFLAGS) $(INCS)

