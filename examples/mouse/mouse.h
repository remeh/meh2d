#ifndef MOUSE_H
#define MOUSE_H

#include "meh.h"

using namespace meh;

class Mouse {
    private:
        Vector2d<float> pos;
        Sprite* s;

    protected:
    public:
        Mouse(View& view);

        void goTo(float x, float y);

        Vector2d<float> position() { return pos; }

        void setPosition(float x, float y) {
            pos.setXY(x,y);
            s->setPosition(x,y);
        }

        Sprite& sprite() { return *s; }
};

#endif // MOUSE_H
