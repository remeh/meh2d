#include <allegro5/allegro_primitives.h>
#include "ui/drawablerectangle.h"
#include "core/color.h"
#include "core/rect.h"

namespace meh {

DrawableRectangle::DrawableRectangle(Rect<float> rect, Color color, float thickness) :
    r(rect),
    c(color),
    t(thickness),
    f(false) {
    type = Drawable::PRIMITIVE;
}

DrawableRectangle::DrawableRectangle(Rect<float> rect, Color color, bool filled) :
    r(rect),
    c(color),
    t(1.0f),
    f(filled) {
    type = Drawable::PRIMITIVE;
}

void DrawableRectangle::draw() {
    if (f) {
        al_draw_filled_rectangle(r.position().x(),r.position().y(),r.position().x()+r.size().x(),r.position().y()+r.size().y(),c.color());
    } else {
        al_draw_rectangle(r.position().x(),r.position().y(),r.position().x()+r.size().x(),r.position().y()+r.size().y(),c.color(),t);
    }
}

void DrawableRectangle::tick() {
    // Nothing to do
}

} // namespace meh
