#include <allegro5/allegro_primitives.h>
#include "ui/drawabletriangle.h"
#include "core/color.h"
#include "core/vector2d.h"

namespace meh {

DrawableTriangle::DrawableTriangle(Vector2d<float> p1, Vector2d<float> p2, Vector2d<float> p3, Color color, float thickness) :
    p1(p1),
    p2(p2),
    p3(p3),
    c(color),
    t(thickness),
    f(false) {
    type = Drawable::PRIMITIVE;
}

DrawableTriangle::DrawableTriangle(Vector2d<float> p1, Vector2d<float> p2, Vector2d<float> p3, Color color, bool filled) :
    p1(p1),
    p2(p2),
    p3(p3),
    c(color),
    t(1.0f),
    f(filled) {
    type = Drawable::PRIMITIVE;
}

void DrawableTriangle::draw() {
    if (f) {
        al_draw_filled_triangle(p1.x(),p1.y(),p2.x(),p2.y(),p3.x(),p3.y(),c.color());
    } else {
        al_draw_triangle(p1.x(),p1.y(),p2.x(),p2.y(),p3.x(),p3.y(),c.color(),t);
    }
}

void DrawableTriangle::tick() {
    // Nothing to do
}

} // namespace meh
