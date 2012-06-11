#include <string>
#include "core/vector2d.h"
#include "ui/drawabletext.h"

using namespace std;

namespace meh {

DrawableText::DrawableText(Vector2d<float> position, Color color, string text, View& view, string fontUniqueId, Font::TextAlignement alignement) :
    pos(position),
    c(color),
    t(text),
    v(view),
    id(fontUniqueId),
    align(alignement) {
    view.addDrawable(this);
}

void DrawableText::draw() {
    Font* f = v.getFont(id);
    f->draw(pos,c,t.c_str(),align);
}

} // namespace meh
