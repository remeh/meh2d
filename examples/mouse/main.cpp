#include <iostream>
#include <vector>
#include <allegro5/allegro.h>

#include "meh.h"
#include "mouse.h"

using namespace meh;
using namespace std;

int main(int argc, char* argv[]) {
    System::init();

    Canvas canvas(640,480);
    canvas.setTitle("Example 2 - Mouse");

    View *view = new View();
    view->resourcesManager().loadBitmap("bitmap","../../res/sprites.bmp");
    canvas.setView(view);

    bool loop = true;

    KeyboardHandler& keyboard = canvas.keyboardHandler();
    MouseHandler& mouseHandler = canvas.mouseHandler();

    Mouse* mouse = new Mouse(*view);

    meh::Font* fpsFont = new meh::Font("../../res/FreeMono.ttf",16);
    double fpsRefresh = System::currentTime()+1000;
    int fps = 0;
    unsigned int frameCount = 0;

    while (loop) {
        view->tick();
        keyboard.refreshState();
        mouseHandler.refreshState();

        mouse->goTo(mouseHandler.x(),mouseHandler.y());

        // Exit
        if (keyboard.keydown(ALLEGRO_KEY_ESCAPE)) {
            loop = false;
        }

        if (canvas.refresh()) {
            frameCount++;
            char tmp[10];
            sprintf(tmp,"FPS: %i",fps);
            string fpsString = tmp;
            fpsFont->draw(Vector2d<float>(10,10),Color(1.0f,1.0f,1.0f,0.5f), fpsString);
            
            Rect<float> cursor = Rect<float>(mouseHandler.x(), mouseHandler.y(), 5,5);
            Rect<float> truc = Rect<float>(mouse->position().x(), mouse->position().y(), 64, 64);
            if (cursor.intersects(truc)) {
                Color c = Color(0.5f,0.5f,0.0f,0.5f);
                mouse->sprite().setTintColor(c);
            } else {
                Color k = Color(1.0f,1.0f,1.0f,1.0f);
                mouse->sprite().setTintColor(k);
            }

            canvas.flip();
        }
        
        if (System::currentTime() > fpsRefresh) {
            fpsRefresh = System::currentTime() + 1000;
            fps = frameCount;
            frameCount = 0;
        }
    }

    return 0;
}
