#include <iostream>
#include <string>
#include <vector>
#include <allegro5/allegro.h>

#include "meh.h"

#define WIDTH 128
#define HEIGHT 96

#define S_WIDTH 5 

using namespace meh;

Sprite* at(std::vector<Sprite*>& sprites,int x, int y) {
    return sprites[y*WIDTH+x];
}

void init(View& view, std::vector<Sprite*>& sprites, bool val[2][WIDTH][HEIGHT]) {
    int i,j;
    for (i = 0; i < HEIGHT; i++) {
        for (j=0; j < WIDTH;j++) {
             Vector2d<float> pos(j*S_WIDTH,i*S_WIDTH);
             Vector2d<float> size(S_WIDTH,S_WIDTH);
             Rect<float> texCoord(0,0,S_WIDTH,S_WIDTH);
             Sprite *s = view.addSprite(pos,size,"bitmap",texCoord);
             Color tColor(System::rnd(10)/10.0f,System::rnd(10)/10.0f,System::rnd(10)/10.0f,1.0f);
             Vector2d<float> c(2,2);
             s->setRotationCenter(c);
             s->setRotationAngle(45.0f);
             s->setTintColor(tColor);
             sprites.push_back(s);
             s->hide();
             val[0][j][i] = false;
             if (System::rnd(7) == 0) {
                val[0][j][i] = true;
             }
        }
    }
}

void life(std::vector<Sprite*>& sprites, bool val[2][WIDTH][HEIGHT], int& buffer, ParticlesManager& pm) {
    int x,y;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            val[!buffer][x][y] = val[buffer][x][y];
        }
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            int xm = x > 0 ? x-1 : WIDTH-1;
            int xp = x < WIDTH-1 ? x+1 : 0;
            int ym = y > 0 ? y-1 : HEIGHT-1;
            int yp = y < HEIGHT-1 ? y+1 : 0;
            int count = 0;

            // Count how many neighbors
            count += val[!buffer][xm][ym];
            count += val[!buffer][x][ym];
            count += val[!buffer][xp][ym];
            count += val[!buffer][xm][y];
            count += val[!buffer][xp][y];
            count += val[!buffer][xm][yp];
            count += val[!buffer][x][yp];
            count += val[!buffer][xp][yp];

            if (!val[!buffer][x][y] && count == 3) {
                val[buffer][x][y] = true;
            }
            if (val[!buffer][x][y] && !(count == 2 || count == 3)) {
                val[buffer][x][y] = false;
            }
        }
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
           if (val[buffer][x][y]) {
             at(sprites,x,y)->show();
           } else {
               at(sprites,x,y)->hide();
           }
        }   
    }
}

int main(int argc, char* argv[]) {
    System::init();

    Canvas canvas(640,480);
    canvas.setTitle("Example 1 - Conway's game of life");

    View *view = new View();
    view->resourcesManager().loadBitmap("bitmap","../res/bitmap.bmp");
    View *particlesView = new View(view);
    canvas.setView(view);

    bool loop = true;
    // List of sprites used to render the scene
    std::vector<Sprite*> sprites;
    // Which buffer we're currently rendering
    int buffer = 0;
    // The states of the game of life (with 2 buffers)
    bool val[2][WIDTH][HEIGHT];

    init(*view,sprites,val);

    KeyboardHandler& keyboard = canvas.keyboardHandler();
    double now = System::currentTime();
    unsigned int frameCount = 0;
    double delay = 100.0;

    while (loop) {
        view->tick();
        keyboard.refreshState();

        if (canvas.refresh()) {
            canvas.flip();
            frameCount++;
        }

        if (System::currentTime() > now+delay) {
            life(sprites,val,buffer,particlesView->particlesManager());
            now = System::currentTime();
        }
        
        // Exit
        if (keyboard.keydown(ALLEGRO_KEY_ESCAPE)) {
            loop = false;
        } else if (keyboard.keydown(ALLEGRO_KEY_LEFT)) {
            delay -= 25.0;
        } else if (keyboard.keydown(ALLEGRO_KEY_RIGHT)) {
            delay += 25.0;
        }

    }

    printf("Time running : %fs\nFrame count : %i\nFPS : %i\n",System::currentTime()/1000, frameCount, static_cast<int>(static_cast<float>(frameCount)/(System::currentTime()/1000)));


    return 0;
}
