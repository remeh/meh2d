#include <allegro5/allegro_primitives.h>
#include "ui/drawableroundedrectangle.h"
#include "core/color.h"
#include "core/rect.h"

namespace meh {

DrawableRoundedRectangle::DrawableRoundedRectangle(Rect<float> rect, float rx, float ry, Color color, float thickness) :
    r(rect),
    c(color),
    t(thickness),
    f(false),
    rx(rx),
    ry(ry) {
    type = Drawable::PRIMITIVE;
}

DrawableRoundedRectangle::DrawableRoundedRectangle(Rect<float> rect, float rx, float ry, Color color, bool filled) :
    r(rect),
    c(color),
    t(1.0f),
    f(filled),
    rx(rx),
    ry(ry) {
    type = Drawable::PRIMITIVE;
}

void DrawableRoundedRectangle::draw() {
    if (f) {
        al_draw_filled_rounded_rectangle(r.position().x(),r.position().y(),r.position().x()+r.size().x(),r.position().y()+r.size().y(),rx,ry,c.color());
    } else {
        al_draw_rounded_rectangle(r.position().x(),r.position().y(),r.position().x()+r.size().x(),r.position().y()+r.size().y(),rx,ry,c.color(),t);
    }
}

void DrawableRoundedRectangle::tick() {
    // Nothing to do
}

} // namespace meh
