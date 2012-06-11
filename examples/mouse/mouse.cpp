#include <cmath>

#include "meh.h"
#include "mouse.h"

using namespace meh;

Mouse::Mouse(View& view) {
    Vector2d<float> pos(304,224);
    s = new Sprite(pos,Vector2d<float>(64,64), view, "bitmap", Rect<float>(0,16,16,16));
    Vector2d<float> c(32,32);
    s->setRotationCenter(c);
}

void Mouse::goTo(float x, float y) {
    Vector2d<float> pos = s->position();
    float dx = pos.x() - x;
    float dy = pos.y() - y;

    float angle = 0.0;
    if (x != 0) {
        angle = atan2(static_cast<int>(dx),static_cast<int>(dy));
    }
    angle = angle*180/ALLEGRO_PI;

    dx = dx/25.0f;
    dy = dy/25.0f;

    if (angle == 180.0f) {
        angle = 0.0001f;
    }
    s->setRotationAngle(-angle+180.0f);

    s->setPosition(pos.x()-dx,pos.y()-dy);
}
