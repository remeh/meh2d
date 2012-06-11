#include <allegro5/allegro_primitives.h>
#include "ui/drawableellipse.h"
#include "core/color.h"
#include "core/rect.h"

namespace meh {

DrawableEllipse::DrawableEllipse(Vector2d<float> center, float rx, float ry, Color color, float thickness) :
    p(center),
    r(Vector2d<float>(rx,ry)),
    c(color),
    t(thickness),
    f(false) {
    type = Drawable::PRIMITIVE;
}

DrawableEllipse::DrawableEllipse(Vector2d<float> center, float rx, float ry, Color color, bool filled) :
    p(center),
    r(Vector2d<float>(rx,ry)),
    c(color),
    t(1.0f),
    f(filled) {
    type = Drawable::PRIMITIVE;
}

DrawableEllipse::DrawableEllipse(Vector2d<float> center, float r, Color color, float thickness) :
    p(center),
    r(Vector2d<float>(r,r)),
    c(color),
    t(thickness),
    f(false) {
    type = Drawable::PRIMITIVE;
}

DrawableEllipse::DrawableEllipse(Vector2d<float> center, float r, Color color, bool filled) :
    p(center),
    r(Vector2d<float>(r,r)),
    c(color),
    t(1.0f),
    f(filled) {
    type = Drawable::PRIMITIVE;
}

void DrawableEllipse::draw() {
    if (f) {
        al_draw_filled_ellipse(p.x(),p.y(),r.x(),r.y(),c.color());
    } else {
        al_draw_ellipse(p.x(),p.y(),r.x(),r.y(),c.color(),t);
    }
}

void DrawableEllipse::tick() {
    // Nothing to do
}

} // namespace meh
