#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "meh.h"

using namespace meh;

int main(int argc, char* argv[]) {
    /*
     * Init Allegro system
     */
    System::init();
    
    /*
     * File Config
     */
    FileConfig config("res/config.ini");
    std::cout << "Map: " << config.values()["section1"]["value3"] << std::endl;
    std::cout << "Al: " << config.getValue("section1","value3") << std::endl;

    /*
     * Canvas
     */
    Canvas canvas(320,240);
    canvas.setTitle("BONJOUR!");
    Vector2d<int> w(128,128);
    canvas.setPosition(w);

    /*
     * View
     */
    View* view = new View;
    View* childView = new View(view);

    ResourcesManager& rm = view->resourcesManager();
    rm.loadBitmap("bitmap","res/sprites.bmp");
    canvas.setView(view);

    /*
     * Sound
     */
//    Sample* sample = rm.loadSample("key","res/key.wav");
//    sample->setPlayMode(Sample::PlayMode::ONCE);
//    sample = childView->getSample("key");
//    sample->play();

    Vector2d<int> vector(0,0);

    /*
     * Sprite
     */
    Vector2d<float> pos(32,32);
    Vector2d<float> size(16,16);
    unsigned int durations[] = { 250,250,250,250 };
    Rect<float> texCoords[] = { Rect<float>(0,0,16,16), Rect<float>(16,0,16,16), Rect<float>(0,0,16,16), Rect<float>(32,0,16,16) };
    Rect<float> texCoordsUp[] = { Rect<float>(48,0,16,16), Rect<float>(64,0,16,16), Rect<float>(48,0,16,16), Rect<float>(80,0,16,16) };
    Rect<float> texCoordsRight[] = { Rect<float>(96,0,16,16), Rect<float>(112,0,16,16), Rect<float>(96,0,16,16), Rect<float>(128,0,16,16) };
    Rect<float> texCoordsLeft[] = { Rect<float>(144,0,16,16), Rect<float>(160,0,16,16), Rect<float>(144,0,16,16), Rect<float>(176,0,16,16) };
    Sprite* sprite = nullptr;

    /*
     * Font
     */
    meh::Font* font = view->resourcesManager().loadFont("fontNormal", "./res/FreeMono.ttf", 56);
    DrawableText* fonttext = new DrawableText(Vector2d<float>(25,25), Color(0.5f,0.5f,0.5f,0.1f), "Some text", *childView, "fontNormal", meh::Font::LEFT);
    
    int i = 0;
    for(i = 0; i < 1; i++) {
        pos.setX(System::rnd(320));
        pos.setY(System::rnd(240));
        sprite = view->addSprite(pos,size,"bitmap",Rect<float>(0,0,16,16));
        sprite->addAnimation("down",4,durations,texCoords);
        sprite->addAnimation("up",4,durations,texCoordsUp);
        sprite->addAnimation("right",4,durations,texCoordsRight);
        sprite->addAnimation("left",4,durations,texCoordsLeft);
        sprite->setAnimation("dwn");
        Color tColor(System::rnd(10)/10.0f,System::rnd(10)/10.0f,System::rnd(10)/10.0f,System::rnd(10)/10.0f);
        sprite->setTintColor(tColor);
    }

    printf("Sprites count : %i\n",i);

    Vector2d<float> c(8,8);
    sprite->setRotationCenter(c);

    /*
     * Mainloop
     */
    bool loop = true;
    int frameCount = 0;
    KeyboardHandler& keyboard = canvas.keyboardHandler();
    MouseHandler& mouse = canvas.mouseHandler();

    double lastRender = System::currentTime();
    Color orange(1.0f,0.3f,0.0f,0.2f);

    /*
     * Draws some primitives.
     */
    DrawableLine* line = new DrawableLine(Vector2d<float>(10,10),Vector2d<float>(310,230),Color(1.0f,1.0f,1.0f,1.0f),1.0f);
    view->addDrawable(line);
    DrawableTriangle* tri = new DrawableTriangle(Vector2d<float>(30,30),Vector2d<float>(10,60),Vector2d<float>(50,60),Color(0.5f,0.0f,0.5f,0.2f),true);
    view->addDrawable(tri);
    Rect<float> rectCoords = Rect<float>(8,8,56,56);
    DrawableRectangle* rect = new DrawableRectangle(rectCoords,Color(0.2f,0.8f,0.2f,0.25f),true);
    view->addDrawable(rect);
    DrawableRoundedRectangle* rrect = new DrawableRoundedRectangle(Rect<float>(60,60,100,100),5.0f,5.0f,Color(0.8f,0.0f,0.75f,0.45f),1.0f);
    view->addDrawable(rrect);
    DrawableEllipse* circle = new DrawableEllipse(Vector2d<float>(220,150),50.0f,Color(1.0f,0.5f,0.0f,0.2f),true);
    view->addDrawable(circle);
    DrawableEllipse* ellipse = new DrawableEllipse(Vector2d<float>(150,180),25.0f,50.0f,Color(0.0f,0.2f,0.8f,0.5f),2.0f);
    view->addDrawable(ellipse);

    /**
     * Moves one of the primitive.
     */
    rect->rect().position().setXY(0,0);

    /*
     * Draws the previous rectangle and line in a Bitmap, then
     * add this Bitmap as a Sprite in a view.
     */
    Bitmap* truc = new Bitmap(64,64);
    truc->bind();
    rect->draw();
    childView->resourcesManager().addBitmap("rect",truc);
    childView->addSprite(Vector2d<float>(100,100), Vector2d<float>(64,64), "rect", Rect<float>(0,0,64,64));
    line->draw();
    font->draw(Vector2d<float>(5,5),Color(1.0f,1.0f,1.0f,1.0f), "AB");

    /*
     * Mainloop
     */
    while (loop) {
        view->tick();
        keyboard.refreshState();
        mouse.refreshState();

        double now = System::currentTime();
        double delta = (now - lastRender); 
        lastRender = now;
        while (delta >= 1) {
            sprite->startAnimation();
            if (keyboard.keydown(ALLEGRO_KEY_UP)) {
                sprite->setAnimation("up");
                sprite->position().setY(sprite->position().y()-0.10);
            } else if (keyboard.keydown(ALLEGRO_KEY_DOWN)) {
                sprite->setAnimation("down");
                sprite->position().setY(sprite->position().y()+0.10);
            } else if (keyboard.keydown(ALLEGRO_KEY_RIGHT)) {
                sprite->setAnimation("right");
                sprite->position().setX(sprite->position().x()+0.10);
            } else if (keyboard.keydown(ALLEGRO_KEY_LEFT)) {
                sprite->setAnimation("left");
                sprite->position().setX(sprite->position().x()-0.10);
            } else if (keyboard.keydown(ALLEGRO_KEY_ESCAPE)) {
                loop = false;
            } else {
                sprite->stopAnimation();
            }
            if (keyboard.keydown(ALLEGRO_KEY_E)) {
                for (int i = 0; i <10; i++) {
                    double time = 500 + System::rnd(250);
                    double ang = System::rnd(360);
                    double velocity = 3.0 + System::rnd(1000)/1000.0;
                    childView->particlesManager().addParticle(sprite->position(),time,ang,velocity,0.01,orange);
                }
            }
            if (keyboard.keydown(ALLEGRO_KEY_C)) {
                meh::Drawable * dd = new DrawableLine(Vector2d<float>(10,10),Vector2d<float>(200,200),Color(0.2f,0.8f,0.8f,1.0f), 5.0f);
                printf("%p\n",dd);
                delete dd;
            }
            if (keyboard.keydown(ALLEGRO_KEY_SPACE)) {
                printf("%i %i %i | %f:%f | %i\n",mouse.left(),mouse.middle(),mouse.right(),mouse.x(),mouse.position().y(),mouse.wheel());
                sprite->setRotationAngle(sprite->rotationAngle()+.01f);
                printf("Angle : %f\n",sprite->rotationAngle());
            }

            Rect<float> spriteRect = Rect<float>(sprite->position().x(),sprite->position().y(),sprite->size().x(),sprite->size().y());
            if (spriteRect.intersects(rectCoords)) {
                for (int i = 0; i <10; i++) {
                    double time = 500 + System::rnd(250);
                    double ang = System::rnd(360);
                    double velocity = 3.0 + System::rnd(1000)/1000.0;
                    childView->particlesManager().addParticle(sprite->position(),time,ang,velocity,0.01,orange);
                }
            }

            delta -= 1.0;
        }

        if (canvas.refresh()) {
            canvas.flip();
            frameCount++;
        }
    }

    printf("Time running : %fs\nFrame count : %i\nFPS : %i\n",System::currentTime()/1000, frameCount, static_cast<int>(static_cast<float>(frameCount)/(System::currentTime()/1000)));
    return 0;
}
