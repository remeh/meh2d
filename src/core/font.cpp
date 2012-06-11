#include <string>
#include "core/font.h"

using namespace std;

namespace meh {

Font::Font(string filename, int ptSize) :
    aFont(nullptr),
    pt(ptSize) {
    aFont = al_load_ttf_font(filename.c_str(),ptSize,0);
}

Font::~Font() {
    if (aFont) {
        al_destroy_font(aFont);
    }
}

void Font::draw(Vector2d<float> position, Color color, string text, Font::TextAlignement alignement) {
    al_draw_text(aFont, color.color(), position.x(), position.y(), alignement, text.c_str());
}

} // namespace meh
