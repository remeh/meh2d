#include <allegro5/allegro_primitives.h>
#include "ui/drawableline.h"

namespace meh {

DrawableLine::DrawableLine(Vector2d<float> start, Vector2d<float> end, Color color, float thickness) :
    s(start),
    e(end),
    c(color),
    t(thickness) { 
    type = Drawable::PRIMITIVE;
}

void DrawableLine::draw() {
    al_draw_line(s.x(),s.y(),e.x(),e.y(),c.color(),t);
}

void DrawableLine::tick() {
    // Nothing to do
}

} // namespace meh
